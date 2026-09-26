typedef unsigned short u16;
typedef unsigned int u32;
typedef void (*ARCallback)(void);

typedef struct OSContext OSContext;

extern void OSClearContext(OSContext* context);
extern void OSSetCurrentContext(OSContext* context);

extern ARCallback lbl_8066F9B8;

volatile u16 __DSPRegs[0x200] : 0xCC005000;

void __ARHandler(int exception, OSContext* context)
{
    long long exceptionContext[0x2c8 / 8];
    u16 tmp;

    tmp = __DSPRegs[5];
    tmp = (tmp & ~0x88) | 0x20;
    __DSPRegs[5] = tmp;
    OSClearContext((OSContext*)exceptionContext);
    OSSetCurrentContext((OSContext*)exceptionContext);
    if (lbl_8066F9B8) {
        lbl_8066F9B8();
    }
    OSClearContext((OSContext*)exceptionContext);
    OSSetCurrentContext(context);
}
