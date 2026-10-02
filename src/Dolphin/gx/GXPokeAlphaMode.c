typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned long u32;

extern volatile u16* __peReg;

void GXPokeAlphaMode(u32 func, u8 threshold)
{
    u32 reg;

    reg = (func << 8) | threshold;
    __peReg[3] = reg;
}
