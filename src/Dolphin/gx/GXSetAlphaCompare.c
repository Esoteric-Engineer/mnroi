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

volatile GXFifoObj GXWGFifo : 0xCC008000;

#define SET_REG_FIELD(reg, size, shift, val)               \
    (reg) = (u32)__rlwimi((int)(reg), (int)(val), (shift), \
                          (32 - (shift) - (size)), (31 - (shift)))

void GXSetAlphaCompare(u32 comp0, u8 ref0, u32 op, u32 comp1, u8 ref1)
{
    u32 reg = 0xF3000000;

    SET_REG_FIELD(reg, 8, 0, ref0);
    SET_REG_FIELD(reg, 8, 8, ref1);
    SET_REG_FIELD(reg, 3, 16, comp0);
    SET_REG_FIELD(reg, 3, 19, comp1);
    SET_REG_FIELD(reg, 2, 22, op);
    GXWGFifo.u8 = 0x61;
    GXWGFifo.u32 = reg;
    __GXData->bpSentNot = 0;
}
