typedef unsigned char u8;
typedef unsigned long u32;

volatile u32 __AIRegs[8] : 0xCC006C00;

void AISetStreamVolRight(u32 vol)
{
    u32 reg = __AIRegs[1];
    reg = (u32)__rlwimi((int)(reg & 0xFFFF00FF), (int)vol, 8, 16, 23);
    __AIRegs[1] = reg;
}
