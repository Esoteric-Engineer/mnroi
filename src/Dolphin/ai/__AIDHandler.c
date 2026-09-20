typedef unsigned short u16;
typedef unsigned char u8;
typedef unsigned long u32;

volatile u16 __DSPRegs[0x20] : 0xCC005000;

extern void (*lbl_8066F40C)(void);
extern void* lbl_8066F410;
extern int lbl_8066F41C;

extern void OSClearContext(void* context);
extern void OSSetCurrentContext(void* context);
extern void __AICallbackStackSwitch(void (*cb)(void));

void __AIDHandler(u32 interrupt, void* context)
{
    u8 exceptionContext[0x2C8];
    u16 tmp;

    tmp = __DSPRegs[5];
    tmp = (tmp & ~0xA0) | 8;
    __DSPRegs[5] = tmp;
    OSClearContext(exceptionContext);
    OSSetCurrentContext(exceptionContext);
    if (lbl_8066F40C) {
        if (lbl_8066F41C == 0) {
            lbl_8066F41C = 1;
            if (lbl_8066F410) {
                __AICallbackStackSwitch(lbl_8066F40C);
            } else {
                lbl_8066F40C();
            }
            lbl_8066F41C = 0;
        }
    }
    OSClearContext(exceptionContext);
    OSSetCurrentContext(context);
}
