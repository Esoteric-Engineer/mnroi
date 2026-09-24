typedef struct GXFifoObj GXFifoObj;

extern void GXFlush(void);
extern void __GXSaveCPUFifoAux(GXFifoObj* fifo);

void GXSaveCPUFifo(GXFifoObj* fifo)
{
    GXFlush();
    __GXSaveCPUFifoAux(fifo);
}
