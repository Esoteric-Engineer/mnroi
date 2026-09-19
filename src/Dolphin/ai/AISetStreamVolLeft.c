typedef unsigned char u8;
typedef unsigned long u32;

volatile u32 __AIRegs[8] : 0xCC006C00;

void AISetStreamVolLeft(u32 vol)
{
    u32 reg = __AIRegs[1];
    reg = (u32)__rlwimi((int)(reg & 0xFFFFFF00), (int)vol, 0, 24, 31);
    __AIRegs[1] = reg;
}
