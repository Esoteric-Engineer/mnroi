typedef unsigned char u8;
typedef unsigned long u32;
typedef unsigned long long u64;

volatile u32 __AIRegs[8] : 0xCC006C00;
u32 __OSBusClock : 0x800000F8;

char lbl_804D2CA8[] = "<< Dolphin SDK - AI\trelease build: Apr 17 2003 12:33:54 (0x2301) >>";
static char* __AIVersion = lbl_804D2CA8;

extern int __AI_init_flag;
extern void (*__AIS_Callback)(u32);
extern void (*__AID_Callback)(void);
extern u8* __CallbackStack;
extern u64 bound_32KHz;
extern u64 bound_48KHz;
extern u64 min_wait;
extern u64 max_wait;
extern u64 buffer;

extern void OSRegisterVersion(const char* version);
extern void __OSSetInterruptHandler(u32 interrupt, void* handler);
extern void __OSUnmaskInterrupts(u32 mask);
extern void __AI_set_stream_sample_rate(u32 rate);
extern void AISetDSPSampleRate(u32 rate);
extern void __AISHandler(void);
extern void __AIDHandler(void);

#define OS_TIMER_CLOCK (__OSBusClock / 4)
#define NS_TO_TICKS(ns) ((u64)(((ns) * (OS_TIMER_CLOCK / 125000)) / 8000))

// Plain C, not __rlwimi: inlined with vol = 0 this must compile to `ori r0,r0,0`.
#define SET_REG_FIELD(reg, size, shift, val) \
    ((reg) = ((u32)(reg) & ~(((1 << (size)) - 1) << (shift))) | ((u32)(val) << (shift)))

static inline void AISetStreamVolLeft(u8 vol)
{
    SET_REG_FIELD(__AIRegs[1], 8, 0, vol);
}

static inline void AISetStreamVolRight(u8 vol)
{
    SET_REG_FIELD(__AIRegs[1], 8, 8, vol);
}

void AIInit(u8* stack)
{
    if (__AI_init_flag != 1) {
        OSRegisterVersion(__AIVersion);
        bound_32KHz = NS_TO_TICKS(31524);
        bound_48KHz = NS_TO_TICKS(42024);
        min_wait = NS_TO_TICKS(42000);
        max_wait = NS_TO_TICKS(63000);
        buffer = NS_TO_TICKS(3000);
        AISetStreamVolRight(0);
        AISetStreamVolLeft(0);
        __AIRegs[3] = 0;
        __AIRegs[0] = (__AIRegs[0] & 0xFFFFFFDF) | 0x20;
        __AI_set_stream_sample_rate(1);
        AISetDSPSampleRate(0);
        __AIS_Callback = 0;
        __AID_Callback = 0;
        __CallbackStack = stack;
        __OSSetInterruptHandler(5, __AIDHandler);
        __OSUnmaskInterrupts(0x04000000);
        __OSSetInterruptHandler(8, __AISHandler);
        __OSUnmaskInterrupts(0x800000);
        __AI_init_flag = 1;
    }
}
