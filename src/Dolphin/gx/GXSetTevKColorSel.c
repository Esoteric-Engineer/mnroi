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

void GXSetTevKColorSel(int stage, u32 sel)
{
    u32* Kreg = &__GXData->tevKsel[stage >> 1];

    if (stage & 1) {
        SET_REG_FIELD(*Kreg, 5, 14, sel);
    } else {
        SET_REG_FIELD(*Kreg, 5, 4, sel);
    }

    GXWGFifo.u8 = 0x61;
    GXWGFifo.u32 = *Kreg;
    __GXData->bpSentNot = 0;
}
