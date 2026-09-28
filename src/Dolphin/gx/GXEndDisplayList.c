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
    u8 pad2[0x5AC - 0x5AA];
    u32 dirtyState;
} __GXDataStruct;

extern __GXDataStruct* const __GXData;
extern volatile u32* __piReg;

extern int OSDisableInterrupts(void);
extern void OSRestoreInterrupts(int enabled);
extern void* memcpy(void* dst, const void* src, u32 n);
extern void GXFlush(void);
extern void GXSetCPUFifo(__GXFifoObj* fifo);
extern void __GXSaveCPUFifoAux(__GXFifoObj* fifo);
extern __GXFifoObj* GXGetCPUFifo(void);
extern void GXSaveCPUFifo(__GXFifoObj* fifo);
extern void GXResetWriteGatherPipe(void);
extern void __GXSetDirtyState(void);

__GXFifoObj DisplayListFifo;
static volatile __GXFifoObj* OldCPUFifo;
__GXDataStruct __savedGXdata;

void GXBeginDisplayList(void* list, u32 size)
{
    __GXFifoObj* CPUFifo = GXGetCPUFifo();

    (void)DisplayListFifo;

    if (__GXData->dirtyState != 0) {
        __GXSetDirtyState();
    }
    if (__GXData->dlSaveContext != 0) {
        memcpy(&__savedGXdata, __GXData, sizeof(__GXDataStruct));
    }
    DisplayListFifo.base = (u8*)list;
    DisplayListFifo.top = (u8*)list + size - 4;
    DisplayListFifo.size = size;
    DisplayListFifo.count = 0;
    DisplayListFifo.rdPtr = list;
    DisplayListFifo.wrPtr = list;
    __GXData->inDispList = 1;
    GXSaveCPUFifo(CPUFifo);
    OldCPUFifo = CPUFifo;
    GXSetCPUFifo(&DisplayListFifo);
    GXResetWriteGatherPipe();
}

u32 GXEndDisplayList(void)
{
    u32 ov;
    int enabled;
    u32 cpenable;

    GXFlush();
    ov = (__piReg[5] >> 26) & 1;
    __GXSaveCPUFifoAux(&DisplayListFifo);
    GXSetCPUFifo((__GXFifoObj*)OldCPUFifo);
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
