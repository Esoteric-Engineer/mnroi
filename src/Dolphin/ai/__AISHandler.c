typedef unsigned char u8;
typedef unsigned long u32;

volatile u32 __AIRegs[8] : 0xCC006C00;

extern void (*lbl_8066F408)(u32);

extern void lbl_8017C728(void* context);
extern void fn_8017C530(void* context);

void __AISHandler(u32 interrupt, void* context)
{
    u8 exceptionContext[0x2C8];

    __AIRegs[0] |= 8;
    lbl_8017C728(exceptionContext);
    fn_8017C530(exceptionContext);
    if (lbl_8066F408) {
        lbl_8066F408(__AIRegs[2]);
    }
    lbl_8017C728(exceptionContext);
    fn_8017C530(context);
}
