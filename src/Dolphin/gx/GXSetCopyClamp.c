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

extern __GXDataStruct* const __GXData;

#define SET_REG_FIELD(reg, size, shift, val)               \
    (reg) = (u32)__rlwimi((int)(reg), (int)(val), (shift), \
                          (32 - (shift) - (size)), (31 - (shift)))

void GXSetCopyClamp(u32 clamp)
{
    u8 clmpT;
    u8 clmpB;

    clmpT = (clamp & 1) == 1;
    clmpB = (clamp & 2) == 2;

    SET_REG_FIELD(__GXData->cpDisp, 1, 0, clmpT);
    SET_REG_FIELD(__GXData->cpDisp, 1, 1, clmpB);

    SET_REG_FIELD(__GXData->cpTex, 1, 0, clmpT);
    SET_REG_FIELD(__GXData->cpTex, 1, 1, clmpB);
}
