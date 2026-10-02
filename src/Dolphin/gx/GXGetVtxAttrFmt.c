// These five functions share a translation unit because their switch jump tables are packed back to back in .data (0x804D2EB0 through 0x804D2F64) with no alignment padding, and MWCC always gives .data 8-byte alignment.
// GXSetArray and GXInvalidateVtxCache have no tables of their own but sit between the others in .text, so they're here too.
typedef unsigned char u8;
typedef unsigned long u32;

typedef int GXAttr;
typedef int GXCompCnt;
typedef int GXCompType;

typedef struct {
    GXAttr attr;
    GXCompCnt cnt;
    GXCompType type;
    u8 frac;
} GXVtxAttrFmtList;

typedef union {
    volatile u8 u8;
    volatile u32 u32;
} GXFifoObj;

volatile GXFifoObj GXWGFifo : 0xCC008000;

// Real Dolphin SDK global GX state (gx). Only the fields these functions touch are declared. The rest is padding to keep their offsets correct.
typedef struct {
    u8 pad0[0x1C];
    u32 vatA[8];
    u32 vatB[8];
    u32 vatC[8];
    u8 pad1[0x80 - 0x7C];
    u32 matIdxA;
    u32 matIdxB;
} __GXDataStruct;

extern __GXDataStruct* const __GXData;

extern void __GXSetMatrixIndex(int index);

#define GET_REG_FIELD(reg, size, shift) (((reg) >> (shift)) & ((1 << (size)) - 1))

#define SET_REG_FIELD(reg, size, shift, val)               \
    (reg) = (u32)__rlwimi((int)(reg), (int)(val), (shift), \
                          (32 - (shift) - (size)), (31 - (shift)))

void GXGetVtxAttrFmt(int vtxfmt, GXAttr attr, GXCompCnt* cnt, GXCompType* type, u8* frac)
{
    u32* va = &__GXData->vatA[vtxfmt];
    u32* vb = &__GXData->vatB[vtxfmt];
    u32* vc = &__GXData->vatC[vtxfmt];
    u8 f;

    switch (attr) {
    case 9:
        *cnt = GET_REG_FIELD(*va, 1, 0);
        *type = GET_REG_FIELD(*va, 3, 1);
        *frac = GET_REG_FIELD(*va, 5, 4);
        return;
    case 10:
    case 25:
        *cnt = GET_REG_FIELD(*va, 1, 9);
        if (*cnt == 1 && (*va >> 31) != 0) {
            *cnt = 2;
        }
        *type = GET_REG_FIELD(*va, 3, 10);
        switch (*type) {
        case 1:
            f = 6;
            break;
        case 3:
            f = 14;
            break;
        default:
            f = 0;
            break;
        }
        *frac = f;
        return;
    case 11:
        *cnt = GET_REG_FIELD(*va, 1, 13);
        *type = GET_REG_FIELD(*va, 3, 14);
        *frac = 0;
        return;
    case 12:
        *cnt = GET_REG_FIELD(*va, 1, 17);
        *type = GET_REG_FIELD(*va, 3, 18);
        *frac = 0;
        return;
    case 13:
        *cnt = GET_REG_FIELD(*va, 1, 21);
        *type = GET_REG_FIELD(*va, 3, 22);
        *frac = GET_REG_FIELD(*va, 5, 25);
        return;
    case 14:
        *cnt = GET_REG_FIELD(*vb, 1, 0);
        *type = GET_REG_FIELD(*vb, 3, 1);
        *frac = GET_REG_FIELD(*vb, 5, 4);
        return;
    case 15:
        *cnt = GET_REG_FIELD(*vb, 1, 9);
        *type = GET_REG_FIELD(*vb, 3, 10);
        *frac = GET_REG_FIELD(*vb, 5, 13);
        return;
    case 16:
        *cnt = GET_REG_FIELD(*vb, 1, 18);
        *type = GET_REG_FIELD(*vb, 3, 19);
        *frac = GET_REG_FIELD(*vb, 5, 22);
        return;
    case 17:
        *cnt = GET_REG_FIELD(*vb, 1, 27);
        *type = GET_REG_FIELD(*vb, 3, 28);
        *frac = GET_REG_FIELD(*vc, 5, 0);
        return;
    case 18:
        *cnt = GET_REG_FIELD(*vc, 1, 5);
        *type = GET_REG_FIELD(*vc, 3, 6);
        *frac = GET_REG_FIELD(*vc, 5, 9);
        return;
    case 19:
        *cnt = GET_REG_FIELD(*vc, 1, 14);
        *type = GET_REG_FIELD(*vc, 3, 15);
        *frac = GET_REG_FIELD(*vc, 5, 18);
        return;
    case 20:
        *cnt = GET_REG_FIELD(*vc, 1, 23);
        *type = GET_REG_FIELD(*vc, 3, 24);
        *frac = *vc >> 27;
        return;
    default:
        *cnt = 1;
        *type = 0;
        *frac = 0;
        return;
    }
}

void GXGetVtxAttrFmtv(int vtxfmt, GXVtxAttrFmtList* vat)
{
    GXAttr attr;

    for (attr = 9; attr <= 20; attr++) {
        vat->attr = attr;
        GXGetVtxAttrFmt(vtxfmt, attr, &vat->cnt, &vat->type, &vat->frac);
        vat++;
    }
    vat->attr = 0xFF;
}

void GXSetArray(int attr, const void* base_ptr, u8 stride)
{
    int cpAttr;
    u32 phyAddr;

    attr;
    if (attr == 0x19) {
        attr = 0xA;
    }
    cpAttr = attr - 9;
    phyAddr = (u32)base_ptr & 0x3FFFFFFF;
    GXWGFifo.u8 = 8;
    GXWGFifo.u8 = cpAttr | 0xA0;
    GXWGFifo.u32 = phyAddr;
    GXWGFifo.u8 = 8;
    GXWGFifo.u8 = cpAttr | 0xB0;
    GXWGFifo.u32 = stride;
}

void GXInvalidateVtxCache(void)
{
    GXWGFifo.u8 = 0x48;
}

void GXSetTexCoordGen2(int dst_coord, int func, int src_param, u32 mtx, u8 normalize, u32 pt_texmtx)
{
    u32 reg = 0;
    u32 row;
    u32 form;

    form = 0;
    row = 5;
    switch (src_param) {
    case 0:
        row = 0;
        form = 1;
        break;
    case 1:
        row = 1;
        form = 1;
        break;
    case 2:
        row = 3;
        form = 1;
        break;
    case 3:
        row = 4;
        form = 1;
        break;
    case 19:
        row = 2;
        break;
    case 20:
        row = 2;
        break;
    case 4:
        row = 5;
        break;
    case 5:
        row = 6;
        break;
    case 6:
        row = 7;
        break;
    case 7:
        row = 8;
        break;
    case 8:
        row = 9;
        break;
    case 9:
        row = 10;
        break;
    case 10:
        row = 11;
        break;
    case 11:
        row = 12;
        break;
    default:
        break;
    }
    switch (func) {
    case 1:
        SET_REG_FIELD(reg, 1, 1, 0);
        SET_REG_FIELD(reg, 1, 2, form);
        SET_REG_FIELD(reg, 3, 4, 0);
        SET_REG_FIELD(reg, 5, 7, row);
        break;
    case 0:
        SET_REG_FIELD(reg, 1, 1, 1);
        SET_REG_FIELD(reg, 1, 2, form);
        SET_REG_FIELD(reg, 3, 4, 0);
        SET_REG_FIELD(reg, 5, 7, row);
        break;
    case 2:
    case 3:
    case 4:
    case 5:
    case 6:
    case 7:
    case 8:
    case 9:
        SET_REG_FIELD(reg, 1, 1, 0);
        SET_REG_FIELD(reg, 1, 2, form);
        SET_REG_FIELD(reg, 3, 4, 1);
        SET_REG_FIELD(reg, 5, 7, row);
        SET_REG_FIELD(reg, 3, 12, src_param - 12);
        SET_REG_FIELD(reg, 3, 15, func - 2);
        break;
    case 10:
        SET_REG_FIELD(reg, 1, 1, 0);
        SET_REG_FIELD(reg, 1, 2, form);
        if (src_param == 19) {
            SET_REG_FIELD(reg, 3, 4, 2);
        } else {
            SET_REG_FIELD(reg, 3, 4, 3);
        }
        SET_REG_FIELD(reg, 5, 7, 2);
        break;
    default:
        break;
    }
    GXWGFifo.u8 = 0x10;
    GXWGFifo.u32 = dst_coord + 0x1040;
    GXWGFifo.u32 = reg;
    reg = 0;
    SET_REG_FIELD(reg, 6, 0, pt_texmtx - 64);
    SET_REG_FIELD(reg, 1, 8, normalize);
    GXWGFifo.u8 = 0x10;
    GXWGFifo.u32 = dst_coord + 0x1050;
    GXWGFifo.u32 = reg;
    switch (dst_coord) {
    case 0:
        SET_REG_FIELD(__GXData->matIdxA, 6, 6, mtx);
        break;
    case 1:
        SET_REG_FIELD(__GXData->matIdxA, 6, 12, mtx);
        break;
    case 2:
        SET_REG_FIELD(__GXData->matIdxA, 6, 18, mtx);
        break;
    case 3:
        SET_REG_FIELD(__GXData->matIdxA, 6, 24, mtx);
        break;
    case 4:
        SET_REG_FIELD(__GXData->matIdxB, 6, 0, mtx);
        break;
    case 5:
        SET_REG_FIELD(__GXData->matIdxB, 6, 6, mtx);
        break;
    case 6:
        SET_REG_FIELD(__GXData->matIdxB, 6, 12, mtx);
        break;
    default:
        SET_REG_FIELD(__GXData->matIdxB, 6, 18, mtx);
        break;
    }
    __GXSetMatrixIndex(dst_coord + 1);
}
