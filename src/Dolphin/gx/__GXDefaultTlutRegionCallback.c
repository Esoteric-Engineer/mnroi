typedef unsigned long u32;

typedef struct {
    u32 dummy[4];
} GXTlutRegion;

// Real Dolphin SDK global GX state (gx). Only the fields this function touches are declared. The rest is padding to keep their offsets correct.
typedef struct {
    char pad0[0x388];
    GXTlutRegion TlutRegions[20];
} __GXDataStruct;

extern __GXDataStruct* const __GXData;

#pragma peephole off
GXTlutRegion* __GXDefaultTlutRegionCallback(u32 idx)
{
    if (idx >= 0x14U) {
        return 0;
    }
    return &__GXData->TlutRegions[idx];
}
