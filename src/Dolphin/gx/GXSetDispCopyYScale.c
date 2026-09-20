typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned long u32;
typedef float f32;

typedef union {
    volatile u8 u8;
    volatile u32 u32;
} GXFifoObj;

volatile GXFifoObj GXWGFifo : 0xCC008000;

// Real Dolphin SDK global GX state (gx). Only the fields this function touches are declared. The rest is padding to keep their offsets correct.
typedef struct {
    u8 pad0[0x2];
    u16 bpSentNot;
    u8 pad1[0x1E4 - 0x4];
    u32 cpDispSize;
    u8 pad2[0x1EC - 0x1E8];
    u32 cpDisp;
} __GXDataStruct;

extern __GXDataStruct* const __GXData;
extern const f32 GXDispCopyYScaleConst;

#define SET_REG_FIELD(reg, size, shift, val)               \
    (reg) = (u32)__rlwimi((int)(reg), (int)(val), (shift), \
                          (32 - (shift) - (size)), (31 - (shift)))

static u32 __GXGetNumXfbLines(u32 efbHt, u32 iScale)
{
    u32 count;
    u32 realHt;
    u32 iScaleD;

    count = (efbHt - 1) * 0x100;
    realHt = (count / iScale) + 1;
    iScaleD = iScale;

    if (iScaleD > 128 && iScaleD < 256) {
        for (; (iScaleD & 1) == 0; iScaleD >>= 1)
            ;

        if ((efbHt % iScaleD) == 0) {
            realHt++;
        }
    }

    if (realHt > 1024) {
        realHt = 1024;
    }

    return realHt;
}

u32 GXSetDispCopyYScale(f32 vscale)
{
    u8 enable;
    u32 iScale;
    u32 ht;
    u32 reg;

    iScale = (u32)(GXDispCopyYScaleConst / vscale) & 0x1FF;
    enable = (iScale != 256);

    reg = 0;
    SET_REG_FIELD(reg, 9, 0, iScale);
    SET_REG_FIELD(reg, 8, 24, 0x4E);
    GXWGFifo.u8 = 0x61;
    GXWGFifo.u32 = reg;
    __GXData->bpSentNot = 0;
    SET_REG_FIELD(__GXData->cpDisp, 1, 10, enable);
    ht = ((__GXData->cpDispSize >> 10) & 0x3FF) + 1;
    return __GXGetNumXfbLines(ht, iScale);
}
