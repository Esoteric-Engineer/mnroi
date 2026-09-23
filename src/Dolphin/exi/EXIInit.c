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
volatile u32 __gUnknown800030C0[2] : 0x800030C0;

extern u32 IDSerialPort1;
extern int __OSInIPL;
extern char* __EXIVersion;

extern u32 __OSMaskInterrupts(u32 mask);
extern void __OSSetInterruptHandler(short interrupt, void (*handler)(short, OSContext*));
extern void OSRegisterVersion(char* version);
extern int __EXIProbe(s32 chan);
extern s32 EXIGetID(s32 chan, u32 dev, u32* id);
extern void __OSEnableBarnacle(s32 chan, u32 dev);
extern void EXIIntrruptHandler(short interrupt, OSContext* context);
extern void TCIntrruptHandler(short interrupt, OSContext* context);
extern void EXTIntrruptHandler(short interrupt, OSContext* context);

#pragma scheduling off

void EXIInit(void)
{
    u32 id;

    while (((__EXIRegs[3] & 1) == 1) || ((__EXIRegs[8] & 1) == 1) || ((__EXIRegs[13] & 1) == 1)) {
    }
    __OSMaskInterrupts(0x7F8000U);
    __EXIRegs[0] = 0;
    __EXIRegs[5] = 0;
    __EXIRegs[10] = 0;
    __EXIRegs[0] = 0x2000;
    __OSSetInterruptHandler(9, EXIIntrruptHandler);
    __OSSetInterruptHandler(10, TCIntrruptHandler);
    __OSSetInterruptHandler(11, EXTIntrruptHandler);
    __OSSetInterruptHandler(12, EXIIntrruptHandler);
    __OSSetInterruptHandler(13, TCIntrruptHandler);
    __OSSetInterruptHandler(14, EXTIntrruptHandler);
    __OSSetInterruptHandler(15, EXIIntrruptHandler);
    __OSSetInterruptHandler(16, TCIntrruptHandler);
    EXIGetID(0, 2, &IDSerialPort1);
    if (__OSInIPL) {
        __gUnknown800030C0[0] = __gUnknown800030C0[1] = 0;
        Ecb[0].idTime = Ecb[1].idTime = 0;
        __EXIProbe(0);
        __EXIProbe(1);
    } else if (EXIGetID(0, 0, &id) && id == 0x07010000) {
        __OSEnableBarnacle(1, 0);
    } else if (EXIGetID(1, 0, &id) && id == 0x07010000) {
        __OSEnableBarnacle(0, 2);
    }
    OSRegisterVersion(__EXIVersion);
}
