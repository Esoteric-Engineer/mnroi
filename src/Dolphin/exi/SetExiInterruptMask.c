typedef unsigned long u32;
typedef long s32;
typedef void (*EXICallback)(s32, void*);

typedef struct EXIControl {
    EXICallback exiCallback;
    EXICallback tcCallback;
    EXICallback extCallback;
    volatile u32 state;
    int immLen;
    unsigned char* immBuf;
    u32 dev;
    u32 id;
    s32 idTime;
    int items;
    struct {
        u32 dev;
        EXICallback callback;
    } queue[3];
} EXIControl;

EXIControl Ecb[3] __attribute__((aligned(32)));

extern void* __OSGetInterruptHandler(short interrupt);
extern u32 __OSMaskInterrupts(u32 mask);
extern u32 __OSUnmaskInterrupts(u32 mask);

#pragma scheduling off

void SetExiInterruptMask(s32 chan, EXIControl* exi)
{
    EXIControl* exi2 = &Ecb[2];

    switch (chan) {
    case 0:
        if ((exi->exiCallback == 0 && exi2->exiCallback == 0) || exi->state & 0x10) {
            __OSMaskInterrupts(0x410000U);
            return;
        }
        __OSUnmaskInterrupts(0x410000U);
        return;
    case 1:
        if (exi->exiCallback == 0 || exi->state & 0x10) {
            __OSMaskInterrupts(0x80000U);
            return;
        }
        __OSUnmaskInterrupts(0x80000U);
        return;
    case 2:
        if ((__OSGetInterruptHandler(0x19) == 0U) || (exi->state & 0x10)) {
            __OSMaskInterrupts(0x40U);
            return;
        }
        __OSUnmaskInterrupts(0x40U);
        return;
    }
}
