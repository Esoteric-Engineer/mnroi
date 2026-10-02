typedef unsigned char u8;
typedef unsigned long u32;

// Real Dolphin SDK global GX state (gx). Only the fields this function touches are declared. The rest is padding to keep their offsets correct.
typedef struct {
    u8 pad0[0x80];
    u32 matIdxA;
} __GXDataStruct;

extern __GXDataStruct* __GXData;

extern void __GXSetMatrixIndex(int index);

#define SET_REG_FIELD(reg, size, shift, val)               \
    (reg) = (u32)__rlwimi((int)(reg), (int)(val), (shift), \
                          (32 - (shift) - (size)), (31 - (shift)))

void GXSetCurrentMtx(u32 id)
{
    __GXDataStruct* gx = __GXData;

    SET_REG_FIELD(gx->matIdxA, 6, 0, id);
    __GXSetMatrixIndex(0);
}
