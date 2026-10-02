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
extern u32 __OSUnmaskInterrupts(u32 mask);
extern u32 EXIClearInterrupts(s32 chan, int exi, int tc, int ext);

#pragma scheduling off

int EXIDma(s32 chan, void* buf, s32 len, u32 type, EXICallback callback)
{
    EXIControl* exi;
    int enabled;

    exi = &Ecb[chan];
    enabled = OSDisableInterrupts();
    if ((exi->state & 3) || !(exi->state & 4)) {
        OSRestoreInterrupts(enabled);
        return 0;
    }
    exi->tcCallback = callback;
    if (exi->tcCallback) {
        EXIClearInterrupts(chan, 0, 1, 0);
        __OSUnmaskInterrupts(0x200000U >> (chan * 3));
    }
    exi->state |= 1;
    __EXIRegs[chan * 5 + 1] = (u32)buf & 0x03FFFFE0;
    __EXIRegs[chan * 5 + 2] = len;
    __EXIRegs[chan * 5 + 3] = (type * 4) | 3;
    OSRestoreInterrupts(enabled);
    return 1;
}
