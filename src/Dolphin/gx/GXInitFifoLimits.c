typedef unsigned char u8;
typedef unsigned long u32;

typedef struct {
    u8* base;
    u8* top;
    u32 size;
    u32 hiWatermark;
    u32 loWatermark;
} GXFifoObj;

void GXInitFifoLimits(GXFifoObj* fifo, u32 hi, u32 lo)
{
    fifo->hiWatermark = hi;
    fifo->loWatermark = lo;
}
