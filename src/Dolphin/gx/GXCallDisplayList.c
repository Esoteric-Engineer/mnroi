typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned long u32;

typedef union {
    volatile u8 u8;
    volatile u16 u16;
    volatile u32 u32;
} GXFifoObj;

// Real Dolphin SDK global GX state (gx).
// Only the fields this function touches are declared. The rest is padding to keep their offsets correct.
typedef struct {
    u16 vNumNot;
    u16 bpSentNot;
    u8 pad4[0x5AC - 4];
    u32 dirtyState;
} __GXDataStruct;

extern __GXDataStruct* const __GXData;

extern void __GXSetDirtyState(void);
extern void __GXSendFlushPrim(void);

volatile GXFifoObj GXWGFifo : 0xCC008000;

void GXCallDisplayList(void* list, u32 nbytes)
{
    if (__GXData->dirtyState != 0) {
        __GXSetDirtyState();
    }
    if (*(u32*)&__GXData->vNumNot == 0) {
        __GXSendFlushPrim();
    }
    GXWGFifo.u8 = 0x40;
    GXWGFifo.u32 = (u32)list;
    GXWGFifo.u32 = nbytes;
}
