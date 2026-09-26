typedef unsigned char u8;
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
    u32 pad;
} __GXFifoObj;

typedef struct {
    u8 pad0[0x8];
    u32 cpEnable;
    u8 pad1[0x5A8 - 0xC];
    u8 inDispList;
    u8 dlSaveContext;
    u8 pad2[0x5B0 - 0x5AA];
} __GXDataStruct;

extern __GXDataStruct* const __GXData;
extern volatile u32* __piReg;
extern __GXFifoObj* lbl_8066FB18; // OldCPUFifo

extern int OSDisableInterrupts(void);
extern void OSRestoreInterrupts(int enabled);
extern void* memcpy(void* dst, const void* src, u32 n);
extern void GXFlush(void);
extern void GXSetCPUFifo(__GXFifoObj* fifo);
extern void __GXSaveCPUFifoAux(__GXFifoObj* fifo);

__GXFifoObj DisplayListFifo;
__GXDataStruct __savedGXdata;

u32 GXEndDisplayList(void)
{
    u32 ov;
    int enabled;
    u32 cpenable;

    GXFlush();
    ov = (__piReg[5] >> 26) & 1;
    __GXSaveCPUFifoAux(&DisplayListFifo);
    GXSetCPUFifo(lbl_8066FB18);
    if (__GXData->dlSaveContext != 0) {
        enabled = OSDisableInterrupts();
        cpenable = __GXData->cpEnable;
        memcpy(__GXData, &__savedGXdata, sizeof(__GXDataStruct));
        __GXData->cpEnable = cpenable;
        OSRestoreInterrupts(enabled);
    }
    __GXData->inDispList = 0;
    if (!ov) {
        return DisplayListFifo.count;
    }
    return 0;
}
