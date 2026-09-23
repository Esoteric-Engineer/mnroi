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
extern u32 __OSMaskInterrupts(u32 mask);

#pragma scheduling off

int EXIDetach(s32 chan)
{
    EXIControl* exi;
    int enabled;

    exi = &lbl_8057DBE0[chan];
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
