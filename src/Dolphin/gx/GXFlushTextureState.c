typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned long u32;

// Real Dolphin SDK global GX state (gx). Only the fields this function touches are declared. The rest is padding to keep their offsets correct.
typedef struct {
    u8 pad0[2];
    u16 bpSentNot;
    u8 pad1[0x120];
    u32 bpMask;
} __GXDataStruct;

extern __GXDataStruct* __GXData;

typedef union {
    volatile u8 u8;
    volatile u16 u16;
    volatile u32 u32;
} GXFifoObj;

#define GXWGFifo (*(GXFifoObj*)0xCC008000)

void __GXFlushTextureState(void)
{
    __GXDataStruct* gx = __GXData;

    GXWGFifo.u8 = 0x61;
    GXWGFifo.u32 = gx->bpMask;
    gx->bpSentNot = 0;
}
