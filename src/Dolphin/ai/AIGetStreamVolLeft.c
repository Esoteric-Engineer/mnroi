typedef unsigned char u8;
typedef unsigned long u32;

volatile u32 __AIRegs[8] : 0xCC006C00;

u8 AIGetStreamVolLeft(void)
{
    return (u8)__AIRegs[1];
}
