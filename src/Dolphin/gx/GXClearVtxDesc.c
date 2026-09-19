typedef unsigned char u8;
typedef unsigned long u32;

// Real Dolphin SDK global GX state (gx). Only the fields this function touches are declared; the rest is padding to keep their offsets correct.
typedef struct {
    u8 pad0[0x14];
    u32 vcdLo;
    u32 vcdHi;
    u8 pad1[0x4D4 - 0x1C];
    u8 hasNrms;
    u8 hasBiNrms;
    u8 pad2[0x5AC - 0x4D6];
    u32 dirtyState;
} __GXDataStruct;

extern __GXDataStruct* __GXData;

#define SET_REG_FIELD(reg, size, shift, val)               \
    (reg) = (u32)__rlwimi((int)(reg), (int)(val), (shift), \
                          (32 - (shift) - (size)), (31 - (shift)))

void GXClearVtxDesc(void)
{
    __GXDataStruct* gx = __GXData;
    u32 vcdLo;

    gx->vcdLo = 0;
    vcdLo = gx->vcdLo;
    SET_REG_FIELD(vcdLo, 2, 9, 1);
    gx->vcdLo = vcdLo;
    gx->vcdHi = 0;
    gx->hasNrms = 0;
    gx->hasBiNrms = 0;
    gx->dirtyState |= 8;
}
