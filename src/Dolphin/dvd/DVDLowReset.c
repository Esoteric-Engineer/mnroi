typedef int BOOL;
typedef unsigned long u32;
typedef long s32;
typedef long long s64;
typedef s64 OSTime;

extern volatile u32 __DIRegs[0x20] : 0xCC006000;
extern volatile u32 __PIRegs[0x20] : 0xCC003000;

// Declare-at-address (as in os.h) so MWCC hoists the load out of the wait loop.
u32 __OSBusClock : 0x800000F8;

#define OS_BUS_CLOCK __OSBusClock
#define OS_TIMER_CLOCK (OS_BUS_CLOCK / 4)
#define OSMicrosecondsToTicks(usec) (((usec) * (OS_TIMER_CLOCK / 125000)) / 8)

// Reverse declaration order in .sbss: this puts LastResetEnd first and lays the rest of dvdlow.c's .sbss out ascending from there.
s32 NextCommandNumber;
volatile BOOL LastCommandWasRead;
OSTime LastReadIssued;
volatile OSTime LastReadFinished;
u32 WorkAroundSeekLocation;
volatile u32 WorkAroundType;
volatile BOOL lbl_8066F350;
volatile BOOL WaitingCoverClose;
volatile u32 ResetOccurred;
volatile OSTime LastResetEnd;

OSTime __OSGetSystemTime(void);

void DVDLowReset(void)
{
    u32 reg;
    OSTime resetStart;

    __DIRegs[1] = 2;
    reg = __PIRegs[9];
    __PIRegs[9] = (reg & ~4) | 1;

    resetStart = __OSGetSystemTime();
    while ((__OSGetSystemTime() - resetStart) < OSMicrosecondsToTicks(12))
        ;

    __PIRegs[9] = reg | 4 | 1;
    ResetOccurred = 1;
    LastResetEnd = __OSGetSystemTime();
}
