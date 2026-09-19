typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned long u32;

// Real Dolphin SDK global GX state (gx). Only the fields these functions touch are declared; the rest is padding to keep their offsets correct.
typedef struct {
    u8 pad0[2];
    u16 bpSentNot;
    u8 pad1[0xB4];
    u32 suTs0[8];
    u32 suTs1[8];
    u8 pad2[8];
    u32 tref[8];
    u32 iref;
    u8 pad3[0xE0];
    u32 genMode;
    u8 pad4[0x30C];
    u32 tImage0[8];
    u32 tMode0[8];
    u32 texmapId[16];
    u32 tcsManEnab;
    u32 tevTcEnab;
} __GXDataStruct;

extern __GXDataStruct* __GXData;

typedef union {
    volatile u8 u8;
    volatile u16 u16;
    volatile u32 u32;
} GXFifoObj;

#define GXWGFifo (*(GXFifoObj*)0xCC008000)

#define SET_REG_FIELD(reg, size, shift, val)               \
    (reg) = (u32)__rlwimi((int)(reg), (int)(val), (shift), \
                          (32 - (shift) - (size)), (31 - (shift)))

#define GET_REG_FIELD(reg, size, shift) ((((u32)(reg)) >> (shift)) & ((1 << (size)) - 1))

#define GX_WRITE_RAS_REG(value) \
    do {                        \
        GXWGFifo.u8 = 0x61;     \
        GXWGFifo.u32 = (value); \
    } while (0)

#define gx __GXData

#pragma dont_inline on
static void __SetSURegs(u32 tmap, u32 tcoord)
{
    __GXDataStruct* g = __GXData;
    u32 w;
    u32 h;
    u8 s_bias;
    u8 t_bias;

    w = GET_REG_FIELD(g->tImage0[tmap], 10, 0);
    h = GET_REG_FIELD(g->tImage0[tmap], 10, 10);
    SET_REG_FIELD(g->suTs0[tcoord], 16, 0, w);
    SET_REG_FIELD(g->suTs1[tcoord], 16, 0, h);
    s_bias = GET_REG_FIELD(g->tMode0[tmap], 2, 0) == 1;
    t_bias = GET_REG_FIELD(g->tMode0[tmap], 2, 2) == 1;
    SET_REG_FIELD(g->suTs0[tcoord], 1, 16, s_bias);
    SET_REG_FIELD(g->suTs1[tcoord], 1, 16, t_bias);
    GX_WRITE_RAS_REG(g->suTs0[tcoord]);
    GX_WRITE_RAS_REG(g->suTs1[tcoord]);
    g->bpSentNot = 0;
}

#pragma dont_inline reset
void __GXSetSUTexRegs(void)
{
    u32 nStages;
    u32 nIndStages;
    u32 i;
    u32 map;
    u32 tmap;
    u32 coord;
    u32* ptref;

    if (gx->tcsManEnab != 0xFF) {
        nStages = GET_REG_FIELD(gx->genMode, 4, 10) + 1;
        nIndStages = GET_REG_FIELD(gx->genMode, 3, 16);
        for (i = 0; i < nIndStages; i++) {
            switch (i) {
            case 0:
                tmap = GET_REG_FIELD(gx->iref, 3, 0);
                coord = GET_REG_FIELD(gx->iref, 3, 3);
                break;
            case 1:
                tmap = GET_REG_FIELD(gx->iref, 3, 6);
                coord = GET_REG_FIELD(gx->iref, 3, 9);
                break;
            case 2:
                tmap = GET_REG_FIELD(gx->iref, 3, 12);
                coord = GET_REG_FIELD(gx->iref, 3, 15);
                break;
            case 3:
                tmap = GET_REG_FIELD(gx->iref, 3, 18);
                coord = GET_REG_FIELD(gx->iref, 3, 21);
                break;
            }
            if (!(gx->tcsManEnab & (1 << coord))) {
                __SetSURegs(tmap, coord);
            }
        }
        i = 0;
        for (i = 0; i < nStages; i++) {
            ptref = &gx->tref[i / 2];
            map = gx->texmapId[i];
            tmap = map & 0xFFFFFEFF;
            if (i & 1) {
                coord = GET_REG_FIELD(*ptref, 3, 15);
            } else {
                coord = GET_REG_FIELD(*ptref, 3, 3);
            }
            if ((tmap != 0xFF) && !(gx->tcsManEnab & (1 << coord)) && (gx->tevTcEnab & (1 << i))) {
                __SetSURegs(tmap, coord);
            }
        }
    }
}
