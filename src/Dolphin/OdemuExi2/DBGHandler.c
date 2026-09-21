typedef unsigned long u32;
typedef short s16;

volatile u32 __PIRegs[12] : 0xCC003000;

extern void (*lbl_8066F4C4)(s16 interrupt, void* context);

void DBGHandler(int interrupt, void* context)
{
    __PIRegs[0] = 0x1000;
    if (lbl_8066F4C4) {
        lbl_8066F4C4(interrupt, context);
    }
}
