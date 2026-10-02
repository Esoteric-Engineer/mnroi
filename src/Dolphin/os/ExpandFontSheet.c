typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned long u32;
typedef long s32;

typedef struct OSFontHeader {
    u16 fontType;
    u16 firstChar;
    u16 lastChar;
    u16 invalChar;
    u16 ascent;
    u16 descent;
    u16 width;
    u16 leading;
    u16 cellWidth;
    u16 cellHeight;
    u32 sheetSize;
    u16 sheetFormat;
    u16 sheetColumn;
    u16 sheetRow;
    u16 sheetWidth;
    u16 sheetHeight;
    u16 widthTable;
    u32 sheetImage;
    u32 sheetFullSize;
    u8 c0;
    u8 c1;
    u8 c2;
    u8 c3;
} OSFontHeader;

extern void DCStoreRange(void* addr, u32 nBytes);

void ExpandFontSheet(OSFontHeader* font, u8* src, u8* dst)
{
    int i;
    u8* colorIndex = &font->c0;

    if (font->sheetFormat == 0 /* GX_TF_I4 */) {
        for (i = (s32)(font->sheetFullSize) / 2 - 1; i >= 0; i--) {
            dst[i * 2 + 0] = colorIndex[src[i] >> 6 & 3] & 0xF0
                             | colorIndex[src[i] >> 4 & 3] & 0x0F;
            dst[i * 2 + 1] = colorIndex[src[i] >> 2 & 3] & 0xF0
                             | colorIndex[src[i] >> 0 & 3] & 0x0F;
        }
    } else if (font->sheetFormat == 2 /* GX_TF_IA4 */) {
        for (i = (s32)(font->sheetFullSize) / 4 - 1; i >= 0; i--) {
            dst[i * 4 + 0] = colorIndex[src[i] >> 6 & 3];
            dst[i * 4 + 1] = colorIndex[src[i] >> 4 & 3];
            dst[i * 4 + 2] = colorIndex[src[i] >> 2 & 3];
            dst[i * 4 + 3] = colorIndex[src[i] >> 0 & 3];
        }
    }

    DCStoreRange(dst, font->sheetFullSize);
}
