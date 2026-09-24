typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned long u32;

typedef union {
    volatile u8 u8;
    volatile u32 u32;
} GXFifoObj;

// Real Dolphin SDK global GX state (gx). Only the fields this function touches are declared. The rest is padding to keep their offsets correct.
typedef struct {
    u8 pad0[2];
    u16 bpSentNot;
    u8 pad1[0x14 - 4];
    u32 vcdLo;
    u32 vcdHi;
    u8 pad2[0x4D4 - 0x1C];
    u8 hasNrms;
    u8 hasBiNrms;
} __GXDataStruct;

extern __GXDataStruct* const __GXData;

volatile GXFifoObj GXWGFifo : 0xCC008000;

extern int __cntlzw(unsigned int);

// The SDK macro: the (int) cast is what keeps the vcdHi clrlwi in place.
#define GET_REG_FIELD(reg, size, shift) ((int)((reg) >> (shift)) & ((1 << (size)) - 1))

static inline void __GXXfVtxSpecs(void)
{
    u32 nCols;
    u32 nNrm;
    u32 nTex;
    u32 reg;

    nNrm = __GXData->hasBiNrms ? 2 : __GXData->hasNrms ? 1 : 0;
    nCols = GET_REG_FIELD(__GXData->vcdLo, 4, 13);
    nCols = (u32)(33 - __cntlzw(nCols)) / 2;
    nTex = GET_REG_FIELD(__GXData->vcdHi, 16, 0);
    nTex = (u32)(33 - __cntlzw(nTex)) / 2;
    reg = (nCols) | (nNrm << 2) | (nTex << 4);
    GXWGFifo.u8 = 0x10;
    GXWGFifo.u32 = 0x1008;
    GXWGFifo.u32 = reg;
    __GXData->bpSentNot = 1;
}

void __GXSetVCD(void)
{
    GXWGFifo.u8 = 8;
    GXWGFifo.u8 = 0x50;
    GXWGFifo.u32 = __GXData->vcdLo;
    GXWGFifo.u8 = 8;
    GXWGFifo.u8 = 0x60;
    GXWGFifo.u32 = __GXData->vcdHi;
    __GXXfVtxSpecs();
}
