typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned long u32;

typedef struct {
    u8* base;
    u8* top;
    u32 size;
    u32 hiWatermark;
    u32 loWatermark;
    u8* rdPtr;
    u8* wrPtr;
    int count;
} __GXFifoObj;

extern int OSDisableInterrupts(void);
extern int OSRestoreInterrupts(int enabled);

extern volatile u32* __piReg;
extern volatile u16* __cpReg;
extern u8 lbl_8066F47C; // CPGPLinked

void __GXSaveCPUFifoAux(__GXFifoObj* realFifo)
{
    u32 temp;
    int enabled = OSDisableInterrupts();

    realFifo->base = (u8*)(__piReg[3] + 0x80000000);
    realFifo->top = (u8*)(__piReg[4] + 0x80000000);
    realFifo->wrPtr = (u8*)((__piReg[5] & 0xFBFFFFFF) + 0x80000000);
    if (lbl_8066F47C) {
        temp = __cpReg[29] << 16;
        temp |= __cpReg[28];
        realFifo->rdPtr = (u8*)(temp + 0x80000000);
        temp = __cpReg[25] << 16;
        temp |= __cpReg[24];
        realFifo->count = temp;
    } else {
        realFifo->count = realFifo->wrPtr - realFifo->rdPtr;
        if (realFifo->count < 0)
            realFifo->count += realFifo->size;
    }
    OSRestoreInterrupts(enabled);
}
