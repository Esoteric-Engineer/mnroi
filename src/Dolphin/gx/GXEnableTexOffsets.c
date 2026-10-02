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
    u8 pad1[0xB4];
    u32 suTs0[8];
} __GXDataStruct;

extern __GXDataStruct* const __GXData;

volatile GXFifoObj GXWGFifo : 0xCC008000;

#define SET_REG_FIELD(reg, size, shift, val)               \
    (reg) = (u32)__rlwimi((int)(reg), (int)(val), (shift), \
                          (32 - (shift) - (size)), (31 - (shift)))

void GXEnableTexOffsets(u32 coord, u8 line_enable, u8 point_enable)
{
    SET_REG_FIELD(__GXData->suTs0[coord], 1, 18, line_enable);
    SET_REG_FIELD(__GXData->suTs0[coord], 1, 19, point_enable);
    GXWGFifo.u8 = 0x61;
    GXWGFifo.u32 = __GXData->suTs0[coord];
    __GXData->bpSentNot = 0;
}
