typedef unsigned char u8;

typedef union {
    volatile u8 u8;
} GXFifoObj;

#define GXWGFifo (*(GXFifoObj*)0xCC008000)

void GXInvalidateVtxCache(void)
{
    GXWGFifo.u8 = 0x48;
}
