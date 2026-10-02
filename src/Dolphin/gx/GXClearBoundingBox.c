typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned long u32;

typedef union {
    volatile u8 u8;
    volatile u32 u32;
} GXFifoObj;

volatile GXFifoObj GXWGFifo : 0xCC008000;

typedef struct {
    u8 pad0[0x2];
    u16 bpSentNot;
} __GXDataStruct;

extern __GXDataStruct* __GXData;
#define gx __GXData

void GXClearBoundingBox(void)
{
    u32 reg;

    reg = 0x550003FF;
    GXWGFifo.u8 = 0x61;
    GXWGFifo.u32 = reg;
    reg = 0x560003FF;
    GXWGFifo.u8 = 0x61;
    GXWGFifo.u32 = reg;
    gx->bpSentNot = 0;
}
