typedef unsigned long u32;

typedef struct EXIControl {
    u32 pad0[3];
    volatile u32 state;
    u32 pad1[12];
} EXIControl;

extern EXIControl lbl_8057DBE0[3];

#pragma scheduling off
u32 EXIGetState(long chan)
{
    EXIControl* exi;

    exi = &lbl_8057DBE0[chan];
    return exi->state;
}
