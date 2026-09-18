typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned long u32;

typedef void* (*GXRegionCallback)(u32);

// Real Dolphin SDK global GX state (gx). Only the field this function touches is declared. The rest is padding to keep its offset correct.
typedef struct {
    u8 pad0[2];
    u16 bpSentNot;
    u8 pad1[1224];
    GXRegionCallback tlutRegionCallback;
} __GXDataStruct;

extern __GXDataStruct* __GXData;

GXRegionCallback GXSetTlutRegionCallback(GXRegionCallback f)
{
    GXRegionCallback oldcb = __GXData->tlutRegionCallback;

    __GXData->tlutRegionCallback = f;
    return oldcb;
}
