typedef unsigned char u8;
typedef unsigned long u32;
typedef unsigned long long u64;

volatile u32 __AIRegs[8] : 0xCC006C00;
u32 __OSBusClock : 0x800000F8;

extern const char* lbl_8066C4B8;
extern int lbl_8066F418;
extern void (*lbl_8066F408)(u32);
extern void (*lbl_8066F40C)(void);
extern u8* lbl_8066F410;
extern u64 lbl_8066F420;
extern u64 lbl_8066F428;
extern u64 lbl_8066F430;
extern u64 lbl_8066F438;
extern u64 lbl_8066F440;

extern void OSRegisterVersion(const char* version);
extern void lbl_8017DBD4(u32 interrupt, void* handler);
extern void __OSUnmaskInterrupts(u32 mask);
extern void __AI_set_stream_sample_rate(u32 rate);
extern void AISetDSPSampleRate(u32 rate);
extern void __AISHandler(void);
extern void fn_8018BC20(void);

#define OS_TIMER_CLOCK (__OSBusClock / 4)
#define NS_TO_TICKS(ns) ((u64)(((ns) * (OS_TIMER_CLOCK / 125000)) / 8000))

static inline void SetVolLeft(u8 vol)
{
    u32 reg = __AIRegs[1];
    reg = (u32)__rlwimi((int)(reg & 0xFFFFFF00), (int)vol, 0, 24, 31);
    __AIRegs[1] = reg;
}

static inline void SetVolRight(u8 vol)
{
    u32 reg = __AIRegs[1];
    reg = (u32)__rlwimi((int)(reg & 0xFFFF00FF), (int)vol, 8, 16, 23);
    __AIRegs[1] = reg;
}

void AIInit(u8* stack)
{
    if (lbl_8066F418 != 1) {
        OSRegisterVersion(lbl_8066C4B8);
        lbl_8066F420 = NS_TO_TICKS(31524);
        lbl_8066F428 = NS_TO_TICKS(42024);
        lbl_8066F430 = NS_TO_TICKS(42000);
        lbl_8066F438 = NS_TO_TICKS(63000);
        lbl_8066F440 = NS_TO_TICKS(3000);
        SetVolRight(0);
        SetVolLeft(0);
        __AIRegs[3] = 0;
        __AIRegs[0] = (__AIRegs[0] & 0xFFFFFFDF) | 0x20;
        __AI_set_stream_sample_rate(1);
        AISetDSPSampleRate(0);
        lbl_8066F408 = 0;
        lbl_8066F40C = 0;
        lbl_8066F410 = stack;
        lbl_8017DBD4(5, fn_8018BC20);
        __OSUnmaskInterrupts(0x04000000);
        lbl_8017DBD4(8, __AISHandler);
        __OSUnmaskInterrupts(0x800000);
        lbl_8066F418 = 1;
    }
}
