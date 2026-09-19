typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned long u32;
typedef float f32;

// Real Dolphin SDK global GX state (gx). Only the fields this function touches are declared. The rest is padding to keep their offsets correct.
typedef struct {
    u8 pad0[2];
    u16 bpSentNot;
    u8 pad1[0x4D4];
    u32 projType;
    f32 projMtx[6];
} __GXDataStruct;

extern __GXDataStruct* __GXData;

typedef union {
    volatile u8 u8;
    volatile u16 u16;
    volatile u32 u32;
    volatile f32 f32;
} GXFifoObj;

#define GXWGFifo (*(GXFifoObj*)0xCC008000)

static inline void WriteProjPS(const register f32 src[6], register volatile void* dst)
{
    register f32 f1, f2, f3;
    asm {
        psq_l f1, 0(src), 0, 0
        psq_l f2, 8(src), 0, 0
        psq_l f3, 16(src), 0, 0
        psq_st f1, 0(dst), 0, 0
        psq_st f2, 0(dst), 0, 0
        psq_st f3, 0(dst), 0, 0
    }
}

void GXSetProjection(f32 mtx[4][4], int type)
{
    __GXDataStruct* gx = __GXData;
    __GXDataStruct* gx2;
    u32 reg;

    gx->projType = type;
    gx->projMtx[0] = mtx[0][0];
    gx->projMtx[2] = mtx[1][1];
    gx->projMtx[4] = mtx[2][2];
    gx->projMtx[5] = mtx[2][3];
    if (type == 1) {
        gx->projMtx[1] = mtx[0][3];
        gx->projMtx[3] = mtx[1][3];
    } else {
        gx->projMtx[1] = mtx[0][2];
        gx->projMtx[3] = mtx[1][2];
    }

    gx2 = __GXData;
    reg = 0x00061020;
    GXWGFifo.u8 = 0x10;
    GXWGFifo.u32 = reg;
    WriteProjPS(gx2->projMtx, &GXWGFifo);
    GXWGFifo.u32 = gx2->projType;
    gx2->bpSentNot = 1;
}

static inline void CopyProjPS(const register f32 src[6], register f32 dst[6])
{
    register f32 f1, f2, f3;
    asm {
        psq_l f1, 0(src), 0, 0
        psq_l f2, 8(src), 0, 0
        psq_l f3, 16(src), 0, 0
        psq_st f1, 0(dst), 0, 0
        psq_st f2, 8(dst), 0, 0
        psq_st f3, 16(dst), 0, 0
    }
}

extern const f32 lbl_80670770;

void GXSetProjectionv(f32* ptr)
{
    __GXDataStruct* gx;
    u32 type = (ptr[0] == lbl_80670770) ? 0 : 1;
    u32 reg;

    gx = __GXData;
    gx->projType = type;
    CopyProjPS(ptr + 1, gx->projMtx);

    reg = 0x00061020;
    GXWGFifo.u8 = 0x10;
    GXWGFifo.u32 = reg;
    WriteProjPS(gx->projMtx, &GXWGFifo);
    GXWGFifo.u32 = gx->projType;
    gx->bpSentNot = 1;
}
