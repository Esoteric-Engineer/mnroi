typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned long u32;

// Real Dolphin SDK global GX state (gx). Only the fields this function touches are declared. The rest is padding to keep their offsets correct.
typedef struct {
    u8 pad0[0x8];
    u32 cpEnable;
    u8 pad1[0x4];
    u32 cpClr;
} __GXDataStruct;

extern __GXDataStruct* const __GXData;
extern volatile u16* __cpReg;

#define SET_REG_FIELD(reg, size, shift, val)               \
    (reg) = (u32)__rlwimi((int)(reg), (int)(val), (shift), \
                          (32 - (shift) - (size)), (31 - (shift)))

void __GXWriteFifoIntEnable(u8 hiWatermarkEn, u8 loWatermarkEn)
{
    SET_REG_FIELD(__GXData->cpEnable, 1, 2, hiWatermarkEn);
    SET_REG_FIELD(__GXData->cpEnable, 1, 3, loWatermarkEn);
    __cpReg[1] = __GXData->cpEnable;
}
