typedef unsigned char u8;
typedef unsigned long u32;

// Real Dolphin SDK global GX state (gx). Only the fields this function touches are declared; the rest is padding to keep their offsets correct.
typedef struct {
    u8 pad0[0x204];
    u32 genMode;
    u8 pad1[0x3A4];
    u32 dirtyState;
} __GXDataStruct;

extern __GXDataStruct* __GXData;

#define SET_REG_FIELD(reg, size, shift, val)               \
    (reg) = (u32)__rlwimi((int)(reg), (int)(val), (shift), \
                          (32 - (shift) - (size)), (31 - (shift)))

void GXSetNumIndStages(u8 nIndStages)
{
    __GXDataStruct* gx = __GXData;

    SET_REG_FIELD(gx->genMode, 3, 16, nIndStages);
    gx->dirtyState |= 6;
}
