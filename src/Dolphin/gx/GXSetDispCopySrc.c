typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned long u32;

// Real Dolphin SDK global GX state (gx). Only the fields this function touches are declared. The rest is padding to keep their offsets correct.
typedef struct {
    u8 pad0[0x1E0];
    u32 cpDispSrc;
    u32 cpDispSize;
} __GXDataStruct;

extern __GXDataStruct* __GXData;

#define SET_REG_FIELD(reg, size, shift, val)               \
    (reg) = (u32)__rlwimi((int)(reg), (int)(val), (shift), \
                          (32 - (shift) - (size)), (31 - (shift)))

void GXSetDispCopySrc(u16 left, u16 top, u16 wd, u16 ht)
{
    u32 h = ht;
    __GXDataStruct* gx = __GXData;

    gx->cpDispSrc = 0;
    SET_REG_FIELD(gx->cpDispSrc, 10, 0, left);
    SET_REG_FIELD(gx->cpDispSrc, 10, 10, top);
    SET_REG_FIELD(gx->cpDispSrc, 8, 24, 0x49);

    gx->cpDispSize = 0;
    SET_REG_FIELD(gx->cpDispSize, 10, 0, wd - 1);
    SET_REG_FIELD(gx->cpDispSize, 10, 10, h - 1);
    SET_REG_FIELD(gx->cpDispSize, 8, 24, 0x4A);
}
