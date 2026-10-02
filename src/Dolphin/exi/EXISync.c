typedef unsigned long u32;
typedef long s32;
typedef unsigned char u8;
typedef unsigned short u16;
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
volatile u16 __OSDeviceCode : 0x800030E6;

extern int OSDisableInterrupts(void);
extern int OSRestoreInterrupts(int enabled);
extern u32 __OSGetDIConfig(void);
extern u32 OSGetConsoleType(void);

#pragma scheduling off

static inline void CompleteTransfer(s32 chan)
{
    EXIControl* exi;
    u8* buf;
    u32 data;
    int i;
    int len;

    exi = &Ecb[chan];
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

int EXISync(s32 chan)
{
    EXIControl* exi;
    int rc;
    int enabled;

    exi = &Ecb[chan];
    rc = 0;
    while ((exi->state & 4)) {
        if (!(__EXIRegs[chan * 5 + 3] & 1)) {
            enabled = OSDisableInterrupts();
            if (exi->state & 4) {
                CompleteTransfer(chan);
                if (__OSGetDIConfig() != 0xFF || (OSGetConsoleType() & 0xF0000000) == 0x20000000 ||
                    (exi->immLen != 4 || (__EXIRegs[chan * 5] & 0x70) ||
                     (__EXIRegs[chan * 5 + 4] != 0x01010000 && __EXIRegs[chan * 5 + 4] != 0x05070000 &&
                      __EXIRegs[chan * 5 + 4] != 0x04220001)) ||
                    __OSDeviceCode == 0x8200) {
                    rc = 1;
                }
            }
            OSRestoreInterrupts(enabled);
            break;
        }
    }
    return rc;
}
