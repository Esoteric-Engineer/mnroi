typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned long u32;

extern volatile u16* __peReg;

#define SET_REG_FIELD(reg, size, shift, val)               \
    (reg) = (u32)__rlwimi((int)(reg), (int)(val), (shift), \
                          (32 - (shift) - (size)), (31 - (shift)))

void GXPokeAlphaRead(u32 mode)
{
    u32 reg;

    reg = 0;
    SET_REG_FIELD(reg, 2, 0, mode);
    SET_REG_FIELD(reg, 1, 2, 1);
    __peReg[4] = reg;
}
