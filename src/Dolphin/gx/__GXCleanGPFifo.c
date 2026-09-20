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

static inline void InitFifoPtrs(GXFifoObj* fifo, void* readPtr, void* writePtr)
{
    int enabled;

    enabled = OSDisableInterrupts();
    fifo->rdPtr = readPtr;
    fifo->wrPtr = writePtr;
    fifo->count = (u8*)writePtr - (u8*)readPtr;
    if (fifo->count < 0) {
        fifo->count += fifo->size;
    }
    OSRestoreInterrupts(enabled);
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
    base = gpFifo->base;
    dummyFifo = *gpFifo;
    InitFifoPtrs(&dummyFifo, base, base);
    GXSetGPFifo(&dummyFifo);
    if (cpuFifo == gpFifo) {
        GXSetCPUFifo(&dummyFifo);
    }
    InitFifoPtrs(gpFifo, base, base);
    GXSetGPFifo(gpFifo);
    if (cpuFifo == gpFifo) {
        GXSetCPUFifo(cpuFifo);
    }
}
