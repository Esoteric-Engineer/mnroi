// GXSetVtxAttrFmt and GXSetVtxAttrFmtv share a translation unit.
// Their two switch jump tables are adjacent in .data (0x804D2E28 and 0x804D2E6C) with no alignment padding between them, and MWCC always gives .data 8-byte alignment.
// Splitting them into separate units would land the second table 4 bytes late. See docs/matching_notes.md.
typedef unsigned char u8;
typedef unsigned long u32;

typedef enum { A_NULL = 0xFF, A_MAX = 0x7FFFFFFF } GXAttr;
typedef enum { C_MAX = 0x7FFFFFFF } GXCompCnt;
typedef enum { T_MAX = 0x7FFFFFFF } GXCompType;
typedef struct {
    GXAttr attr;
    GXCompCnt cnt;
    GXCompType type;
    u8 frac;
} GXVtxAttrFmtList;

// Real Dolphin SDK global GX state (gx). Only the fields this function touches are declared. The rest is padding to keep their offsets correct.
typedef struct {
    u8 pad0[0x1C];
    u32 vatA[8];
    u32 vatB[8];
    u32 vatC[8];
    u8 pad1[0x5AB - 0x7C];
    u8 dirtyVAT;
    u32 dirtyState;
} __GXDataStruct;

extern __GXDataStruct* const __GXData;

#define SET_REG_FIELD(reg, size, shift, val)               \
    (reg) = (u32)__rlwimi((int)(reg), (int)(val), (shift), \
                          (32 - (shift) - (size)), (31 - (shift)))

static inline void SETVAT(u32* va, u32* vb, u32* vc, GXAttr attr, GXCompCnt cnt, GXCompType type, u8 shft)
{
    switch (attr) {
    case 9:
        SET_REG_FIELD(*va, 1, 0, cnt);
        SET_REG_FIELD(*va, 3, 1, type);
        SET_REG_FIELD(*va, 5, 4, shft);
        break;
    case 10:
    case 25:
        SET_REG_FIELD(*va, 3, 10, type);
        if (cnt == 2) {
            SET_REG_FIELD(*va, 1, 9, 1);
            SET_REG_FIELD(*va, 1, 31, 1);
        } else {
            SET_REG_FIELD(*va, 1, 9, cnt);
            SET_REG_FIELD(*va, 1, 31, 0);
        }
        break;
    case 11:
        SET_REG_FIELD(*va, 1, 13, cnt);
        SET_REG_FIELD(*va, 3, 14, type);
        break;
    case 12:
        SET_REG_FIELD(*va, 1, 17, cnt);
        SET_REG_FIELD(*va, 3, 18, type);
        break;
    case 13:
        SET_REG_FIELD(*va, 1, 21, cnt);
        SET_REG_FIELD(*va, 3, 22, type);
        SET_REG_FIELD(*va, 5, 25, shft);
        break;
    case 14:
        SET_REG_FIELD(*vb, 1, 0, cnt);
        SET_REG_FIELD(*vb, 3, 1, type);
        SET_REG_FIELD(*vb, 5, 4, shft);
        break;
    case 15:
        SET_REG_FIELD(*vb, 1, 9, cnt);
        SET_REG_FIELD(*vb, 3, 10, type);
        SET_REG_FIELD(*vb, 5, 13, shft);
        break;
    case 16:
        SET_REG_FIELD(*vb, 1, 18, cnt);
        SET_REG_FIELD(*vb, 3, 19, type);
        SET_REG_FIELD(*vb, 5, 22, shft);
        break;
    case 17:
        SET_REG_FIELD(*vb, 1, 27, cnt);
        SET_REG_FIELD(*vb, 3, 28, type);
        SET_REG_FIELD(*vc, 5, 0, shft);
        break;
    case 18:
        SET_REG_FIELD(*vc, 1, 5, cnt);
        SET_REG_FIELD(*vc, 3, 6, type);
        SET_REG_FIELD(*vc, 5, 9, shft);
        break;
    case 19:
        SET_REG_FIELD(*vc, 1, 14, cnt);
        SET_REG_FIELD(*vc, 3, 15, type);
        SET_REG_FIELD(*vc, 5, 18, shft);
        break;
    case 20:
        SET_REG_FIELD(*vc, 1, 23, cnt);
        SET_REG_FIELD(*vc, 3, 24, type);
        SET_REG_FIELD(*vc, 5, 27, shft);
        break;
    }
}

void GXSetVtxAttrFmt(int vtxfmt, GXAttr attr, GXCompCnt cnt, GXCompType type, u8 frac)
{
    u32* va = &__GXData->vatA[vtxfmt];
    u32* vb = &__GXData->vatB[vtxfmt];
    u32* vc = &__GXData->vatC[vtxfmt];

    SETVAT(va, vb, vc, attr, cnt, type, frac);
    __GXData->dirtyState |= 0x10;
    __GXData->dirtyVAT |= (u8)(1 << (u8)vtxfmt);
}

void GXSetVtxAttrFmtv(int vtxfmt, const GXVtxAttrFmtList* list)
{
    u32* va = &__GXData->vatA[vtxfmt];
    u32* vb = &__GXData->vatB[vtxfmt];
    u32* vc = &__GXData->vatC[vtxfmt];

    while (list->attr != 0xFF) {
        SETVAT(va, vb, vc, list->attr, list->cnt, list->type, list->frac);
        list++;
    }
    __GXData->dirtyState |= 0x10;
    __GXData->dirtyVAT |= (u8)(1 << (u8)vtxfmt);
}
