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

extern int OSDisableInterrupts(void);
extern int OSRestoreInterrupts(int enabled);

void GXInitFifoPtrs(GXFifoObj* fifo, void* readPtr, void* writePtr)
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
