typedef unsigned char u8;
typedef unsigned long u32;

typedef union {
    volatile u8 u8;
    volatile u32 u32;
} GXFifoObj;

volatile GXFifoObj GXWGFifo : 0xCC008000;

// Real Dolphin SDK global GX state (gx). Only the fields this function touches are declared. The rest is padding to keep their offsets correct.
typedef struct {
    u8 pad0[0x1C];
    u32 vatA[8];
    u32 vatB[8];
    u32 vatC[8];
    u8 pad1[0x5AB - 0x7C];
    u8 dirtyVAT;
} __GXDataStruct;

extern __GXDataStruct* const __GXData;

void __GXSetVAT(void)
{
    u32 i = 0;
    u32 mask = __GXData->dirtyVAT;

    do {
        if (mask & 1) {
            GXWGFifo.u8 = 8;
            GXWGFifo.u8 = i | 0x70;
            GXWGFifo.u32 = __GXData->vatA[i];
            GXWGFifo.u8 = 8;
            GXWGFifo.u8 = i | 0x80;
            GXWGFifo.u32 = __GXData->vatB[i];
            GXWGFifo.u8 = 8;
            GXWGFifo.u8 = i | 0x90;
            GXWGFifo.u32 = __GXData->vatC[i];
        }
        mask >>= 1;
        i++;
    } while (mask != 0);
    __GXData->dirtyVAT = 0;
}
