typedef unsigned long u32;
typedef long long s64;
typedef s64 OSTime;

extern volatile u32 __DIRegs[0x20] : 0xCC006000;
extern volatile u32 __PIRegs[0x20] : 0xCC003000;

static volatile OSTime LastResetEnd;
static volatile u32 ResetOccurred;

OSTime __OSGetSystemTime(void);

void DVDLowReset(void)
{
    u32 reg;
    OSTime resetStart;
    u32 ticks;

    __DIRegs[1] = 2;
    reg = __PIRegs[9];
    __PIRegs[9] = (reg & ~4) | 1;

    resetStart = __OSGetSystemTime();
    ticks = ((*(u32*)0x800000F8) / 4 / 125000 * 12) / 8;
    while ((__OSGetSystemTime() - resetStart) < ticks)
        ;

    __PIRegs[9] = reg | 4 | 1;
    ResetOccurred = 1;
    LastResetEnd = __OSGetSystemTime();
}
