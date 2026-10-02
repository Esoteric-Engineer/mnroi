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

#pragma scheduling off

EXICallback EXISetExiCallback(s32 chan, EXICallback exiCallback)
{
    EXIControl* exi;
    EXICallback prev;
    int enabled;

    exi = &Ecb[chan];
    enabled = OSDisableInterrupts();
    prev = exi->exiCallback;
    exi->exiCallback = exiCallback;
    if (chan != 2) {
        SetExiInterruptMask(chan, exi);
    } else {
        SetExiInterruptMask(0, &Ecb[0]);
    }
    OSRestoreInterrupts(enabled);
    return prev;
}
