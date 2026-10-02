typedef struct GXFifoObj GXFifoObj;

extern GXFifoObj* GPFifo;

GXFifoObj* GXGetGPFifo(void)
{
    return GPFifo;
}
