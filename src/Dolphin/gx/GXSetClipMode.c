typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned long u32;

typedef struct {
    u8 pad0[2];
    u16 bpSentNot;
} __GXDataStruct;

extern __GXDataStruct* const __GXData;

typedef union {
    volatile u8 u8;
    volatile u32 u32;
} GXFifoObj;

volatile GXFifoObj GXWGFifo : 0xCC008000;

void GXSetClipMode(u32 mode)
{
    GXWGFifo.u8 = 0x10;
    GXWGFifo.u32 = 0x1005;
    GXWGFifo.u32 = mode;
    __GXData->bpSentNot = 1;
}
