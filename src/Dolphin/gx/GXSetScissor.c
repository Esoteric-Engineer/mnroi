typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned long u32;

// Only the fields this function touches are declared; the rest is padding.
typedef struct {
    u8 pad0[2];
    u16 bpSentNot;
    u8 pad1[0xF4];
    u32 suScis0;
    u32 suScis1;
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

void GXSetScissor(u32 left, u32 top, u32 wd, u32 ht)
{
    __GXDataStruct* gx = __GXData;
    u32 tp, lf, bm, rt;

    tp = top + 342;
    lf = left + 342;
    bm = tp + ht - 1;
    rt = lf + wd - 1;

    SET_REG_FIELD(gx->suScis0, 11, 0, tp);
    SET_REG_FIELD(gx->suScis0, 11, 12, lf);
    SET_REG_FIELD(gx->suScis1, 11, 0, bm);
    SET_REG_FIELD(gx->suScis1, 11, 12, rt);

    GXWGFifo.u8 = 0x61;
    GXWGFifo.u32 = gx->suScis0;
    GXWGFifo.u8 = 0x61;
    GXWGFifo.u32 = gx->suScis1;
    gx->bpSentNot = 0;
}
