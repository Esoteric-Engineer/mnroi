typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned long u32;
typedef u8 GXBool;

// Real Dolphin SDK global GX state (gx). Only the fields this function touches are declared. The rest is padding to keep their offsets correct.
typedef struct {
    u8 pad0[2];
    u16 bpSentNot;
} __GXDataStruct;

extern __GXDataStruct* const __GXData;

typedef union {
    volatile u8 u8;
    volatile u16 u16;
    volatile u32 u32;
} GXFifoObj;

volatile GXFifoObj GXWGFifo : 0xCC008000;

#define SET_REG_FIELD(reg, size, shift, val)               \
    (reg) = (u32)__rlwimi((int)(reg), (int)(val), (shift), \
                          (32 - (shift) - (size)), (31 - (shift)))

#define GX_WRITE_RAS_REG(v) \
    do {                     \
        GXWGFifo.u8 = 0x61; \
        GXWGFifo.u32 = (v); \
    } while (0)

void GXSetCopyFilter(GXBool aa, const u8 sample_pattern[12][2], GXBool vf, const u8 vfilter[7])
{
    u32 msLoc[4];
    u32 coeff0;
    u32 coeff1;

    if (aa != 0) {
        msLoc[0] = 0;
        SET_REG_FIELD(msLoc[0], 4, 0, sample_pattern[0][0]);
        SET_REG_FIELD(msLoc[0], 4, 4, sample_pattern[0][1]);
        SET_REG_FIELD(msLoc[0], 4, 8, sample_pattern[1][0]);
        SET_REG_FIELD(msLoc[0], 4, 12, sample_pattern[1][1]);
        SET_REG_FIELD(msLoc[0], 4, 16, sample_pattern[2][0]);
        SET_REG_FIELD(msLoc[0], 4, 20, sample_pattern[2][1]);
        SET_REG_FIELD(msLoc[0], 8, 24, 1);

        msLoc[1] = 0;
        SET_REG_FIELD(msLoc[1], 4, 0, sample_pattern[3][0]);
        SET_REG_FIELD(msLoc[1], 4, 4, sample_pattern[3][1]);
        SET_REG_FIELD(msLoc[1], 4, 8, sample_pattern[4][0]);
        SET_REG_FIELD(msLoc[1], 4, 12, sample_pattern[4][1]);
        SET_REG_FIELD(msLoc[1], 4, 16, sample_pattern[5][0]);
        SET_REG_FIELD(msLoc[1], 4, 20, sample_pattern[5][1]);
        SET_REG_FIELD(msLoc[1], 8, 24, 2);

        msLoc[2] = 0;
        SET_REG_FIELD(msLoc[2], 4, 0, sample_pattern[6][0]);
        SET_REG_FIELD(msLoc[2], 4, 4, sample_pattern[6][1]);
        SET_REG_FIELD(msLoc[2], 4, 8, sample_pattern[7][0]);
        SET_REG_FIELD(msLoc[2], 4, 12, sample_pattern[7][1]);
        SET_REG_FIELD(msLoc[2], 4, 16, sample_pattern[8][0]);
        SET_REG_FIELD(msLoc[2], 4, 20, sample_pattern[8][1]);
        SET_REG_FIELD(msLoc[2], 8, 24, 3);

        msLoc[3] = 0;
        SET_REG_FIELD(msLoc[3], 4, 0, sample_pattern[9][0]);
        SET_REG_FIELD(msLoc[3], 4, 4, sample_pattern[9][1]);
        SET_REG_FIELD(msLoc[3], 4, 8, sample_pattern[10][0]);
        SET_REG_FIELD(msLoc[3], 4, 12, sample_pattern[10][1]);
        SET_REG_FIELD(msLoc[3], 4, 16, sample_pattern[11][0]);
        SET_REG_FIELD(msLoc[3], 4, 20, sample_pattern[11][1]);
        SET_REG_FIELD(msLoc[3], 8, 24, 4);
    } else {
        msLoc[0] = 0x1666666;
        msLoc[1] = 0x2666666;
        msLoc[2] = 0x3666666;
        msLoc[3] = 0x4666666;
    }
    GX_WRITE_RAS_REG(msLoc[0]);
    GX_WRITE_RAS_REG(msLoc[1]);
    GX_WRITE_RAS_REG(msLoc[2]);
    GX_WRITE_RAS_REG(msLoc[3]);

    coeff0 = 0;
    SET_REG_FIELD(coeff0, 8, 24, 0x53);
    coeff1 = 0;
    SET_REG_FIELD(coeff1, 8, 24, 0x54);
    if (vf != 0) {
        SET_REG_FIELD(coeff0, 6, 0, vfilter[0]);
        SET_REG_FIELD(coeff0, 6, 6, vfilter[1]);
        SET_REG_FIELD(coeff0, 6, 12, vfilter[2]);
        SET_REG_FIELD(coeff0, 6, 18, vfilter[3]);
        SET_REG_FIELD(coeff1, 6, 0, vfilter[4]);
        SET_REG_FIELD(coeff1, 6, 6, vfilter[5]);
        SET_REG_FIELD(coeff1, 6, 12, vfilter[6]);
    } else {
        SET_REG_FIELD(coeff0, 6, 0, 0);
        SET_REG_FIELD(coeff0, 6, 6, 0);
        SET_REG_FIELD(coeff0, 6, 12, 21);
        SET_REG_FIELD(coeff0, 6, 18, 22);
        SET_REG_FIELD(coeff1, 6, 0, 21);
        SET_REG_FIELD(coeff1, 6, 6, 0);
        SET_REG_FIELD(coeff1, 6, 12, 0);
    }
    GX_WRITE_RAS_REG(coeff0);
    GX_WRITE_RAS_REG(coeff1);
    __GXData->bpSentNot = 0;
}
