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
volatile u32 __EXIRegs[0x40] : 0xCC006800;

extern u32 __OSMaskInterrupts(u32 mask);
extern void OSClearContext(OSContext* context);
extern OSContext* OSSetCurrentContext(OSContext* context);

static inline u32 EXIClearInterruptsI(s32 chan, int exi, int tc, int ext)
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

static inline void CompleteTransferI(s32 chan)
{
    EXIControl* exi = &Ecb[chan];
    unsigned char* buf;
    u32 data;
    int i;
    int len;

    if (exi->state & 3) {
        if (exi->state & 2) {
            if ((len = exi->immLen) != 0) {
                buf = exi->immBuf;
                data = __EXIRegs[chan * 5 + 4];
                for (i = 0; i < len; i++) {
                    *buf++ = data >> ((3 - i) * 8);
                }
            }
        }
        exi->state &= ~3;
    }
}

#pragma scheduling off

void TCIntrruptHandler(short interrupt, OSContext* context)
{
    s32 chan;
    EXIControl* exi;
    EXICallback callback;

    chan = (interrupt - 10) / 3;
    exi = &Ecb[chan];
    __OSMaskInterrupts(0x80000000U >> interrupt);
    EXIClearInterruptsI(chan, 0, 1, 0);
    callback = exi->tcCallback;
    if (callback) {
        long long exceptionContext[0x2c8 / 8];

        exi->tcCallback = 0;
        CompleteTransferI(chan);
        OSClearContext((OSContext*)exceptionContext);
        OSSetCurrentContext((OSContext*)exceptionContext);
        callback(chan, context);
        OSClearContext((OSContext*)exceptionContext);
        OSSetCurrentContext(context);
    }
}
