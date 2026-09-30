// These GXTexture.c functions share a translation unit.
// Their switch jump tables are packed back to back in .data (0x804D2F88 through 0x804D32A0) with no alignment padding, and MWCC always gives .data 8-byte alignment.
//
// The unit owns its .sdata2 literal pool (see splits.txt).
// dtk's bake-sda rewrites every .sdata2 access into a fixed r13 offset and drops the relocation. This leaves the pool unreferenced and lets mwld dead-strip it.
// force_active keeps it linked, and also keeps __GXGetTexTileShift, whose only callers inline it.
#pragma force_active on

typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned long u32;
typedef float f32;

typedef int GXTexFmt;
typedef int GXTexWrapMode;

typedef struct {
    u32 mode0;
    u32 mode1;
    u32 image0;
    u32 image3;
    void* userData;
    GXTexFmt fmt;
    u32 tlutName;
    u16 loadCnt;
    u8 loadFmt;
    u8 flags;
} GXTexObj;

extern void* memset(void* dst, int val, u32 n);

// GXTexture.c's .sdata: GXLoadTexObjPreLoaded.c (a different unit) externs the Ids tables.
// HW2GXFiltConv is unreferenced anywhere, kept alive by force_active above.
u8 GXTexMode0Ids[8] = { 0x80, 0x81, 0x82, 0x83, 0xA0, 0xA1, 0xA2, 0xA3 };
u8 GXTexMode1Ids[8] = { 0x84, 0x85, 0x86, 0x87, 0xA4, 0xA5, 0xA6, 0xA7 };
u8 GXTexImage0Ids[8] = { 0x88, 0x89, 0x8A, 0x8B, 0xA8, 0xA9, 0xAA, 0xAB };
u8 GXTexImage1Ids[8] = { 0x8C, 0x8D, 0x8E, 0x8F, 0xAC, 0xAD, 0xAE, 0xAF };
u8 GXTexImage2Ids[8] = { 0x90, 0x91, 0x92, 0x93, 0xB0, 0xB1, 0xB2, 0xB3 };
u8 GXTexImage3Ids[8] = { 0x94, 0x95, 0x96, 0x97, 0xB4, 0xB5, 0xB6, 0xB7 };
u8 GXTexTlutIds[8] = { 0x98, 0x99, 0x9A, 0x9B, 0xB8, 0xB9, 0xBA, 0xBB };

#define SET_REG_FIELD(reg, size, shift, val)               \
    (reg) = (u32)__rlwimi((int)(reg), (int)(val), (shift), \
                          (32 - (shift) - (size)), (31 - (shift)))

void __GXGetTexTileShift(GXTexFmt fmt, u32* rowTileS, u32* colTileS)
{
    switch (fmt) {
    case 0x0:
    case 0x8:
    case 0xE:
    case 0x20:
    case 0x30:
        *rowTileS = 3;
        *colTileS = 3;
        break;
    case 0x1:
    case 0x2:
    case 0x9:
    case 0x11:
    case 0x22:
    case 0x27:
    case 0x28:
    case 0x29:
    case 0x2A:
    case 0x39:
    case 0x3A:
        *rowTileS = 3;
        *colTileS = 2;
        break;
    case 0x3:
    case 0x4:
    case 0x5:
    case 0x6:
    case 0xA:
    case 0x13:
    case 0x16:
    case 0x23:
    case 0x2B:
    case 0x2C:
    case 0x3C:
        *rowTileS = 2;
        *colTileS = 2;
        break;
    default:
        *rowTileS = *colTileS = 0;
        break;
    }
}

u32 GXGetTexBufferSize(u16 width, u16 height, u32 format, u8 mipmap, u8 max_lod)
{
    u32 tileShiftX;
    u32 tileShiftY;
    u32 tileBytes;
    u32 bufferSize;
    u32 nx;
    u32 ny;
    u32 level;

    __GXGetTexTileShift(format, &tileShiftX, &tileShiftY);
    if (format == 6 || format == 0x16) {
        tileBytes = 64;
    } else {
        tileBytes = 32;
    }
    if (mipmap == 1) {
        bufferSize = 0;
        for (level = 0; level < max_lod; level++) {
            nx = (width + (1 << tileShiftX) - 1) >> tileShiftX;
            ny = (height + (1 << tileShiftY) - 1) >> tileShiftY;
            bufferSize += tileBytes * (nx * ny);
            if (width == 1 && height == 1) {
                break;
            }
            width = (width > 1) ? width >> 1 : 1;
            height = (height > 1) ? height >> 1 : 1;
        }
    } else {
        nx = (width + (1 << tileShiftX) - 1) >> tileShiftX;
        ny = (height + (1 << tileShiftY) - 1) >> tileShiftY;
        bufferSize = nx * ny * tileBytes;
    }
    return bufferSize;
}

void __GetImageTileCount(GXTexFmt fmt, u16 wd, u16 ht, u32* rowTiles, u32* colTiles, u32* cmpTiles)
{
    u32 texRowShift;
    u32 texColShift;

    __GXGetTexTileShift(fmt, &texRowShift, &texColShift);
    if (wd == 0) {
        wd = 1;
    }
    if (ht == 0) {
        ht = 1;
    }
    *rowTiles = (wd + (1 << texRowShift) - 1) >> texRowShift;
    *colTiles = (ht + (1 << texColShift) - 1) >> texColShift;
    *cmpTiles = (fmt == 6 || fmt == 0x16) ? 2 : 1;
}

void GXInitTexObj(GXTexObj* obj, void* image_ptr, u16 width, u16 height, GXTexFmt format,
                  GXTexWrapMode wrap_s, GXTexWrapMode wrap_t, u8 mipmap)
{
    u32 f;
    u32 imageBase;
    u32 maxLOD;
    u16 rowT;
    u16 colT;
    u32 rowC;
    u32 colC;
    GXTexObj* t = obj;

    memset(t, 0, 0x20);
    SET_REG_FIELD(t->mode0, 2, 0, wrap_s);
    SET_REG_FIELD(t->mode0, 2, 2, wrap_t);
    SET_REG_FIELD(t->mode0, 1, 4, 1);
    if (mipmap != 0) {
        u8 lmax;
        t->flags |= 1;
        if (format == 8 || format == 9 || format == 10) {
            SET_REG_FIELD(t->mode0, 3, 5, 5);
        } else {
            SET_REG_FIELD(t->mode0, 3, 5, 6);
        }
        if (width > height) {
            maxLOD = 31 - __cntlzw(width);
        } else {
            maxLOD = 31 - __cntlzw(height);
        }
        lmax = 16.0f * maxLOD;
        SET_REG_FIELD(t->mode1, 8, 8, lmax);
    } else {
        SET_REG_FIELD(t->mode0, 3, 5, 4);
    }
    f = format & 0xF;
    t->fmt = format;
    SET_REG_FIELD(t->image0, 10, 0, width - 1);
    SET_REG_FIELD(t->image0, 10, 10, height - 1);
    SET_REG_FIELD(t->image0, 4, 20, f);
    imageBase = ((u32)image_ptr >> 5) & 0x01FFFFFF;
    SET_REG_FIELD(t->image3, 21, 0, imageBase);
    switch (f) {
    case 0:
    case 8:
        t->loadFmt = 1;
        rowT = 3;
        colT = 3;
        break;
    case 1:
    case 2:
    case 9:
        t->loadFmt = 2;
        rowT = 3;
        colT = 2;
        break;
    case 3:
    case 4:
    case 5:
    case 10:
        t->loadFmt = 2;
        rowT = 2;
        colT = 2;
        break;
    case 6:
        t->loadFmt = 3;
        rowT = 2;
        colT = 2;
        break;
    case 14:
        t->loadFmt = 0;
        rowT = 3;
        colT = 3;
        break;
    default:
        t->loadFmt = 2;
        rowT = 2;
        colT = 2;
        break;
    }
    rowC = (width + (1 << rowT) - 1) >> rowT;
    colC = (height + (1 << colT) - 1) >> colT;
    t->loadCnt = (rowC * colC) & 0x7FFF;
    t->flags |= 2;
}

void GXInitTexObjCI(GXTexObj* obj, void* image_ptr, u16 width, u16 height, GXTexFmt format,
                    GXTexWrapMode wrap_s, GXTexWrapMode wrap_t, u8 mipmap, u32 tlut_name)
{
    GXInitTexObj(obj, image_ptr, width, height, format, wrap_s, wrap_t, mipmap);
    obj->flags &= 0xFFFFFFFD;
    obj->tlutName = tlut_name;
}

u8 GX2HWFiltConv[8] = { 0x00, 0x04, 0x01, 0x05, 0x02, 0x06 };
u8 HW2GXFiltConv[8] = { 0x00, 0x02, 0x04, 0x00, 0x01, 0x03, 0x05, 0x00 };

void GXInitTexObjLOD(GXTexObj* obj, int min_filt, int mag_filt, f32 min_lod, f32 max_lod,
                     f32 lod_bias, u8 bias_clamp, u8 do_edge_lod, int max_aniso)
{
    u8 lbias;
    u8 lmin;
    u8 lmax;
    GXTexObj* t = obj;

    if (lod_bias < -4.0f) {
        lod_bias = -4.0f;
    } else if (lod_bias >= 4.0f) {
        lod_bias = 3.99f;
    }
    lbias = 32.0f * lod_bias;
    SET_REG_FIELD(t->mode0, 8, 9, lbias);
    SET_REG_FIELD(t->mode0, 1, 4, (mag_filt == 1) ? 1 : 0);
    SET_REG_FIELD(t->mode0, 3, 5, GX2HWFiltConv[min_filt]);
    SET_REG_FIELD(t->mode0, 1, 8, do_edge_lod ? 0 : 1);
    SET_REG_FIELD(t->mode0, 1, 17, 0);
    SET_REG_FIELD(t->mode0, 1, 18, 0);
    SET_REG_FIELD(t->mode0, 2, 19, max_aniso);
    SET_REG_FIELD(t->mode0, 1, 21, bias_clamp);
    if (min_lod < 0.0f) {
        min_lod = 0.0f;
    } else if (min_lod > 10.0f) {
        min_lod = 10.0f;
    }
    lmin = 16.0f * min_lod;
    if (max_lod < 0.0f) {
        max_lod = 0.0f;
    } else if (max_lod > 10.0f) {
        max_lod = 10.0f;
    }
    lmax = 16.0f * max_lod;
    SET_REG_FIELD(t->mode1, 8, 0, lmin);
    SET_REG_FIELD(t->mode1, 8, 8, lmax);
}

// GXGetTexObjMinLOD (GXTexture.c) reads this by a hardcoded r13 offset, not by symbol, so no extern is needed here.
// The rest are unreferenced, kept alive by force_active above.
const f32 GXTexObjMinLodScaleConst = 0.0625f;
const f32 GXTexturePoolConst1 = 0.03125f;
const f32 GXTexturePoolConst2 = 176.0f;
const f32 GXTexturePoolConst3 = -0.0f;
