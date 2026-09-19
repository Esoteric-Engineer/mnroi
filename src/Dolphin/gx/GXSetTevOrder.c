typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned long u32;

// Real Dolphin SDK global GX state (gx). Only the fields this function touches are declared. The rest is padding to keep their offsets correct.
typedef struct {
    u8 pad0[2];
    u16 bpSentNot;
    u8 pad1[0xFC];
    u32 tref[8];
    u8 pad2[0x554 - 0x120];
    u32 texmapId[16];
    u8 pad3[0x598 - 0x594];
    u32 tevTcEnab;
    u8 pad4[0x5AC - 0x59C];
    u32 dirtyState;
} __GXDataStruct;

extern __GXDataStruct* __GXData;
extern int c2r[9];

typedef union {
    volatile u8 u8;
    volatile u16 u16;
    volatile u32 u32;
} GXFifoObj;

#define GXWGFifo (*(GXFifoObj*)0xCC008000)

#define SET_REG_FIELD(reg, size, shift, val)               \
    (reg) = (u32)__rlwimi((int)(reg), (int)(val), (shift), \
                          (32 - (shift) - (size)), (31 - (shift)))

void GXSetTevOrder(int stage, int coord, int map, int color)
{
    u32* ptref;
    u32 tmap;
    u32 tcoord;
    __GXDataStruct* gx;
    ptref = &__GXData->tref[stage / 2];
    __GXData->texmapId[stage] = map;

    tmap = map & ~0x100;
    tmap = (tmap >= 8) ? 0 : tmap;

    if (coord >= 8) {
        tcoord = 0;
        __GXData->tevTcEnab = __GXData->tevTcEnab & ~(1 << stage);
    } else {
        tcoord = coord;
        __GXData->tevTcEnab = __GXData->tevTcEnab | (1 << stage);
    }

    if (stage & 1) {
        SET_REG_FIELD(*ptref, 3, 12, tmap);
        SET_REG_FIELD(*ptref, 3, 15, tcoord);
        SET_REG_FIELD(*ptref, 3, 19, (color == 0xFF) ? 7 : c2r[color]);
        SET_REG_FIELD(*ptref, 1, 18, (map != 0xFF && !(map & 0x100)));
    } else {
        SET_REG_FIELD(*ptref, 3, 0, tmap);
        SET_REG_FIELD(*ptref, 3, 3, tcoord);
        SET_REG_FIELD(*ptref, 3, 7, (color == 0xFF) ? 7 : c2r[color]);
        SET_REG_FIELD(*ptref, 1, 6, (map != 0xFF && !(map & 0x100)));
    }

    GXWGFifo.u8 = 0x61;
    GXWGFifo.u32 = *ptref;
    gx = __GXData;
    gx->bpSentNot = 0;
    gx->dirtyState |= 1;
}
