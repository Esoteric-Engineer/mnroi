typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned long u32;

// Real Dolphin SDK global GX state (gx). Only the fields this function touches are declared. The rest is padding to keep their offsets correct.
typedef struct {
    u8 pad0[0x1F8];
    u32 cpTexStride;
    u32 cpTex;
    u8 cpTexZ;
} __GXDataStruct;

extern __GXDataStruct* const __GXData;
extern void fn_8018DDCC(int fmt, u16 wd, u16 ht, u32* rowTiles, u32* colTiles, u32* cmpTiles);

#define SET_REG_FIELD(reg, size, shift, val)               \
    (reg) = (u32)__rlwimi((int)(reg), (int)(val), (shift), \
                          (32 - (shift) - (size)), (31 - (shift)))

void GXSetTexCopyDst(u16 wd, u16 ht, int fmt, u8 mipmap)
{
    u32 rowTiles;
    u32 colTiles;
    u32 cmpTiles;
    u32 peTexFmt;
    __GXDataStruct* gx;

    __GXData->cpTexZ = 0;
    peTexFmt = fmt & 0xF;
    if (fmt == 0x13) {
        peTexFmt = 0xB;
    }
    switch (fmt) {
    case 0:
    case 1:
    case 2:
    case 3:
    case 0x26:
        SET_REG_FIELD(__GXData->cpTex, 2, 15, 3);
        break;
    default:
        SET_REG_FIELD(__GXData->cpTex, 2, 15, 2);
        break;
    }

    __GXData->cpTexZ = (fmt & 0x10) == 0x10;
    __GXData->cpTex = (u32)__rlwimi((int)__GXData->cpTex, (int)peTexFmt, 0, 28, 28);
    peTexFmt = peTexFmt & 7;
    fn_8018DDCC(fmt, wd, ht, &rowTiles, &colTiles, &cmpTiles);

    gx = __GXData;
    gx->cpTexStride = 0;
    SET_REG_FIELD(gx->cpTexStride, 10, 0, rowTiles * cmpTiles);
    SET_REG_FIELD(gx->cpTexStride, 8, 24, 0x4D);
    SET_REG_FIELD(gx->cpTex, 1, 9, mipmap);
    SET_REG_FIELD(gx->cpTex, 3, 4, peTexFmt);
}
