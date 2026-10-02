typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned long u32;

typedef union {
    volatile u8 u8;
    volatile u32 u32;
} GXFifoObj;

volatile GXFifoObj GXWGFifo : 0xCC008000;

// Real Dolphin SDK global GX state (gx). Only the fields this function touches are declared. The rest is padding to keep their offsets correct.
typedef struct {
    u8 pad0[0x2];
    u16 bpSentNot;
} __GXDataStruct;

extern __GXDataStruct* const __GXData;

#define SET_REG_FIELD(reg, size, shift, val)               \
    (reg) = (u32)__rlwimi((int)(reg), (int)(val), (shift), \
                          (32 - (shift) - (size)), (31 - (shift)))

void GXSetChanCtrl(int chan, u8 enable, int amb_src, int mat_src, u32 light_mask, int diff_fn, int attn_fn)
{
    u32 reg;
    u32 idx;

    idx = chan & 3;

    reg = 0;
    SET_REG_FIELD(reg, 1, 1, enable);
    SET_REG_FIELD(reg, 1, 0, mat_src);
    SET_REG_FIELD(reg, 1, 6, amb_src);
    SET_REG_FIELD(reg, 2, 7, (attn_fn == 0) ? 0 : diff_fn);
    SET_REG_FIELD(reg, 1, 9, (attn_fn != 2));
    SET_REG_FIELD(reg, 1, 10, (attn_fn != 0));
    SET_REG_FIELD(reg, 4, 2, light_mask);
    SET_REG_FIELD(reg, 4, 11, light_mask >> 4);

    GXWGFifo.u8 = 0x10;
    GXWGFifo.u32 = idx + 0x100E;
    GXWGFifo.u32 = reg;
    if (chan == 4) {
        GXWGFifo.u8 = 0x10;
        GXWGFifo.u32 = 0x1010;
        GXWGFifo.u32 = reg;
    } else if (chan == 5) {
        GXWGFifo.u8 = 0x10;
        GXWGFifo.u32 = 0x1011;
        GXWGFifo.u32 = reg;
    }
    __GXData->bpSentNot = 1;
}
