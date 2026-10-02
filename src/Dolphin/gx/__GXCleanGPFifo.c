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
    u8 pad[0x80 - 0x22];
} GXFifoObj;

extern int OSDisableInterrupts(void);
extern int OSRestoreInterrupts(int enabled);
extern GXFifoObj* GXGetGPFifo(void);
extern GXFifoObj* GXGetCPUFifo(void);
extern void GXSetGPFifo(GXFifoObj* fifo);
extern void GXSetCPUFifo(GXFifoObj* fifo);

typedef GXFifoObj __GXFifoObj;

inline void GXInitFifoPtrs(GXFifoObj* fifo, void* readPtr, void* writePtr)
{
    __GXFifoObj* realFifo = (__GXFifoObj*)fifo;
    int enabled;

    enabled = OSDisableInterrupts();
    realFifo->rdPtr = readPtr;
    realFifo->wrPtr = writePtr;
    realFifo->count = (u8*)writePtr - (u8*)readPtr;
    if (realFifo->count < 0) {
        realFifo->count += realFifo->size;
    }
    OSRestoreInterrupts(enabled);
}

inline void* GXGetFifoBase(GXFifoObj* fifo)
{
    __GXFifoObj* realFifo = (__GXFifoObj*)fifo;
    return realFifo->base;
}

void __GXCleanGPFifo(void)
{
    GXFifoObj dummyFifo;
    GXFifoObj* gpFifo = GXGetGPFifo();
    GXFifoObj* cpuFifo;
    void* base;

    if (gpFifo == 0) {
        return;
    }
    cpuFifo = GXGetCPUFifo();
    base = GXGetFifoBase(gpFifo);
    dummyFifo = *gpFifo;
    GXInitFifoPtrs(&dummyFifo, base, base);
    GXSetGPFifo(&dummyFifo);
    if (cpuFifo == gpFifo) {
        GXSetCPUFifo(&dummyFifo);
    }
    GXInitFifoPtrs(gpFifo, base, base);
    GXSetGPFifo(gpFifo);
    if (cpuFifo == gpFifo) {
        GXSetCPUFifo(cpuFifo);
    }
}
