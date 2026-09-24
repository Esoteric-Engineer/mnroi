typedef unsigned short u16;
typedef unsigned int u32;

volatile u16 __DSPRegs[0x200] : 0xCC005000;

void __ARClearInterrupt(void)
{
    u16 tmp;
    tmp = __DSPRegs[5];
    tmp = tmp & ~0x88 | 0x20;
    __DSPRegs[5] = tmp;
}
