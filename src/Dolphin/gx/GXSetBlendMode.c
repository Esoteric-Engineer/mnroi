typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned long u32;

// Real Dolphin SDK global GX state (gx). Only the fields this function touches are declared. The rest is padding to keep their offsets correct.
typedef struct {
    u8 pad0[2];
    u16 bpSentNot;
    u8 pad1[0x1CC];
    u32 cmode0;
} __GXDataStruct;

extern __GXDataStruct* __GXData;

typedef union {
    volatile u8 u8;
    volatile u16 u16;
    volatile u32 u32;
} GXFifoObj;

#define GXWGFifo (*(GXFifoObj*)0xCC008000)

#define SET_REG_FIELD(reg, size, shift, val)               \
    (reg) = (u32)__rlwimi((int)(reg), (int)(val), (shift), \
                          (32 - (shift) - (size)), (31 - (shift)))

void GXSetBlendMode(u32 type, u32 src_factor, u32 dst_factor, u32 op)
{
    __GXDataStruct* gx = __GXData;
    u32 reg = gx->cmode0;

    SET_REG_FIELD(reg, 1, 11, type == 3);
    SET_REG_FIELD(reg, 1, 0, type);
    SET_REG_FIELD(reg, 1, 1, type == 2);
    SET_REG_FIELD(reg, 4, 12, op);
    SET_REG_FIELD(reg, 3, 8, src_factor);
    SET_REG_FIELD(reg, 3, 5, dst_factor);
    GXWGFifo.u8 = 0x61;
    GXWGFifo.u32 = reg;
    gx->cmode0 = reg;
    gx->bpSentNot = 0;
}
