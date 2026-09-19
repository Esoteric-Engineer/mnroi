typedef unsigned char u8;
typedef unsigned long u32;

typedef union {
    volatile u8 u8;
    volatile u32 u32;
} GXFifoObj;

#define GXWGFifo (*(GXFifoObj*)0xCC008000)

void GXSetArray(int attr, const void* base_ptr, u8 stride)
{
    int cpAttr;
    u32 phyAddr;

    attr;
    if (attr == 0x19) {
        attr = 0xA;
    }
    cpAttr = attr - 9;
    phyAddr = (u32)base_ptr & 0x3FFFFFFF;
    GXWGFifo.u8 = 8;
    GXWGFifo.u8 = cpAttr | 0xA0;
    GXWGFifo.u32 = phyAddr;
    GXWGFifo.u8 = 8;
    GXWGFifo.u8 = cpAttr | 0xB0;
    GXWGFifo.u32 = stride;
}
