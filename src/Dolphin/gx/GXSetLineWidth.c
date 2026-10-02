typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned long u32;

typedef union {
    volatile u8 u8;
    volatile u32 u32;
} GXFifoObj;

// Real Dolphin SDK global GX state (gx). Only the fields this function touches are declared. The rest is padding to keep their offsets correct.
typedef struct {
    u8 pad0[2];
    u16 bpSentNot;
    u8 pad1[0x78];
    u32 lpSize;
} __GXDataStruct;

extern __GXDataStruct* const __GXData;

volatile GXFifoObj GXWGFifo : 0xCC008000;

#define SET_REG_FIELD(reg, size, shift, val)               \
    (reg) = (u32)__rlwimi((int)(reg), (int)(val), (shift), \
                          (32 - (shift) - (size)), (31 - (shift)))

void GXSetLineWidth(u8 width, u32 texOffsets)
{
    SET_REG_FIELD(__GXData->lpSize, 8, 0, width);
    SET_REG_FIELD(__GXData->lpSize, 3, 16, texOffsets);
    GXWGFifo.u8 = 0x61;
    GXWGFifo.u32 = __GXData->lpSize;
    __GXData->bpSentNot = 0;
}
