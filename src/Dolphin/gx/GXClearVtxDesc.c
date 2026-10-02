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

extern __GXDataStruct* const __GXData;

#define SET_REG_FIELD(reg, size, shift, val)               \
    (reg) = (u32)__rlwimi((int)(reg), (int)(val), (shift), \
                          (32 - (shift) - (size)), (31 - (shift)))

void GXClearVtxDesc(void)
{
    __GXData->vcdLo = 0;
    SET_REG_FIELD(__GXData->vcdLo, 2, 9, 1);
    __GXData->vcdHi = 0;
    __GXData->hasNrms = 0;
    __GXData->hasBiNrms = 0;
    __GXData->dirtyState |= 8;
}
