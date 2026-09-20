typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned long u32;

typedef union {
    volatile u8 u8;
    volatile u32 u32;
} GXFifoObj;

#define GXWGFifo (*(GXFifoObj*)0xCC008000)

// Real Dolphin SDK global GX state (gx). Only the fields this function touches are declared; the rest is padding to keep their offsets correct.
typedef struct {
    u8 pad0[0x2];
    u16 bpSentNot;
    u8 pad1[0x204 - 0x4];
    u32 genMode;
} __GXDataStruct;

extern __GXDataStruct* __GXData;

void __GXSetGenMode(void)
{
    __GXDataStruct* gx = __GXData;

    GXWGFifo.u8 = 0x61;
    GXWGFifo.u32 = gx->genMode;
    gx->bpSentNot = 0;
}
