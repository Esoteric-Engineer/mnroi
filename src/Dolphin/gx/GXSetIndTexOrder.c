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
    u8 pad1[0x120 - 0x4];
    u32 iref;
    u8 pad2[0x5AC - 0x124];
    u32 dirtyState;
} __GXDataStruct;

extern __GXDataStruct* const __GXData;

#define SET_REG_FIELD(reg, size, shift, val)               \
    (reg) = (u32)__rlwimi((int)(reg), (int)(val), (shift), \
                          (32 - (shift) - (size)), (31 - (shift)))

void GXSetIndTexOrder(int ind_stage, int tex_coord, int tex_map)
{
    if (tex_map == 0xFF) {
        tex_map = 0;
    }
    if (tex_coord == 0xFF) {
        tex_coord = 0;
    }
    switch (ind_stage) {
    case 0:
        SET_REG_FIELD(__GXData->iref, 3, 0, tex_map);
        SET_REG_FIELD(__GXData->iref, 3, 3, tex_coord);
        break;
    case 1:
        SET_REG_FIELD(__GXData->iref, 3, 6, tex_map);
        SET_REG_FIELD(__GXData->iref, 3, 9, tex_coord);
        break;
    case 2:
        SET_REG_FIELD(__GXData->iref, 3, 12, tex_map);
        SET_REG_FIELD(__GXData->iref, 3, 15, tex_coord);
        break;
    case 3:
        SET_REG_FIELD(__GXData->iref, 3, 18, tex_map);
        SET_REG_FIELD(__GXData->iref, 3, 21, tex_coord);
        break;
    default:
        break;
    }
    GXWGFifo.u8 = 0x61;
    GXWGFifo.u32 = __GXData->iref;
    __GXData->dirtyState |= 3;
    __GXData->bpSentNot = 0;
}
