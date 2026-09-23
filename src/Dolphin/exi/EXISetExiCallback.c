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
extern void fn_80193E54(s32 chan, EXIControl* exi);

#pragma scheduling off

EXICallback EXISetExiCallback(s32 chan, EXICallback exiCallback)
{
    EXIControl* exi;
    EXICallback prev;
    int enabled;

    exi = &lbl_8057DBE0[chan];
    enabled = OSDisableInterrupts();
    prev = exi->exiCallback;
    exi->exiCallback = exiCallback;
    if (chan != 2) {
        fn_80193E54(chan, exi);
    } else {
        fn_80193E54(0, &lbl_8057DBE0[0]);
    }
    OSRestoreInterrupts(enabled);
    return prev;
}
