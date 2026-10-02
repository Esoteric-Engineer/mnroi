typedef unsigned long u32;
typedef unsigned short u16;
typedef short s16;
typedef long long s64;
typedef void (*__OSInterruptHandler)(s16 interrupt, void* context);

extern __OSInterruptHandler* InterruptHandlerTable;
extern volatile s16 __OSLastInterrupt;
extern volatile s64 __OSLastInterruptTime;
extern volatile u32 __OSLastInterruptSrr0;

extern void OSLoadContext(void* context);
extern s64 OSGetTime(void);
extern int OSDisableScheduler(void);
extern int OSEnableScheduler(void);
extern void __OSReschedule(void);

volatile u16 __MEMRegs[64] : 0xCC004000;
volatile u16 __DSPRegs[0x20] : 0xCC005000;
volatile u32 __EXIRegs[0x20] : 0xCC006800;
volatile u32 __AIRegs[8] : 0xCC006C00;
volatile u32 __PIRegs[0x20] : 0xCC003000;

static u32 InterruptPrioTable[] = {
    0x00000100, 0x00000040, 0xF8000000, 0x00000200, 0x00000080, 0x00003000,
    0x00000020, 0x03FF8C00, 0x04000000, 0x00004000, 0xFFFFFFFF,
};

static inline __OSInterruptHandler GetInterruptHandler(s16 interrupt)
{
    return InterruptHandlerTable[interrupt];
}

#pragma peephole off
void __OSDispatchInterrupt(s16 exception, void* context)
{
    u32 intsr;
    u32 reg;
    u32 cause;
    u32 unmasked;
    u32* prio;
    s16 interrupt;
    __OSInterruptHandler handler;

    intsr = __PIRegs[0];
    intsr &= ~0x00010000;

    if (intsr == 0 || (intsr & __PIRegs[1]) == 0) {
        OSLoadContext(context);
    }

    cause = 0;

    if (intsr & 0x00000080) {
        reg = __MEMRegs[15];
        if (reg & 0x1)
            cause |= 0x80000000;
        if (reg & 0x2)
            cause |= 0x40000000;
        if (reg & 0x4)
            cause |= 0x20000000;
        if (reg & 0x8)
            cause |= 0x10000000;
        if (reg & 0x10)
            cause |= 0x08000000;
    }

    if (intsr & 0x00000040) {
        reg = __DSPRegs[5];
        if (reg & 0x8)
            cause |= 0x04000000;
        if (reg & 0x20)
            cause |= 0x02000000;
        if (reg & 0x80)
            cause |= 0x01000000;
    }

    if (intsr & 0x00000020) {
        reg = __AIRegs[0];
        if (reg & 0x8)
            cause |= 0x00800000;
    }

    if (intsr & 0x00000010) {
        reg = __EXIRegs[0];
        if (reg & 0x2)
            cause |= 0x00400000;
        if (reg & 0x8)
            cause |= 0x00200000;
        if (reg & 0x800)
            cause |= 0x00100000;
        reg = __EXIRegs[5];
        if (reg & 0x2)
            cause |= 0x00080000;
        if (reg & 0x8)
            cause |= 0x00040000;
        if (reg & 0x800)
            cause |= 0x00020000;
        reg = __EXIRegs[10];
        if (reg & 0x2)
            cause |= 0x00010000;
        if (reg & 0x8)
            cause |= 0x00008000;
    }

    if (intsr & 0x00002000)
        cause |= 0x00000020;
    if (intsr & 0x00001000)
        cause |= 0x00000040;
    if (intsr & 0x00000400)
        cause |= 0x00001000;
    if (intsr & 0x00000200)
        cause |= 0x00002000;
    if (intsr & 0x00000100)
        cause |= 0x00000080;
    if (intsr & 0x00000008)
        cause |= 0x00000800;
    if (intsr & 0x00000004)
        cause |= 0x00000400;
    if (intsr & 0x00000002)
        cause |= 0x00000200;
    if (intsr & 0x00000800)
        cause |= 0x00004000;
    if (intsr & 0x00000001)
        cause |= 0x00000100;

    unmasked = cause & ~(*(u32*)0x800000C4 | *(u32*)0x800000C8);
    if (unmasked) {
        for (prio = InterruptPrioTable;; ++prio) {
            if (unmasked & *prio) {
                interrupt = (s16)__cntlzw(unmasked & *prio);
                break;
            }
        }

        handler = GetInterruptHandler(interrupt);
        if (handler) {
            if (interrupt > 4) {
                __OSLastInterrupt = interrupt;
                __OSLastInterruptTime = OSGetTime();
                __OSLastInterruptSrr0 = *(u32*)((char*)context + 0x198);
            }
            OSDisableScheduler();
            handler(interrupt, context);
            OSEnableScheduler();
            __OSReschedule();
            OSLoadContext(context);
        }
    }

    OSLoadContext(context);
}
