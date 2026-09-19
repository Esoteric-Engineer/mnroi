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

extern __GXDataStruct* __GXData;
extern const f32 lbl_80670778;
extern const f32 lbl_8067077C;

typedef union {
    volatile u8 u8;
    volatile u32 u32;
    volatile f32 f32;
} GXFifoObj;

#define GXWGFifo (*(GXFifoObj*)0xCC008000)

#pragma fp_contract off
void __GXSetViewport(void)
{
    __GXDataStruct* gx = __GXData;
    f32 sx, sy, sz, ox, oy, oz;
    f32 zmin, zmax;
    u32 reg;

    sx = gx->vpWd * lbl_80670778;
    zmax = gx->vpFarz * gx->zScale;
    ox = lbl_8067077C + (gx->vpLeft + sx);
    sy = -gx->vpHt * lbl_80670778;
    oy = lbl_8067077C + (gx->vpTop + gx->vpHt * lbl_80670778);
    zmin = gx->vpNearz * gx->zScale;
    sz = zmax - zmin;
    oz = zmax + gx->zOffset;

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
    __GXDataStruct* gx = __GXData;

    gx->vpLeft = left;
    gx->vpTop = top;
    gx->vpWd = wd;
    gx->vpHt = ht;
    gx->vpNearz = nearz;
    gx->vpFarz = farz;
    __GXSetViewport();
    __GXData->bpSentNot = 1;
}
