typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned long u32;

typedef union {
    volatile u8 u8;
    volatile u16 u16;
    volatile u32 u32;
} GXFifoObj;

// Real Dolphin SDK global GX state (gx). Only the fields this function touches are declared. The rest is padding to keep their offsets correct.
typedef struct {
    u8 pad0[2];
    u16 bpSentNot;
    u16 vNum;
    u16 vLim;
} __GXDataStruct;

extern __GXDataStruct* const __GXData;

volatile GXFifoObj GXWGFifo : 0xCC008000;

void __GXSendFlushPrim(void)
{
    u32 i;
    u32 numD = __GXData->vNum * __GXData->vLim;

    GXWGFifo.u8 = 0x98;
    GXWGFifo.u16 = __GXData->vNum;
    for (i = 0; i < numD; i += 4) {
        GXWGFifo.u32 = 0;
    }
    __GXData->bpSentNot = 1;
}
