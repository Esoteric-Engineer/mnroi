typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned long u32;

// Real Dolphin SDK global GX state (gx). Only the fields this function touches are declared. The rest is padding to keep their offsets correct.
typedef struct {
    u8 pad0[2];
    u16 bpSentNot;
    u8 pad1[0x12C];
    u32 tevc[16];
    u32 teva[16];
    u32 tevKsel[8];
} __GXDataStruct;

extern __GXDataStruct* __GXData;

typedef union {
    volatile u8 u8;
    volatile u16 u16;
    volatile u32 u32;
} GXFifoObj;

#define GXWGFifo (*(GXFifoObj*)0xCC008000)

#define SET_REG_FIELD(reg, size, shift, val)               \
    (reg) = (u32)__rlwimi((int)(reg), (int)(val), (shift), \
                          (32 - (shift) - (size)), (31 - (shift)))

void GXSetTevSwapMode(u32 stage, u32 ras_sel, u32 tex_sel)
{
    __GXDataStruct* gx = __GXData;
    u32* pTevReg = &gx->teva[stage];

    SET_REG_FIELD(*pTevReg, 2, 0, ras_sel);
    SET_REG_FIELD(*pTevReg, 2, 2, tex_sel);

    GXWGFifo.u8 = 0x61;
    GXWGFifo.u32 = *pTevReg;
    gx->bpSentNot = 0;
}
