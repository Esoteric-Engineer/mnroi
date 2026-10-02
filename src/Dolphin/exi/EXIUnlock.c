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

extern int OSDisableInterrupts(void);
extern int OSRestoreInterrupts(int enabled);
extern void SetExiInterruptMask(s32 chan, EXIControl* exi);
extern void* memmove(void* dst, const void* src, u32 n);

#pragma scheduling off

int EXIUnlock(s32 chan)
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
