typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned long u32;

// Real Dolphin SDK global GX state (gx). Only the fields this function touches are declared. The rest is padding to keep their offsets correct.
typedef struct {
    u8 pad0[2];
    u16 bpSentNot;
    u8 pad1[0x1D8];
    u32 peCtrl;
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

void GXSetZCompLoc(u8 before_tex)
{
    __GXDataStruct* gx = __GXData;

    SET_REG_FIELD(gx->peCtrl, 1, 6, before_tex);
    GXWGFifo.u8 = 0x61;
    GXWGFifo.u32 = gx->peCtrl;
    gx->bpSentNot = 0;
}
