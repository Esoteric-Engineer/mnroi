typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned long u32;

// Real Dolphin SDK global GX state (gx). Only the fields this function touches are declared. The rest is padding to keep their offsets correct.
typedef struct {
    u8 pad0[0x1E8];
    u32 cpDispStride;
} __GXDataStruct;

extern __GXDataStruct* __GXData;

#define SET_REG_FIELD(reg, size, shift, val)               \
    (reg) = (u32)__rlwimi((int)(reg), (int)(val), (shift), \
                          (32 - (shift) - (size)), (31 - (shift)))

void GXSetDispCopyDst(u16 wd, u16 ht)
{
    __GXDataStruct* gx = __GXData;
    u16 stride = (int)wd * 2;

    gx->cpDispStride = 0;
    SET_REG_FIELD(gx->cpDispStride, 10, 0, stride >> 5);
    SET_REG_FIELD(gx->cpDispStride, 8, 24, 0x4D);
}
