typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned long u32;
typedef signed long s32;

typedef struct {
    u8 pad0[2];
    u16 bpSentNot;
} __GXDataStruct;

extern __GXDataStruct* __GXData;

typedef union {
    volatile u8 u8;
    volatile u32 u32;
} GXFifoObj;

volatile GXFifoObj GXWGFifo : 0xCC008000;

#define SET_REG_FIELD(reg, size, shift, val)               \
    (reg) = (u32)__rlwimi((int)(reg), (int)(val), (shift), \
                          (32 - (shift) - (size)), (31 - (shift)))

void GXSetScissorBoxOffset(s32 x_off, s32 y_off)
{
    u32 reg = 0;
    u32 x;
    u32 y;

    x = (u32)(x_off + 342);
    y = (u32)(y_off + 342);
    SET_REG_FIELD(reg, 10, 0, x >> 1);
    SET_REG_FIELD(reg, 10, 10, y >> 1);
    SET_REG_FIELD(reg, 8, 24, 0x59);

    GXWGFifo.u8 = 0x61;
    GXWGFifo.u32 = reg;
    __GXData->bpSentNot = 0;
}
