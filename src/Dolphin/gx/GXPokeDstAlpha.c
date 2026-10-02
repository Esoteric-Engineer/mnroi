typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned long u32;

extern volatile u16* __peReg;

#define SET_REG_FIELD(reg, size, shift, val)               \
    (reg) = (u32)__rlwimi((int)(reg), (int)(val), (shift), \
                          (32 - (shift) - (size)), (31 - (shift)))

void GXPokeDstAlpha(u8 enable, u8 alpha)
{
    u32 reg = 0;

    SET_REG_FIELD(reg, 8, 0, alpha);
    SET_REG_FIELD(reg, 1, 8, enable);
    __peReg[2] = reg;
}
