typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned long u32;

// Real Dolphin SDK global GX state (gx). Only the fields this function touches are declared. The rest is padding to keep their offsets correct.
typedef struct {
    u8 pad0[0x1EC];
    u32 cpDisp;
    u8 pad1[0x1FC - 0x1F0];
    u32 cpTex;
} __GXDataStruct;

extern __GXDataStruct* __GXData;

#define SET_REG_FIELD(reg, size, shift, val)               \
    (reg) = (u32)__rlwimi((int)(reg), (int)(val), (shift), \
                          (32 - (shift) - (size)), (31 - (shift)))

void GXSetCopyClamp(u32 clamp)
{
    u8 clmpT;
    u8 clmpB;
    __GXDataStruct* gx;

    clmpT = (clamp & 1) == 1;
    clmpB = (clamp & 2) == 2;

    gx = __GXData;
    SET_REG_FIELD(gx->cpDisp, 1, 0, clmpT);
    SET_REG_FIELD(gx->cpDisp, 1, 1, clmpB);

    SET_REG_FIELD(gx->cpTex, 1, 0, clmpT);
    SET_REG_FIELD(gx->cpTex, 1, 1, clmpB);
}
