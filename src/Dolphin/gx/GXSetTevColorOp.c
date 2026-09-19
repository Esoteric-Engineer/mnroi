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

void GXSetTevColorOp(u32 stage, int op, u32 bias, u32 scale, u32 clamp, u32 out_reg)
{
    __GXDataStruct* gx;
    u32 tevc = __GXData->tevc[stage];

    SET_REG_FIELD(tevc, 1, 18, op & 1);
    if (op <= 1) {
        SET_REG_FIELD(tevc, 2, 20, scale);
        SET_REG_FIELD(tevc, 2, 16, bias);
    } else {
        SET_REG_FIELD(tevc, 2, 20, (op >> 1) & 3);
        SET_REG_FIELD(tevc, 2, 16, 3);
    }
    SET_REG_FIELD(tevc, 1, 19, clamp & 0xFF);
    SET_REG_FIELD(tevc, 2, 22, out_reg);
    gx = __GXData;
    GXWGFifo.u8 = 0x61;
    GXWGFifo.u32 = tevc;
    gx->tevc[stage] = tevc;
    gx->bpSentNot = 0;
}
