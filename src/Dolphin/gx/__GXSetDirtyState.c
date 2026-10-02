typedef unsigned char u8;
typedef unsigned long u32;

// Real Dolphin SDK global GX state (gx). Only the fields this function touches are declared. The rest is padding to keep their offsets correct.
typedef struct {
    u8 pad0[0x5AC];
    u32 dirtyState;
} __GXDataStruct;

extern __GXDataStruct* __GXData;

extern void __GXSetSUTexRegs(void);
extern void __GXUpdateBPMask(void);
extern void __GXSetGenMode(void);
extern void __GXSetVCD(void);
extern void __GXSetVAT(void);
extern void __GXCalculateVLim(void);

void __GXSetDirtyState(void)
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
