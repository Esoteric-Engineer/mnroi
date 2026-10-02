typedef unsigned long u32;
typedef short s16;
typedef struct OSContext OSContext;

extern void __OSMaskInterrupts(u32 mask);
extern void __OSUnmaskInterrupts(u32 mask);
extern void __OSSetInterruptHandler(s16 interrupt, void* handler);
extern void DBGHandler(int interrupt, void* context);
extern void MWCallback(u32 interrupt, OSContext* context);
extern void (*lbl_8066F4C4)(s16 interrupt, void* context);

void DBInitInterrupts(void)
{
    __OSMaskInterrupts(0x18000);
    __OSMaskInterrupts(0x40);
    lbl_8066F4C4 = (void (*)(s16, void*))MWCallback;
    __OSSetInterruptHandler(0x19, DBGHandler);
    __OSUnmaskInterrupts(0x40);
}
