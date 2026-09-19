typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned long u32;

// Real Dolphin SDK global GX state (gx). Only the fields this function touches are declared. The rest is padding to keep their offsets correct.
typedef struct {
    u8 pad0[2];
    u16 bpSentNot;
} __GXDataStruct;

extern __GXDataStruct* __GXData;

typedef struct {
    u8 r, g, b, a;
} GXColor;

typedef union {
    volatile u8 u8;
    volatile u16 u16;
    volatile u32 u32;
} GXFifoObj;

#define GXWGFifo (*(GXFifoObj*)0xCC008000)

#define SET_REG_FIELD(reg, size, shift, val)               \
    (reg) = (u32)__rlwimi((int)(reg), (int)(val), (shift), \
                          (32 - (shift) - (size)), (31 - (shift)))

void GXSetTevKColor(u32 id, GXColor color)
{
    __GXDataStruct* gx = __GXData;
    u32 regRA;
    u32 regBG;

    regRA = (224 + id * 2) << 24;
    SET_REG_FIELD(regRA, 8, 0, *(u32*)&color >> 24);
    SET_REG_FIELD(regRA, 8, 12, *(u32*)&color);
    SET_REG_FIELD(regRA, 4, 20, 8);

    regBG = (225 + id * 2) << 24;
    SET_REG_FIELD(regBG, 8, 0, *(u32*)&color >> 8);
    SET_REG_FIELD(regBG, 8, 12, *(u32*)&color >> 16);
    SET_REG_FIELD(regBG, 4, 20, 8);

    GXWGFifo.u8 = 0x61;
    GXWGFifo.u32 = regRA;
    GXWGFifo.u8 = 0x61;
    GXWGFifo.u32 = regBG;
    gx->bpSentNot = 0;
}
