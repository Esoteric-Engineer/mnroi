typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned long u32;

typedef union {
    volatile u8 u8;
    volatile u16 u16;
    volatile u32 u32;
} GXFifoObj;

// Real Dolphin SDK global GX state (gx). Only the fields this function touches are declared. The rest is padding to keep their offsets correct.
typedef struct {
    u32 vNumNot;
    u8 pad4[0x5AC - 4];
    u32 dirtyState;
} __GXDataStruct;

extern __GXDataStruct* __GXData;

extern void __GXSetSUTexRegs(void);
extern void __GXUpdateBPMask(void);
extern void __GXSetGenMode(void);
extern void __GXSetVCD(void);
extern void __GXSetVAT(void);
extern void __GXCalculateVLim(void);
extern void __GXSendFlushPrim(void);

volatile GXFifoObj GXWGFifo : 0xCC008000;

static inline void __GXSetDirtyState(void)
{
    u32 dirty = __GXData->dirtyState;

    if (dirty & 1) {
        __GXSetSUTexRegs();
    }
    if (dirty & 2) {
        __GXUpdateBPMask();
    }
    if (dirty & 4) {
        __GXSetGenMode();
    }
    if (dirty & 8) {
        __GXSetVCD();
    }
    if (dirty & 0x10) {
        __GXSetVAT();
    }
    if (dirty & (0x10 | 8)) {
        __GXCalculateVLim();
    }
    __GXData->dirtyState = 0;
}

void GXBegin(u32 type, u32 vtxfmt, u16 nverts)
{
    if (__GXData->dirtyState != 0) {
        __GXSetDirtyState();
    }
    if (__GXData->vNumNot == 0) {
        __GXSendFlushPrim();
    }
    GXWGFifo.u8 = vtxfmt | type;
    GXWGFifo.u16 = nverts;
}
