typedef unsigned char u8;
typedef unsigned short u16;
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

// Real Dolphin SDK global GX state (gx). Only the fields this function touches are declared. The rest is padding to keep their offsets correct.
typedef struct {
    u8 pad0[0x8];
    u32 cpEnable;
} __GXDataStruct;

extern int OSDisableInterrupts(void);
extern int OSRestoreInterrupts(int enabled);
extern void fn_8017A838(void);       // __sync
extern void __GXFifoReadDisable(void);
extern void __GXFifoReadEnable(void);
extern void __GXFifoLink(u8 link);
extern void __GXWriteFifoIntEnable(u8 a, u8 b);
extern void __GXWriteFifoIntReset(u8 a, u8 b);

extern __GXDataStruct* const __GXData;
extern volatile u16* __cpReg;
extern GXFifoObj* lbl_8066F470; // CPUFifo
extern GXFifoObj* lbl_8066F474; // GPFifo
extern u8 lbl_8066F47C;         // CPGPLinked

#define SET_REG_FIELD(reg, size, shift, val)               \
    (reg) = (u32)__rlwimi((int)(reg), (int)(val), (shift), \
                          (32 - (shift) - (size)), (31 - (shift)))

void GXSetGPFifo(GXFifoObj* fifo)
{
    int enabled = OSDisableInterrupts();
    u32 reg;
    __GXDataStruct* gx;

    __GXFifoReadDisable();
    __GXWriteFifoIntEnable(0, 0);
    lbl_8066F474 = fifo;

    __cpReg[16] = (u32)fifo->base;
    __cpReg[18] = (u32)fifo->top;
    __cpReg[24] = fifo->count;
    __cpReg[26] = (u32)fifo->wrPtr;
    __cpReg[28] = (u32)fifo->rdPtr;
    __cpReg[20] = fifo->hiWatermark;
    __cpReg[22] = fifo->loWatermark;
    __cpReg[17] = ((u32)fifo->base & 0x3FFFFFFF) >> 16;
    __cpReg[19] = ((u32)fifo->top & 0x3FFFFFFF) >> 16;
    __cpReg[25] = fifo->count >> 16;
    __cpReg[27] = ((u32)fifo->wrPtr & 0x3FFFFFFF) >> 16;
    __cpReg[29] = ((u32)fifo->rdPtr & 0x3FFFFFFF) >> 16;
    __cpReg[21] = fifo->hiWatermark >> 16;
    __cpReg[23] = fifo->loWatermark >> 16;

    fn_8017A838();

    if (lbl_8066F470 == lbl_8066F474) {
        lbl_8066F47C = 1;
        __GXWriteFifoIntEnable(1, 0);
        __GXFifoLink(1);
    } else {
        lbl_8066F47C = 0;
        __GXWriteFifoIntEnable(0, 0);
        __GXFifoLink(0);
    }

    gx = __GXData;
    reg = gx->cpEnable;
    SET_REG_FIELD(reg, 1, 1, 0);
    SET_REG_FIELD(reg, 1, 5, 0);
    __cpReg[1] = reg;
    __cpReg[1] = gx->cpEnable;
    __GXWriteFifoIntReset(1, 1);
    __GXFifoReadEnable();
    OSRestoreInterrupts(enabled);
}
