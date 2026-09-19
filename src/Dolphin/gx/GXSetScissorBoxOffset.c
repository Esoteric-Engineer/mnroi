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

#define GXWGFifo (*(GXFifoObj*)0xCC008000)

#define SET_REG_FIELD(reg, size, shift, val)               \
    (reg) = (u32)__rlwimi((int)(reg), (int)(val), (shift), \
                          (32 - (shift) - (size)), (31 - (shift)))

void GXSetScissorBoxOffset(s32 x_off, s32 y_off)
{
    __GXDataStruct* gx = __GXData;
    u32 reg = 0;
    u32 hx = x_off + 342;
    u32 hy = (u32)(y_off + 342) >> 1;

    SET_REG_FIELD(reg, 10, 0, hx >> 1);
    SET_REG_FIELD(reg, 10, 10, hy);
    SET_REG_FIELD(reg, 8, 24, 0x59);
    GXWGFifo.u8 = 0x61;
    GXWGFifo.u32 = reg;
    gx->bpSentNot = 0;
}
