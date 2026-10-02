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

void GXSetZTexture(u32 op, u32 fmt, u32 bias)
{
    u32 zenv0;
    u32 zenv1;
    u32 type;

    zenv0 = 0;
    SET_REG_FIELD(zenv0, 24, 0, bias);
    SET_REG_FIELD(zenv0, 8, 24, 0xF4);

    zenv1 = 0;
    switch (fmt) {
    case 0x11:
        type = 0;
        break;
    case 0x13:
        type = 1;
        break;
    case 0x16:
        type = 2;
        break;
    default:
        type = 2;
        break;
    }
    SET_REG_FIELD(zenv1, 2, 0, type);
    SET_REG_FIELD(zenv1, 2, 2, op);
    SET_REG_FIELD(zenv1, 8, 24, 0xF5);

    GXWGFifo.u8 = 0x61;
    GXWGFifo.u32 = zenv0;
    GXWGFifo.u8 = 0x61;
    GXWGFifo.u32 = zenv1;
    __GXData->bpSentNot = 0;
}
