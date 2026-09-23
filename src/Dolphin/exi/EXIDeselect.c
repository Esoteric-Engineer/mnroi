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

extern EXIControl lbl_8057DBE0[3];
volatile u32 __EXIRegs[0x40] : 0xCC006800;

extern int OSDisableInterrupts(void);
extern int OSRestoreInterrupts(int enabled);
extern u32 __OSUnmaskInterrupts(u32 mask);
extern int fn_80194640(s32 chan);

#pragma scheduling off

int EXIDeselect(s32 chan)
{
    EXIControl* exi;
    u32 cpr;
    int enabled;

    exi = &lbl_8057DBE0[chan];
    enabled = OSDisableInterrupts();
    if (!(exi->state & 4)) {
        OSRestoreInterrupts(enabled);
        return 0;
    }
    exi->state &= ~4;
    cpr = __EXIRegs[chan * 5];
    __EXIRegs[chan * 5] = cpr & 0x405;
    if (exi->state & 8) {
        switch (chan) {
        case 0:
            __OSUnmaskInterrupts(0x100000U);
            break;
        case 1:
            __OSUnmaskInterrupts(0x20000U);
            break;
        }
    }
    OSRestoreInterrupts(enabled);
    if ((chan != 2) && (cpr & 0x80)) {
        if (fn_80194640(chan) != 0) {
            return 1;
        }
        return 0;
    }
    return 1;
}
