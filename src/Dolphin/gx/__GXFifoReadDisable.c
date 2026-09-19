typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned long u32;

// Real Dolphin SDK global GX state (gx). Only the fields this function touches are declared. The rest is padding to keep their offsets correct.
typedef struct {
    u8 pad0[0x8];
    u32 cpEnable;
} __GXDataStruct;

extern __GXDataStruct* __GXData;
extern volatile u16* __cpReg;

#define SET_REG_FIELD(reg, size, shift, val)               \
    (reg) = (u32)__rlwimi((int)(reg), (int)(val), (shift), \
                          (32 - (shift) - (size)), (31 - (shift)))

void __GXFifoReadDisable(void)
{
    __GXDataStruct* gx = __GXData;

    SET_REG_FIELD(gx->cpEnable, 1, 0, 0);
    __cpReg[1] = gx->cpEnable;
}
