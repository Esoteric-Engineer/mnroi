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

s32 __gUnknown800030C0[2] : 0x800030C0;

extern int __EXIProbe(s32 chan);
extern s32 EXIGetID(s32 chan, u32 dev, u32* id);

#pragma scheduling off

static inline int EXIProbe(s32 chan)
{
    EXIControl* exi = &Ecb[chan];
    int rc;
    u32 id;

    rc = __EXIProbe(chan);
    if (rc && !exi->idTime) {
        rc = EXIGetID(chan, 0, &id) ? 1 : 0;
    }
    return rc;
}

s32 EXIProbeEx(s32 chan)
{
    if (EXIProbe(chan)) {
        return 1;
    }
    if (__gUnknown800030C0[chan]) {
        return 0;
    }
    return -1;
}
