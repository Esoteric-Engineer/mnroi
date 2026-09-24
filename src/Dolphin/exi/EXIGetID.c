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
extern u32 IDSerialPort1;

s32 __gUnknown800030C0[2] : 0x800030C0;

extern int OSDisableInterrupts(void);
extern int OSRestoreInterrupts(int enabled);
extern u32 __OSMaskInterrupts(u32 mask);
extern u32 __OSUnmaskInterrupts(u32 mask);
extern int __EXIProbe(s32 chan);
extern u32 EXIClearInterrupts(s32 chan, int exi, int tc, int ext);
extern int EXILock(s32 chan, u32 dev, EXICallback unlockedCallback);
extern int EXISelect(s32 chan, u32 dev, u32 freq);
extern int EXIImm(s32 chan, void* buf, s32 len, u32 type, EXICallback callback);
extern int EXISync(s32 chan);
extern int EXIDeselect(s32 chan);
extern void SetExiInterruptMask(s32 chan, EXIControl* exi);
extern void* memmove(void* dst, const void* src, u32 n);
extern void UnlockedHandler(s32 chan, void* context);

#pragma scheduling off

static inline int __EXIAttach(s32 chan, EXICallback extCallback)
{
    EXIControl* exi;
    int enabled;

    exi = &Ecb[chan];
    enabled = OSDisableInterrupts();
    if ((exi->state & 8) || !__EXIProbe(chan)) {
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

static inline int EXIUnlock(s32 chan)
{
    EXIControl* exi;
    int enabled;
    EXICallback unlockedCallback;

    exi = &Ecb[chan];
    enabled = OSDisableInterrupts();
    if (!(exi->state & 0x10)) {
        OSRestoreInterrupts(enabled);
        return 0;
    }
    exi->state &= ~0x10;
    SetExiInterruptMask(chan, exi);
    if (exi->items > 0) {
        unlockedCallback = exi->queue[0].callback;
        if (--exi->items > 0) {
            memmove(&exi->queue[0], &exi->queue[1], exi->items * 8);
        }
        unlockedCallback(chan, 0);
    }
    OSRestoreInterrupts(enabled);
    return 1;
}

static inline int EXIDetach(s32 chan)
{
    EXIControl* exi;
    int enabled;

    exi = &Ecb[chan];
    enabled = OSDisableInterrupts();
    if (!(exi->state & 8)) {
        OSRestoreInterrupts(enabled);
        return 1;
    }
    if ((exi->state & 0x10) && exi->dev == 0) {
        OSRestoreInterrupts(enabled);
        return 0;
    }
    exi->state &= ~8;
    __OSMaskInterrupts(0x500000U >> (chan * 3));
    OSRestoreInterrupts(enabled);
    return 1;
}

s32 EXIGetID(s32 chan, u32 dev, u32* id)
{
    EXIControl* exi = &Ecb[chan];
    int err;
    u32 cmd;
    s32 startTime;
    int enabled;

    if (chan == 0 && dev == 2 && IDSerialPort1 != 0) {
        *id = IDSerialPort1;
        return 1;
    }

    if (chan < 2 && dev == 0) {
        if (__EXIProbe(chan) == 0) {
            return 0;
        }

        if (exi->idTime == __gUnknown800030C0[chan]) {
            *id = exi->id;
            return exi->idTime;
        }

        if (!__EXIAttach(chan, 0)) {
            return 0;
        }

        startTime = __gUnknown800030C0[chan];
    }

    enabled = OSDisableInterrupts();
    err = !EXILock(chan, dev, (chan < 2 && dev == 0) ? UnlockedHandler : 0);
    if (err == 0) {
        err = !EXISelect(chan, dev, 0);
        if (err == 0) {
            cmd = 0;
            err |= !EXIImm(chan, &cmd, 2, 1, 0);
            err |= !EXISync(chan);
            err |= !EXIImm(chan, id, 4, 0, 0);
            err |= !EXISync(chan);
            err |= !EXIDeselect(chan);
        }

        EXIUnlock(chan);
    }
    OSRestoreInterrupts(enabled);

    if (chan < 2 && dev == 0) {
        EXIDetach(chan);
        enabled = OSDisableInterrupts();
        err |= __gUnknown800030C0[chan] != startTime;

        if (!err) {
            exi->id = *id;
            exi->idTime = startTime;
        }

        OSRestoreInterrupts(enabled);

        if (err) {
            return 0;
        }

        return exi->idTime;
    }

    if (err) {
        return 0;
    }

    return 1;
}
