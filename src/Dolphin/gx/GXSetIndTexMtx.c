// The unit owns GXBump.c's .sdata2 literal pool.
// dtk's bake-sda rewrites every .sdata2 access into a fixed r13 offset and drops the relocation, which leaves the pool unreferenced and lets mwld dead-strip it.
// force_active keeps it linked.
#pragma force_active on

typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned long u32;
typedef signed char s8;
typedef float f32;

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

void GXSetIndTexMtx(int mtx_id, f32 offset[2][3], s8 scale_exp)
{
    long mtx[6];
    u32 reg;
    u32 id;

    switch (mtx_id) {
    case 1:
    case 2:
    case 3:
        id = mtx_id - 1;
        break;
    case 5:
    case 6:
    case 7:
        id = mtx_id - 5;
        break;
    case 9:
    case 10:
    case 11:
        id = mtx_id - 9;
        break;
    default:
        id = 0;
        break;
    }

    mtx[0] = (int)(1024.0f * offset[0][0]) & 0x7FF;
    mtx[1] = (int)(1024.0f * offset[1][0]) & 0x7FF;
    scale_exp += 0x11;
    reg = 0;
    SET_REG_FIELD(reg, 11, 0, mtx[0]);
    SET_REG_FIELD(reg, 11, 11, mtx[1]);
    SET_REG_FIELD(reg, 2, 22, scale_exp & 3);
    SET_REG_FIELD(reg, 8, 24, id * 3 + 6);
    GXWGFifo.u8 = 0x61;
    GXWGFifo.u32 = reg;

    mtx[2] = (int)(1024.0f * offset[0][1]) & 0x7FF;
    mtx[3] = (int)(1024.0f * offset[1][1]) & 0x7FF;
    reg = 0;
    SET_REG_FIELD(reg, 11, 0, mtx[2]);
    SET_REG_FIELD(reg, 11, 11, mtx[3]);
    SET_REG_FIELD(reg, 2, 22, (scale_exp >> 2) & 3);
    SET_REG_FIELD(reg, 8, 24, id * 3 + 7);
    GXWGFifo.u8 = 0x61;
    GXWGFifo.u32 = reg;

    mtx[4] = (int)(1024.0f * offset[0][2]) & 0x7FF;
    mtx[5] = (int)(1024.0f * offset[1][2]) & 0x7FF;
    reg = 0;
    SET_REG_FIELD(reg, 11, 0, mtx[4]);
    SET_REG_FIELD(reg, 11, 11, mtx[5]);
    SET_REG_FIELD(reg, 2, 22, (scale_exp >> 4) & 3);
    SET_REG_FIELD(reg, 8, 24, id * 3 + 8);
    GXWGFifo.u8 = 0x61;
    GXWGFifo.u32 = reg;

    __GXData->bpSentNot = 0;
}

// The rest of GXBump.c's pool. Their readers (the other GXBump.c functions) are dead-stripped,
// so nothing references these; they must be plain non-static named consts to survive to the link.
const f32 GXIndTexScaleConst = 0.0009765625f;
const double GXBumpZeroConst = 0.0;
const double GXBumpU32ToDoubleMagic = 4503599627370496.0;
