typedef int BOOL;
typedef unsigned long u32;
typedef unsigned char u8;
typedef long s32;
typedef long long s64;
typedef s64 OSTime;
typedef void (*DVDLowCallback)(u32);

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
extern DVDLowCallback Callback;
extern DVDLowCallback lbl_8066F33C;
extern volatile OSTime LastResetEnd;
extern volatile u32 ResetOccurred_8066F348;
extern volatile BOOL WaitingCoverClose;
extern volatile BOOL lbl_8066F350;
extern volatile OSTime LastReadFinished;
extern volatile BOOL lbl_8066F370;
extern volatile u32 NextCommandNumber_8066F374;

// DVDLowRead.c's pooled .bss (0x8057D348), addressed off one base register
typedef struct {
    DVDCommand CommandList[3];
    u32 pad;
    long long AlarmForWA[5];
    long long AlarmForTimeout[5];
    long long AlarmForBreak[5];
    DVDBuffer Prev;
    DVDBuffer Curr;
} DVDLowBss;

extern DVDLowBss CommandList;

#define OS_TIMER_CLOCK ((*(u32*)0x800000F8) / 4)
#define OSMillisecondsToTicks(msec) ((OS_TIMER_CLOCK / 1000) * (msec))

extern OSTime __OSGetSystemTime(void);
extern void OSCancelAlarm(void* alarm);
extern void OSClearContext(void* context);
extern void OSSetCurrentContext(void* context);
extern void fn_801870D4(void* addr, u32 length, u32 offset, DVDLowCallback callback);
extern void DVDLowSeek(u32 offset, DVDLowCallback callback);

static inline BOOL ProcessNextCommand(DVDLowBss* bss)
{
    s32 n = NextCommandNumber_8066F374;

    if (bss->CommandList[n].cmd == 1) {
        ++NextCommandNumber_8066F374;
        fn_801870D4(bss->CommandList[n].addr, bss->CommandList[n].length, bss->CommandList[n].offset, bss->CommandList[n].callback);
        return 1;
    } else if (bss->CommandList[n].cmd == 2) {
        ++NextCommandNumber_8066F374;
        DVDLowSeek(bss->CommandList[n].offset, bss->CommandList[n].callback);
        return 1;
    }
    return 0;
}

void __DVDInterruptHandler(s32 interrupt, void* context)
{
    DVDLowCallback cb;
    u8 exceptionContext[0x2C8];
    u32 cause = 0;
    u32 reg;
    u32 intr;
    u32 mask;
    DVDLowBss* bss = &CommandList;

    if (lbl_8066F370) {
        LastReadFinished = __OSGetSystemTime();
        FirstRead = 0;
        bss->Prev.addr = bss->Curr.addr;
        bss->Prev.length = bss->Curr.length;
        bss->Prev.offset = bss->Curr.offset;
        if (StopAtNextInt == 1) {
            cause |= 8;
        }
    }

    lbl_8066F370 = 0;
    StopAtNextInt = 0;
    reg = __DIRegs[0];
    mask = reg & 0x2a;
    intr = (reg & 0x54) & (mask << 1);

    if (intr & 0x40) {
        cause |= 8;
    }
    if (intr & 0x10) {
        cause |= 1;
    }
    if (intr & 4) {
        cause |= 2;
    }
    if (cause) {
        ResetOccurred_8066F348 = 0;
        OSCancelAlarm(bss->AlarmForTimeout);
    }

    __DIRegs[0] = intr | mask;

    if (ResetOccurred_8066F348 && (__OSGetSystemTime() - LastResetEnd) < OSMillisecondsToTicks(200)) {
        reg = __DIRegs[1];
        mask = reg & 2;
        intr = (reg & 4) & (mask << 1);
        if (intr & 4) {
            if (lbl_8066F33C) {
                lbl_8066F33C(4);
            }
            lbl_8066F33C = 0;
        }
        __DIRegs[1] = __DIRegs[1];
    } else if (WaitingCoverClose) {
        reg = __DIRegs[1];
        mask = reg & 2;
        intr = (reg & 4) & (mask << 1);
        if (intr & 4) {
            cause |= 4;
        }
        __DIRegs[1] = intr | mask;
        WaitingCoverClose = 0;
    } else {
        __DIRegs[1] = 0;
    }

    if ((cause & 8) && !lbl_8066F350) {
        cause &= ~8;
    }

    if (cause & 1) {
        if (ProcessNextCommand(bss)) {
            return;
        }
    } else {
        bss->CommandList[0].cmd = -1;
        NextCommandNumber_8066F374 = 0;
    }

    OSClearContext(exceptionContext);
    OSSetCurrentContext(exceptionContext);

    if (cause) {
        cb = Callback;
        Callback = 0;
        if (cb) {
            cb(cause);
        }
        lbl_8066F350 = 0;
    }

    OSClearContext(exceptionContext);
    OSSetCurrentContext(context);
}
