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
    u8 pad0[0x80];
    u32 matIdxA;
    u32 matIdxB;
} __GXDataStruct;

extern __GXDataStruct* const __GXData;

extern void __GXSetMatrixIndex(int index);

#define SET_REG_FIELD(reg, size, shift, val)               \
    (reg) = (u32)__rlwimi((int)(reg), (int)(val), (shift), \
                          (32 - (shift) - (size)), (31 - (shift)))

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
