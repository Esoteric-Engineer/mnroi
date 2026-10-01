typedef struct GXFifoObj GXFifoObj;

extern GXFifoObj* CPUFifo;

GXFifoObj* GXGetCPUFifo(void)
{
    return CPUFifo;
}
