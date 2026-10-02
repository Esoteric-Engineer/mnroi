typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned long u32;

typedef union {
    volatile u8 u8;
    volatile u32 u32;
} GXFifoObj;

volatile GXFifoObj GXWGFifo : 0xCC008000;

// Real Dolphin SDK global GX state (gx). Only the fields this function touches are declared. The rest is padding to keep their offsets correct.
typedef struct {
    u8 pad0[0x2];
    u16 bpSentNot;
    u8 pad1[0x7C];
    u32 matIdxA;
    u32 matIdxB;
} __GXDataStruct;

extern __GXDataStruct* __GXData;

void __GXSetMatrixIndex(int index)
{
    __GXDataStruct* gx;
    u32 v;
    if (index < 5) {
        GXWGFifo.u8 = 8;
        GXWGFifo.u8 = 0x30;
        gx = __GXData;
        v = gx->matIdxA;
        GXWGFifo.u32 = v;
        GXWGFifo.u8 = 0x10;
        GXWGFifo.u32 = 0x1018;
        GXWGFifo.u32 = v;
    } else {
        GXWGFifo.u8 = 8;
        GXWGFifo.u8 = 0x40;
        gx = __GXData;
        v = gx->matIdxB;
        GXWGFifo.u32 = v;
        GXWGFifo.u8 = 0x10;
        GXWGFifo.u32 = 0x1019;
        GXWGFifo.u32 = v;
    }
    __GXData->bpSentNot = 1;
}
