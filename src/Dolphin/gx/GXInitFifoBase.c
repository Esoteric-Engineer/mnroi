typedef unsigned char u8;
typedef unsigned long u32;

typedef struct {
    u8* base;
    u8* top;
    u32 size;
    u32 hiWatermark;
    u32 loWatermark;
    void* rdPtr;
    void* wrPtr;
    int count;
    u8 bindCpu;
    u8 bindGp;
} GXFifoObj;

extern void GXInitFifoLimits(GXFifoObj* fifo, u32 hi, u32 lo);
extern void GXInitFifoPtrs(GXFifoObj* fifo, void* rd, void* wr);

void GXInitFifoBase(GXFifoObj* fifo, void* base, u32 size)
{
    fifo->base = base;
    fifo->top = (u8*)base + size - 4;
    fifo->size = size;
    fifo->count = 0;
    GXInitFifoLimits(fifo, size - 0x4000, (size >> 1) & ~0x1F);
    GXInitFifoPtrs(fifo, base, base);
}
