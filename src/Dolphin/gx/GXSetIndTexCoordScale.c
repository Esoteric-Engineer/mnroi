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
    u8 pad1[0x128 - 0x4];
    u32 indTexScale0;
    u32 indTexScale1;
} __GXDataStruct;

extern __GXDataStruct* const __GXData;

#define SET_REG_FIELD(reg, size, shift, val)               \
    (reg) = (u32)__rlwimi((int)(reg), (int)(val), (shift), \
                          (32 - (shift) - (size)), (31 - (shift)))

void GXSetIndTexCoordScale(int ind_state, u32 scale_s, u32 scale_t)
{
    switch (ind_state) {
    case 0:
        SET_REG_FIELD(__GXData->indTexScale0, 4, 0, scale_s);
        SET_REG_FIELD(__GXData->indTexScale0, 4, 4, scale_t);
        SET_REG_FIELD(__GXData->indTexScale0, 8, 24, 0x25);
        GXWGFifo.u8 = 0x61;
        GXWGFifo.u32 = __GXData->indTexScale0;
        break;
    case 1:
        SET_REG_FIELD(__GXData->indTexScale0, 4, 8, scale_s);
        SET_REG_FIELD(__GXData->indTexScale0, 4, 12, scale_t);
        SET_REG_FIELD(__GXData->indTexScale0, 8, 24, 0x25);
        GXWGFifo.u8 = 0x61;
        GXWGFifo.u32 = __GXData->indTexScale0;
        break;
    case 2:
        SET_REG_FIELD(__GXData->indTexScale1, 4, 0, scale_s);
        SET_REG_FIELD(__GXData->indTexScale1, 4, 4, scale_t);
        SET_REG_FIELD(__GXData->indTexScale1, 8, 24, 0x26);
        GXWGFifo.u8 = 0x61;
        GXWGFifo.u32 = __GXData->indTexScale1;
        break;
    case 3:
        SET_REG_FIELD(__GXData->indTexScale1, 4, 8, scale_s);
        SET_REG_FIELD(__GXData->indTexScale1, 4, 12, scale_t);
        SET_REG_FIELD(__GXData->indTexScale1, 8, 24, 0x26);
        GXWGFifo.u8 = 0x61;
        GXWGFifo.u32 = __GXData->indTexScale1;
        break;
    default:
        break;
    }
    __GXData->bpSentNot = 0;
}
