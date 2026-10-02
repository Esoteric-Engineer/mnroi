#pragma peephole off
typedef unsigned long u32;
typedef unsigned short u16;

volatile u16 __MEMRegs[64] : 0xCC004000;
volatile u16 __DSPRegs[0x20] : 0xCC005000;
volatile u32 __EXIRegs[0x20] : 0xCC006800;
volatile u32 __AIRegs[8] : 0xCC006C00;
volatile u32 __PIRegs[0x20] : 0xCC003000;

u32 SetInterruptMask(u32 mask, u32 current)
{
    u32 reg;

    switch (__cntlzw(mask)) {
    case 0:
    case 1:
    case 2:
    case 3:
    case 4:
        reg = 0;
        if (!(current & 0x80000000))
            reg |= 0x1;
        if (!(current & 0x40000000))
            reg |= 0x2;
        if (!(current & 0x20000000))
            reg |= 0x4;
        if (!(current & 0x10000000))
            reg |= 0x8;
        if (!(current & 0x08000000))
            reg |= 0x10;
        __MEMRegs[14] = (u16)reg;
        mask &= ~0xF8000000;
        break;
    case 5:
    case 6:
    case 7:
        reg = __DSPRegs[5];
        reg &= ~0x1F8;
        if (!(current & 0x04000000))
            reg |= 0x10;
        if (!(current & 0x02000000))
            reg |= 0x40;
        if (!(current & 0x01000000))
            reg |= 0x100;
        __DSPRegs[5] = (u16)reg;
        mask &= ~0x07000000;
        break;
    case 8:
        reg = __AIRegs[0];
        reg &= ~0x2C;
        if (!(current & 0x00800000))
            reg |= 0x4;
        __AIRegs[0] = reg;
        mask &= ~0x00800000;
        break;
    case 9:
    case 10:
    case 11:
        reg = __EXIRegs[0];
        reg &= ~0x2C0F;
        if (!(current & 0x00400000))
            reg |= 0x1;
        if (!(current & 0x00200000))
            reg |= 0x4;
        if (!(current & 0x00100000))
            reg |= 0x400;
        __EXIRegs[0] = reg;
        mask &= ~0x00700000;
        break;
    case 12:
    case 13:
    case 14:
        reg = __EXIRegs[5];
        reg &= ~0xC0F;
        if (!(current & 0x00080000))
            reg |= 0x1;
        if (!(current & 0x00040000))
            reg |= 0x4;
        if (!(current & 0x00020000))
            reg |= 0x400;
        __EXIRegs[5] = reg;
        mask &= ~0x000E0000;
        break;
    case 15:
    case 16:
        reg = __EXIRegs[10];
        reg &= ~0xF;
        if (!(current & 0x00010000))
            reg |= 0x1;
        if (!(current & 0x00008000))
            reg |= 0x4;
        __EXIRegs[10] = reg;
        mask &= ~0x00018000;
        break;
    case 17:
    case 18:
    case 19:
    case 20:
    case 21:
    case 22:
    case 23:
    case 24:
    case 25:
    case 26:
        reg = 0xF0;
        if (!(current & 0x00004000))
            reg |= 0x800;
        if (!(current & 0x00000800))
            reg |= 0x8;
        if (!(current & 0x00000400))
            reg |= 0x4;
        if (!(current & 0x00000200))
            reg |= 0x2;
        if (!(current & 0x00000100))
            reg |= 0x1;
        if (!(current & 0x00000080))
            reg |= 0x100;
        if (!(current & 0x00000040))
            reg |= 0x1000;
        if (!(current & 0x00002000))
            reg |= 0x200;
        if (!(current & 0x00001000))
            reg |= 0x400;
        if (!(current & 0x00000020))
            reg |= 0x2000;
        __PIRegs[1] = reg;
        mask &= ~0x00007FE0;
        break;
    default:
        break;
    }
    return mask;
}
