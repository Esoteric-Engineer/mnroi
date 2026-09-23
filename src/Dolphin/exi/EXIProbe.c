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

extern int __EXIProbe(s32 chan);
extern s32 fn_80195480(s32 chan, u32 dev, u32* id);

#pragma scheduling off

int EXIProbe(s32 chan)
{
    EXIControl* exi = &lbl_8057DBE0[chan];
    int rc;
    u32 id;

    rc = __EXIProbe(chan);
    if (rc && !exi->idTime) {
        rc = fn_80195480(chan, 0, &id) ? 1 : 0;
    }
    return rc;
}
