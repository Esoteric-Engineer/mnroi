typedef unsigned long u32;
typedef long s32;
typedef long long s64;
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
s32 __gUnknown800030C0[2] : 0x800030C0;
u32 __OSBusClock : 0x800000F8;

extern int OSDisableInterrupts(void);
extern int OSRestoreInterrupts(int enabled);
extern s64 OSGetTime(void);

#pragma scheduling off

static inline u32 EXIClearInterrupts(s32 chan, int exi, int tc, int ext)
{
    u32 cpr;
    u32 prev;

    cpr = prev = __EXIRegs[chan * 5];
    prev &= 0x7F5;
    if (exi != 0) {
        prev |= 2;
    }
    if (tc != 0) {
        prev |= 8;
    }
    if (ext != 0) {
        prev |= 0x800;
    }
    __EXIRegs[chan * 5] = prev;
    return cpr;
}

int __EXIProbe(s32 chan)
{
    EXIControl* exi;
    int enabled;
    int rc;
    u32 cpr;
    s32 t;

    exi = &Ecb[chan];
    if (chan == 2) {
        return 1;
    }
    rc = 1;
    enabled = OSDisableInterrupts();
    cpr = __EXIRegs[chan * 5];
    if (!(exi->state & 8)) {
        if (cpr & 0x800) {
            EXIClearInterrupts(chan, 0, 0, 1);
            __gUnknown800030C0[chan] = exi->idTime = 0;
        }
        if (cpr & 0x1000) {
            t = (s32)((OSGetTime() / (__OSBusClock / 4 / 1000)) / 100) + 1;
            if (__gUnknown800030C0[chan] == 0) {
                __gUnknown800030C0[chan] = t;
            }
            if (t - __gUnknown800030C0[chan] < 3) {
                rc = 0;
            }
        } else {
            __gUnknown800030C0[chan] = exi->idTime = 0;
            rc = 0;
        }
    } else if (!(cpr & 0x1000) || (cpr & 0x800)) {
        __gUnknown800030C0[chan] = exi->idTime = 0;
        rc = 0;
    }
    OSRestoreInterrupts(enabled);
    return rc;
}
