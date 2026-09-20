typedef struct GXFifoObj GXFifoObj;

extern GXFifoObj* lbl_8066F470; // CPUFifo

GXFifoObj* GXGetCPUFifo(void)
{
    return lbl_8066F470;
}
