typedef unsigned long u32;
typedef long long s64;

volatile u32 __AIRegs[8] : 0xCC006C00;

extern s64 bound_32KHz;
extern s64 bound_48KHz;
extern s64 min_wait;
extern s64 max_wait;
extern s64 buffer;

extern s64 OSGetTime(void);

#pragma peephole off
void __AI_SRC_INIT(void)
{
    s64 rising_32khz = 0;
    s64 rising_48khz = 0;
    s64 diff = 0;
    s64 t1 = 0;
    s64 temp;
    u32 temp0;
    u32 temp1;
    u32 done = 0;
    u32 volume = 0;
    u32 Init_Cnt = 0;
    u32 walking = 0;

    walking = 0;
    Init_Cnt = 0;
    temp = 0;

    while (!done) {
        __AIRegs[0] = (__AIRegs[0] & ~0x20) | 0x20;
        __AIRegs[0] = __AIRegs[0] & ~2;
        __AIRegs[0] = (__AIRegs[0] & ~1) | 1;
        temp0 = __AIRegs[2];
        while (temp0 == __AIRegs[2]) { }
        rising_32khz = OSGetTime();
        __AIRegs[0] = (__AIRegs[0] & ~2) | 2;
        __AIRegs[0] = (__AIRegs[0] & ~1) | 1;
        temp1 = __AIRegs[2];
        while (temp1 == __AIRegs[2]) { }
        rising_48khz = OSGetTime();
        diff = rising_48khz - rising_32khz;
        __AIRegs[0] = __AIRegs[0] & ~2;
        __AIRegs[0] = __AIRegs[0] & ~1;
        if (diff < bound_32KHz - buffer) {
            temp = min_wait;
            done = 1;
            Init_Cnt++;
        } else if (diff >= bound_32KHz + buffer
                   && diff < bound_48KHz - buffer) {
            temp = max_wait;
            done = 1;
            Init_Cnt++;
        } else {
            done = 0;
            walking = 1;
            Init_Cnt++;
        }
    }
    while (rising_48khz + temp > OSGetTime()) { }
}
