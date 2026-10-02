typedef int BOOL;
typedef unsigned long u32;
typedef unsigned char u8;
typedef long s32;
typedef long long s64;
typedef s64 OSTime;
typedef void (*DVDLowCallback)(u32);

typedef struct {
    u8 pad[8];
    u8 streaming;
} DVDDiskID;

typedef struct {
    void* addr;
    u32 length;
    u32 offset;
} DVDBuffer;

typedef struct {
    s32 cmd;
    void* addr;
    u32 length;
    u32 offset;
    DVDLowCallback callback;
} DVDCommand;

extern volatile u32 __DIRegs[0x20] : 0xCC006000;

extern s32 FirstRead;
extern volatile BOOL StopAtNextInt;
extern volatile BOOL LastCommandWasRead;
extern OSTime LastReadIssued;
extern u32 LastLength;
extern DVDLowCallback Callback;
extern volatile u32 WorkAroundType;
extern u32 WorkAroundSeekLocation;
extern volatile OSTime LastReadFinished;
extern s32 NextCommandNumber;

// Declare-at-address (as in os.h), not a pointer cast: changes the tick-math registers.
u32 __OSBusClock : 0x800000F8;
#define OS_TIMER_CLOCK (__OSBusClock / 4)
#define OSSecondsToTicks(sec) (OS_TIMER_CLOCK * (sec))
#define OSMillisecondsToTicks(msec) ((OS_TIMER_CLOCK / 1000) * (msec))
#define OSMicrosecondsToTicks(usec) (((OS_TIMER_CLOCK / 125000) * (usec)) / 8)

DVDCommand CommandList[3];
long long AlarmForWA[5];
long long AlarmForTimeout[5];
long long AlarmForBreak[5];
DVDBuffer Prev;
DVDBuffer Curr;

OSTime __OSGetSystemTime(void);
void OSCreateAlarm(void* alarm);
void OSSetAlarm(void* alarm, OSTime tick, void* handler);
DVDDiskID* DVDGetCurrentDiskID(void);
void AlarmHandler_80186FE0(void* alarm, void* context);
void AlarmHandlerForTimeout(void* alarm, void* context);
BOOL DVDLowSeek(u32 offset, DVDLowCallback callback);

static inline void SetTimeoutAlarm(OSTime timeout)
{
    OSCreateAlarm(AlarmForTimeout);
    OSSetAlarm(AlarmForTimeout, timeout, AlarmHandlerForTimeout);
}

void Read(void* addr, u32 length, u32 offset, DVDLowCallback callback)
{
    (void)CommandList;
    (void)AlarmForWA;
    (void)AlarmForTimeout;
    (void)AlarmForBreak;
    (void)Prev;
    (void)Curr;

    Callback = callback;
    StopAtNextInt = 0;
    LastCommandWasRead = 1;
    LastReadIssued = __OSGetSystemTime();

    __DIRegs[2] = 0xA8000000;
    __DIRegs[3] = offset / 4;
    __DIRegs[4] = length;
    __DIRegs[5] = (u32)addr;
    __DIRegs[6] = length;
    LastLength = length;
    __DIRegs[7] = 3;

    if (length > 0xA00000) {
        SetTimeoutAlarm(OSSecondsToTicks(20));
    } else {
        SetTimeoutAlarm(OSSecondsToTicks(10));
    }
}

void SeekTwiceBeforeRead(void* addr, u32 length, u32 offset, DVDLowCallback callback)
{
    u32 newOffset;
    DVDCommand* list = CommandList;
    if ((offset & ~0x7FFF) == 0) {
        newOffset = 0;
    } else {
        newOffset = (offset & ~0x7FFF) + WorkAroundSeekLocation;
    }
    list[0].cmd = 2;
    list[0].offset = newOffset;
    list[0].callback = callback;
    list[1].cmd = 1;
    list[1].addr = addr;
    list[1].length = length;
    list[1].offset = offset;
    list[1].callback = callback;
    list[2].cmd = -1;
    NextCommandNumber = 0;
    DVDLowSeek(newOffset, callback);
}

static inline BOOL AudioBufferOn(void)
{
    DVDDiskID* id = DVDGetCurrentDiskID();
    if (id->streaming) {
        return 1;
    }
    return 0;
}

static inline BOOL HitCache(DVDBuffer* cur, DVDBuffer* prev)
{
    u32 uVar1 = (prev->offset + prev->length - 1) >> 15;
    u32 uVar2 = cur->offset >> 15;
    u32 iVar3 = AudioBufferOn() ? 5 : 15;

    if ((uVar2 > uVar1 - 2) || (uVar2 < uVar1 + iVar3 + 3)) {
        return 1;
    }
    return 0;
}

static inline void DoJustRead(void* addr, u32 length, u32 offset, DVDLowCallback callback)
{
    CommandList[0].cmd = -1;
    NextCommandNumber = 0;
    Read(addr, length, offset, callback);
}

static inline void WaitBeforeRead(void* addr, u32 length, u32 offset, DVDLowCallback callback, OSTime timeout)
{
    CommandList[0].cmd = 1;
    CommandList[0].addr = addr;
    CommandList[0].length = length;
    CommandList[0].offset = offset;
    CommandList[0].callback = callback;
    CommandList[1].cmd = -1;
    NextCommandNumber = 0;
    OSCreateAlarm(AlarmForWA);
    OSSetAlarm(AlarmForWA, timeout, AlarmHandler_80186FE0);
}

BOOL DVDLowRead(void* addr, u32 length, u32 offset, DVDLowCallback callback)
{
    u32 blockNumOfPrevEnd;
    u32 blockNumOfCurrStart;
    OSTime diff;

    __DIRegs[6] = length;
    Curr.addr = addr;
    Curr.length = length;
    Curr.offset = offset;

    if (WorkAroundType == 0) {
        DoJustRead(addr, length, offset, callback);
    } else if (WorkAroundType == 1) {
        if (FirstRead) {
            SeekTwiceBeforeRead(addr, length, offset, callback);
        } else {
            if (!HitCache(&Curr, &Prev)) {
                DoJustRead(addr, length, offset, callback);
            } else {
                blockNumOfPrevEnd = (u32)((Prev.offset + Prev.length - 1) >> 15) & 0x1FFFF;
                blockNumOfCurrStart = (u32)((Curr.offset >> 15) & 0x1FFFF);
                if (blockNumOfPrevEnd == blockNumOfCurrStart || blockNumOfPrevEnd + 1 == blockNumOfCurrStart) {
                    diff = __OSGetSystemTime() - LastReadFinished;
                    if (OSMillisecondsToTicks(5) < diff) {
                        DoJustRead(addr, length, offset, callback);
                    } else {
                        WaitBeforeRead(addr, length, offset, callback,
                                       OSMillisecondsToTicks(5) - diff + OSMicrosecondsToTicks(500));
                    }
                } else {
                    SeekTwiceBeforeRead(addr, length, offset, callback);
                }
            }
        }
    }

    return 1;
}
