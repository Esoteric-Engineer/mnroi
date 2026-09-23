typedef unsigned long u32;

typedef struct EXIControl {
    u32 pad0[3];
    volatile u32 state;
    u32 pad1[12];
} EXIControl;

extern EXIControl Ecb[3];

#pragma scheduling off
u32 EXIGetState(long chan)
{
    EXIControl* exi;

    exi = &Ecb[chan];
    return exi->state;
}
