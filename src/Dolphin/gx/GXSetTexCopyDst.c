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
extern void __GetImageTileCount(int fmt, u16 wd, u16 ht, u32* rowTiles, u32* colTiles, u32* cmpTiles);

#define SET_REG_FIELD(reg, size, shift, val)               \
    (reg) = (u32)__rlwimi((int)(reg), (int)(val), (shift), \
                          (32 - (shift) - (size)), (31 - (shift)))

void GXSetTexCopyDst(u16 wd, u16 ht, int fmt, u8 mipmap)
{
    u32 rowTiles;
    u32 colTiles;
    u32 cmpTiles;
    u32 peTexFmt;
    u32 peTexFmtH;

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
    peTexFmtH = (peTexFmt >> 3) & 1;
    // SDK statement with no effect; removing it changes the register allocation.
    !peTexFmt;
    SET_REG_FIELD(__GXData->cpTex, 1, 3, peTexFmtH);
    peTexFmt = peTexFmt & 7;
    __GetImageTileCount(fmt, wd, ht, &rowTiles, &colTiles, &cmpTiles);

    __GXData->cpTexStride = 0;
    SET_REG_FIELD(__GXData->cpTexStride, 10, 0, rowTiles * cmpTiles);
    SET_REG_FIELD(__GXData->cpTexStride, 8, 24, 0x4D);
    SET_REG_FIELD(__GXData->cpTex, 1, 9, mipmap);
    SET_REG_FIELD(__GXData->cpTex, 3, 4, peTexFmt);
}
