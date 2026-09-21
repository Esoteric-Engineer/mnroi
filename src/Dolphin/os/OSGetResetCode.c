typedef unsigned long u32;

extern int lbl_8057C550[8];
volatile u32 __PIRegs[0x100] : 0xCC003000;

#pragma peephole off
u32 OSGetResetCode(void)
{
    if (lbl_8057C550[0] != 0) {
        return lbl_8057C550[1] | 0x80000000;
    }
    return (__PIRegs[9] & ~7) >> 3;
}
