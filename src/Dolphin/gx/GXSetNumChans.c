typedef unsigned char u8;
typedef unsigned long u32;

typedef union {
    volatile u8 u8;
    volatile u32 u32;
} GXFifoObj;

#define GXWGFifo (*(GXFifoObj*)0xCC008000)

// Real Dolphin SDK global GX state (gx). Only the fields this function touches are declared. The rest is padding to keep their offsets correct.
typedef struct {
    u8 pad0[0x204];
    u32 genMode;
    u8 pad1[0x5AC - 0x208];
    u32 dirtyState;
} __GXDataStruct;

extern __GXDataStruct* __GXData;

#define SET_REG_FIELD(reg, size, shift, val)               \
    (reg) = (u32)__rlwimi((int)(reg), (int)(val), (shift), \
                          (32 - (shift) - (size)), (31 - (shift)))

void GXSetNumChans(u8 nChans)
{
    __GXDataStruct* gx = __GXData;

    SET_REG_FIELD(gx->genMode, 3, 4, nChans);
    GXWGFifo.u8 = 0x10;
    GXWGFifo.u32 = 0x1009;
    GXWGFifo.u32 = nChans;
    gx->dirtyState |= 4;
}
