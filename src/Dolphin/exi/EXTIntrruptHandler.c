typedef unsigned long u32;
typedef long s32;
typedef struct OSContext OSContext;
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

extern u32 __OSMaskInterrupts(u32 mask);
extern void OSClearContext(OSContext* context);
extern OSContext* OSSetCurrentContext(OSContext* context);

#pragma scheduling off

void EXTIntrruptHandler(short interrupt, OSContext* context)
{
    s32 chan;
    EXIControl* exi;
    EXICallback callback;

    chan = (interrupt - 11) / 3;
    __OSMaskInterrupts(0x500000U >> (chan * 3));
    exi = &Ecb[chan];
    callback = exi->extCallback;
    exi->state &= ~8;
    if (callback) {
        long long exceptionContext[0x2c8 / 8];

        OSClearContext((OSContext*)exceptionContext);
        OSSetCurrentContext((OSContext*)exceptionContext);
        exi->extCallback = 0;
        callback(chan, context);
        OSClearContext((OSContext*)exceptionContext);
        OSSetCurrentContext(context);
    }
}
