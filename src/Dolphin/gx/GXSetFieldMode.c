typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned long u32;

// Real Dolphin SDK global GX state (gx). Only the fields this function touches are declared. The rest is padding to keep their offsets correct.
typedef struct {
    u8 pad0[0x7C];
    u32 lpSize;
} __GXDataStruct;

extern __GXDataStruct* __GXData;

extern void __GXFlushTextureState(void);

typedef union {
    volatile u8 u8;
    volatile u16 u16;
    volatile u32 u32;
} GXFifoObj;

#define GXWGFifo (*(GXFifoObj*)0xCC008000)

#define SET_REG_FIELD(reg, size, shift, val)               \
    (reg) = (u32)__rlwimi((int)(reg), (int)(val), (shift), \
                          (32 - (shift) - (size)), (31 - (shift)))

void GXSetFieldMode(u8 field_mode, u8 half_aspect_ratio)
{
    __GXDataStruct* gx = __GXData;
    u32 reg;
    SET_REG_FIELD(gx->lpSize, 1, 22, half_aspect_ratio);
    GXWGFifo.u8 = 0x61;
    GXWGFifo.u32 = gx->lpSize;
    __GXFlushTextureState();
    reg = field_mode | 0x68000000;
    GXWGFifo.u8 = 0x61;
    GXWGFifo.u32 = reg;
    __GXFlushTextureState();
}
