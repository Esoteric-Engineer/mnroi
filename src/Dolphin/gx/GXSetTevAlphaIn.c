typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned long u32;

// Real Dolphin SDK global GX state (gx). Only the fields this function touches are declared. The rest is padding to keep their offsets correct.
typedef struct {
    u8 pad0[2];
    u16 bpSentNot;
    u8 pad1[0x12C];
    u32 tevc[16];
    u32 teva[16];
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

void GXSetTevAlphaIn(u32 stage, u32 a, u32 b, u32 c, u32 d)
{
    __GXDataStruct* gx = __GXData;
    u32 teva = gx->teva[stage];

    SET_REG_FIELD(teva, 3, 13, a);
    SET_REG_FIELD(teva, 3, 10, b);
    SET_REG_FIELD(teva, 3, 7, c);
    SET_REG_FIELD(teva, 3, 4, d);

    GXWGFifo.u8 = 0x61;
    GXWGFifo.u32 = teva;
    gx->teva[stage] = teva;
    gx->bpSentNot = 0;
}
