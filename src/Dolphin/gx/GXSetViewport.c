// The unit owns its .sdata2 literal pool (0.5, 342.0; see splits.txt).
// Nothing references GXTransformMaxIntConst or GXTransformZeroConst (their readers are dead-stripped), so mwld would strip them. force_active keeps them linked.
#pragma force_active on

typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned long u32;
typedef float f32;

// Real Dolphin SDK global GX state (gx). Only the fields this function touches are declared. The rest is padding to keep their offsets correct.
typedef struct {
    u8 pad0[2];
    u16 bpSentNot;
    u8 pad1[0x4F0];
    f32 vpLeft;
    f32 vpTop;
    f32 vpWd;
    f32 vpHt;
    f32 vpNearz;
    f32 vpFarz;
    f32 zOffset;
    f32 zScale;
} __GXDataStruct;

extern __GXDataStruct* const __GXData;

typedef union {
    volatile u8 u8;
    volatile u32 u32;
    volatile f32 f32;
} GXFifoObj;

volatile GXFifoObj GXWGFifo : 0xCC008000;

#pragma fp_contract off
void __GXSetViewport(void)
{
    f32 sx, sy, sz, ox, oy, oz, zmin, zmax;
    u32 reg;

    sx = __GXData->vpWd / 2.0f;
    sy = -__GXData->vpHt / 2.0f;
    ox = 342.0f + (__GXData->vpLeft + (__GXData->vpWd / 2.0f));
    oy = 342.0f + (__GXData->vpTop + (__GXData->vpHt / 2.0f));

    zmin = __GXData->vpNearz * __GXData->zScale;
    zmax = __GXData->vpFarz * __GXData->zScale;

    sz = zmax - zmin;
    oz = zmax + __GXData->zOffset;

    reg = 0x5101A;
    GXWGFifo.u8 = 0x10;
    GXWGFifo.u32 = reg;
    GXWGFifo.f32 = sx;
    GXWGFifo.f32 = sy;
    GXWGFifo.f32 = sz;
    GXWGFifo.f32 = ox;
    GXWGFifo.f32 = oy;
    GXWGFifo.f32 = oz;
}

void GXSetViewport(f32 left, f32 top, f32 wd, f32 ht, f32 nearz, f32 farz)
{
    __GXData->vpLeft = left;
    __GXData->vpTop = top;
    __GXData->vpWd = wd;
    __GXData->vpHt = ht;
    __GXData->vpNearz = nearz;
    __GXData->vpFarz = farz;
    __GXSetViewport();
    __GXData->bpSentNot = 1;
}

// Unreferenced here: the rest of GXTransform.c's .sdata2 pool, kept alive by force_active above.
const f32 GXTransformMaxIntConst = 16777215.0f;
const f32 GXTransformZeroConst = 0.0f;
