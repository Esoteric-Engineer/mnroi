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
extern void PPCSync(void);
extern void __GXFifoLink(u8 link);    // __GXFifoLink
extern void __GXWriteFifoIntEnable(u8 a, u8 b); // __GXWriteFifoIntEnable
extern void __GXWriteFifoIntReset(u8 a, u8 b); // __GXWriteFifoIntReset

extern volatile u32* __piReg;
extern GXFifoObj* lbl_8066F470; // CPUFifo
extern GXFifoObj* lbl_8066F474; // GPFifo
extern u8 lbl_8066F47C;         // CPGPLinked

#define SET_REG_FIELD(reg, size, shift, val)               \
    (reg) = (u32)__rlwimi((int)(reg), (int)(val), (shift), \
                          (32 - (shift) - (size)), (31 - (shift)))

void GXSetCPUFifo(GXFifoObj* fifo)
{
    int enabled = OSDisableInterrupts();

    lbl_8066F470 = fifo;
    if (lbl_8066F470 == lbl_8066F474) {
        u32 reg = 0;

        __piReg[3] = (u32)fifo->base & 0x3FFFFFFF;
        __piReg[4] = (u32)fifo->top & 0x3FFFFFFF;
        SET_REG_FIELD(reg, 21, 5, ((u32)fifo->wrPtr & 0x3FFFFFFF) >> 5);
        SET_REG_FIELD(reg, 1, 26, 0);
        __piReg[5] = reg;
        lbl_8066F47C = 1;
        __GXWriteFifoIntReset(1, 1);
        __GXWriteFifoIntEnable(1, 0);
        __GXFifoLink(1);
    } else {
        u32 reg;

        if (lbl_8066F47C) {
            __GXFifoLink(0);
            lbl_8066F47C = 0;
        }
        __GXWriteFifoIntEnable(0, 0);
        reg = 0;
        __piReg[3] = (u32)fifo->base & 0x3FFFFFFF;
        __piReg[4] = (u32)fifo->top & 0x3FFFFFFF;
        SET_REG_FIELD(reg, 21, 5, ((u32)fifo->wrPtr & 0x3FFFFFFF) >> 5);
        SET_REG_FIELD(reg, 1, 26, 0);
        __piReg[5] = reg;
    }

    PPCSync();
    OSRestoreInterrupts(enabled);
}
