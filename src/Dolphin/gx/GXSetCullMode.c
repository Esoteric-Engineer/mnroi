typedef unsigned char u8;
typedef unsigned long u32;

// Real Dolphin SDK global GX state (gx). Only the fields this function touches are declared; the rest is padding to keep their offsets correct.
typedef struct {
    u8 pad0[0x204];
    u32 genMode;
    u8 pad1[0x5AC - 0x208];
    u32 dirtyState;
} __GXDataStruct;

extern __GXDataStruct* const __GXData;

#define SET_REG_FIELD(reg, size, shift, val)               \
    (reg) = (u32)__rlwimi((int)(reg), (int)(val), (shift), \
                          (32 - (shift) - (size)), (31 - (shift)))

void GXSetCullMode(u32 mode)
{
    u32 hwMode;

    hwMode = (u32)__rlwimi((int)((mode >> 1) & 1), (int)mode, 1, 30, 30);
    SET_REG_FIELD(__GXData->genMode, 2, 14, hwMode);
    __GXData->dirtyState |= 4;
}
