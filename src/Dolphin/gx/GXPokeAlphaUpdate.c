typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned long u32;

extern volatile u16* __peReg;

#define SET_REG_FIELD(reg, size, shift, val)               \
    (reg) = (u32)__rlwimi((int)(reg), (int)(val), (shift), \
                          (32 - (shift) - (size)), (31 - (shift)))

void GXPokeAlphaUpdate(u8 update_enable)
{
    u32 reg;

    reg = __peReg[1];
    SET_REG_FIELD(reg, 1, 4, update_enable);
    __peReg[1] = reg;
}
