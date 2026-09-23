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

extern int OSDisableInterrupts(void);
extern int OSRestoreInterrupts(int enabled);
extern u32 __OSUnmaskInterrupts(u32 mask);
extern int fn_80194640(s32 chan);
extern s32 fn_80195480(s32 chan, u32 dev, u32* id);
extern u32 EXIClearInterrupts(s32 chan, int exi, int tc, int ext);

#pragma scheduling off

static inline int EXIProbe(s32 chan)
{
    EXIControl* exi = &lbl_8057DBE0[chan];
    int rc;
    u32 id;

    rc = fn_80194640(chan);
    if (rc && !exi->idTime) {
        rc = fn_80195480(chan, 0, &id) ? 1 : 0;
    }
    return rc;
}

static int __EXIAttach(s32 chan, EXICallback extCallback)
{
    EXIControl* exi;
    int enabled;

    exi = &lbl_8057DBE0[chan];
    enabled = OSDisableInterrupts();
    if ((exi->state & 8) || !fn_80194640(chan)) {
        OSRestoreInterrupts(enabled);
        return 0;
    }
    EXIClearInterrupts(chan, 1, 0, 0);
    exi->extCallback = extCallback;
    __OSUnmaskInterrupts(0x100000U >> (chan * 3));
    exi->state |= 8;
    OSRestoreInterrupts(enabled);
    return 1;
}

int EXIAttach(s32 chan, EXICallback extCallback)
{
    EXIControl* exi;
    int enabled;
    int rc;

    exi = &lbl_8057DBE0[chan];
    EXIProbe(chan);
    enabled = OSDisableInterrupts();
    if (exi->idTime == 0) {
        OSRestoreInterrupts(enabled);
        return 0;
    }

    rc = __EXIAttach(chan, extCallback);
    OSRestoreInterrupts(enabled);
    return rc;
}
