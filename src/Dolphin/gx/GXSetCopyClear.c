typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned long u32;

// Real Dolphin SDK global GX state (gx). Only the fields this function touches are declared. The rest is padding to keep their offsets correct.
typedef struct {
    u8 pad0[2];
    u16 bpSentNot;
} __GXDataStruct;

extern __GXDataStruct* const __GXData;

typedef struct {
    u8 r, g, b, a;
} GXColor;

typedef union {
    volatile u8 u8;
    volatile u16 u16;
    volatile u32 u32;
} GXFifoObj;

volatile GXFifoObj GXWGFifo : 0xCC008000;

#define SET_REG_FIELD(reg, size, shift, val)               \
    (reg) = (u32)__rlwimi((int)(reg), (int)(val), (shift), \
                          (32 - (shift) - (size)), (31 - (shift)))

void GXSetCopyClear(GXColor clear_clr, u32 clear_z)
{
    u32 reg;

    reg = 0;
    SET_REG_FIELD(reg, 8, 0, clear_clr.r);
    SET_REG_FIELD(reg, 8, 8, clear_clr.a);
    SET_REG_FIELD(reg, 8, 24, 0x4F);
    GXWGFifo.u8 = 0x61;
    GXWGFifo.u32 = reg;

    reg = 0;
    SET_REG_FIELD(reg, 8, 0, clear_clr.b);
    SET_REG_FIELD(reg, 8, 8, clear_clr.g);
    SET_REG_FIELD(reg, 8, 24, 0x50);
    GXWGFifo.u8 = 0x61;
    GXWGFifo.u32 = reg;

    reg = 0;
    SET_REG_FIELD(reg, 24, 0, clear_z);
    SET_REG_FIELD(reg, 8, 24, 0x51);
    GXWGFifo.u8 = 0x61;
    GXWGFifo.u32 = reg;
    __GXData->bpSentNot = 0;
}
