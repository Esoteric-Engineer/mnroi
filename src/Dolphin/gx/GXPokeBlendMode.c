typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned long u32;

extern volatile u16* __peReg;

#define SET_REG_FIELD(reg, size, shift, val)               \
    (reg) = (u32)__rlwimi((int)(reg), (int)(val), (shift), \
                          (32 - (shift) - (size)), (31 - (shift)))

void GXPokeBlendMode(int type, u32 src_factor, u32 dst_factor, u32 op)
{
    u32 reg;

    reg = __peReg[1];
    SET_REG_FIELD(reg, 1, 0, (type == 1) || (type == 3));
    SET_REG_FIELD(reg, 1, 11, (type == 3));
    SET_REG_FIELD(reg, 1, 1, (type == 2));
    SET_REG_FIELD(reg, 4, 12, op);
    SET_REG_FIELD(reg, 3, 8, src_factor);
    SET_REG_FIELD(reg, 3, 5, dst_factor);
    SET_REG_FIELD(reg, 8, 24, 0x41);
    __peReg[1] = reg;
}
