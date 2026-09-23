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

extern EXIControl Ecb[3];
volatile u32 __EXIRegs[0x40] : 0xCC006800;

extern int OSDisableInterrupts(void);
extern int OSRestoreInterrupts(int enabled);
extern u32 __OSMaskInterrupts(u32 mask);
extern int __EXIProbe(s32 chan);

#pragma scheduling off

int EXISelect(s32 chan, u32 dev, u32 freq)
{
    EXIControl* exi;
    u32 cpr;
    int enabled;

    exi = &Ecb[chan];
    enabled = OSDisableInterrupts();
    if ((exi->state & 4)
        || ((chan != 2)
            && (((dev == 0) && !(exi->state & 8) && (__EXIProbe(chan) == 0))
                || !(exi->state & 0x10) || (exi->dev != dev)))) {
        OSRestoreInterrupts(enabled);
        return 0;
    }
    exi->state |= 4;
    cpr = __EXIRegs[chan * 5];
    cpr &= 0x405;
    cpr |= (((1 << dev) << 7) | (freq * 0x10));
    __EXIRegs[chan * 5] = cpr;
    if (exi->state & 8) {
        switch (chan) {
        case 0:
            __OSMaskInterrupts(0x100000U);
            break;
        case 1:
            __OSMaskInterrupts(0x20000U);
            break;
        }
    }
    OSRestoreInterrupts(enabled);
    return 1;
}
