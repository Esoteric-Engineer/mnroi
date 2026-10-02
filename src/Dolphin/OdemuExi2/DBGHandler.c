typedef unsigned long u32;
typedef short s16;
typedef unsigned char u8;
typedef struct OSContext OSContext;

volatile u32 __PIRegs[12] : 0xCC003000;

extern void (*lbl_8066F4C0)(s16 interrupt, OSContext* context);
extern u8 lbl_8066F4D4;
extern void (*lbl_8066F4C4)(s16 interrupt, void* context);

void DBGHandler(int interrupt, void* context)
{
    __PIRegs[0] = 0x1000;
    if (lbl_8066F4C4) {
        lbl_8066F4C4(interrupt, context);
    }
}

void MWCallback(u32 interrupt, OSContext* context)
{
    lbl_8066F4D4 = 1;
    if (lbl_8066F4C0) {
        lbl_8066F4C0(0, context);
    }
}
