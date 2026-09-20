typedef unsigned char u8;
typedef unsigned long u32;

typedef union {
    volatile u8 u8;
    volatile u32 u32;
} GXFifoObj;

#define GXWGFifo (*(GXFifoObj*)0xCC008000)

// Real Dolphin SDK global GX state (gx). Only the fields this function touches are declared; the rest is padding to keep their offsets correct.
typedef struct {
    u8 pad0[0x204];
    u32 genMode;
} __GXDataStruct;

extern __GXDataStruct* __GXData;

#define SET_REG_FIELD(reg, size, shift, val)               \
    (reg) = (u32)__rlwimi((int)(reg), (int)(val), (shift), \
                          (32 - (shift) - (size)), (31 - (shift)))

void GXSetCoPlanar(u32 enable)
{
    __GXDataStruct* gx = __GXData;
    u32 reg;

    SET_REG_FIELD(gx->genMode, 1, 19, enable);
    reg = 0xFE080000;
    GXWGFifo.u8 = 0x61;
    GXWGFifo.u32 = reg;
    GXWGFifo.u8 = 0x61;
    GXWGFifo.u32 = gx->genMode;
}
