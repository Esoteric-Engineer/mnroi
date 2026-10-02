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

extern u16 FontEncode;
extern char* (*ParseString)(u16 encode, char* string, OSFontHeader** fontData, s32* fontCode);
extern char* ParseStringS(u16 encode, char* string, OSFontHeader** fontData, s32* fontCode);
extern OSFontHeader* FontDataAnsi;
extern OSFontHeader* FontDataSjis;
extern volatile u16 __VIRegs[0x100] : 0xCC002000;

extern u32 ReadFont(void* src, u16 encode, OSFontHeader* dst);
extern void ExpandFontSheet(OSFontHeader* font, u8* src, u8* dst);

static inline u16 GetFontEncode(void)
{
    if (FontEncode != 0xFFFF) {
        return FontEncode;
    }
    switch (*(int*)0x800000CC) {
    case 0:
        FontEncode = (__VIRegs[55] & 2) ? 1 : 0;
        break;
    case 1:
    case 2:
    case 3:
    case 4:
    case 5:
    default:
        FontEncode = 0;
    }
    ParseString = ParseStringS;
    return FontEncode;
}

int OSInitFont(OSFontHeader* fontData)
{
    u8* data;
    u8* src;

    switch (GetFontEncode()) {
    case 0:
        FontDataAnsi = fontData;
        data = (u8*)fontData + 0x1D120;
        if (ReadFont(data, 0, FontDataAnsi) == 0) {
            return 0;
        }
        src = (u8*)FontDataAnsi + FontDataAnsi->sheetImage;
        FontDataAnsi->sheetImage = (FontDataAnsi->sheetImage + 0x1F) & ~0x1F;
        ExpandFontSheet(FontDataAnsi, src, (u8*)FontDataAnsi + FontDataAnsi->sheetImage);
        break;
    case 1:
        FontDataSjis = fontData;
        data = (u8*)fontData + 0xD3F00;
        if (ReadFont(data, 1, FontDataSjis) == 0) {
            return 0;
        }
        src = (u8*)FontDataSjis + FontDataSjis->sheetImage;
        FontDataSjis->sheetImage = (FontDataSjis->sheetImage + 0x1F) & ~0x1F;
        ExpandFontSheet(FontDataSjis, src, (u8*)FontDataSjis + FontDataSjis->sheetImage);
        break;
    case 3:
    case 4:
    case 5:
        FontDataAnsi = fontData;
        data = (u8*)fontData + 0xF4020;
        if (ReadFont(data, 0, FontDataAnsi) == 0) {
            return 0;
        }
        src = (u8*)FontDataAnsi + FontDataAnsi->sheetImage;
        FontDataAnsi->sheetImage = (FontDataAnsi->sheetImage + 0x1F) & ~0x1F;
        ExpandFontSheet(FontDataAnsi, src, (u8*)FontDataAnsi + FontDataAnsi->sheetImage);
        FontDataSjis = (OSFontHeader*)((u8*)FontDataAnsi + 0x20120);
        if (ReadFont(data, 1, FontDataSjis) == 0) {
            return 0;
        }
        src = (u8*)FontDataSjis + FontDataSjis->sheetImage;
        FontDataSjis->sheetImage = (FontDataSjis->sheetImage + 0x1F) & ~0x1F;
        ExpandFontSheet(FontDataSjis, src, (u8*)FontDataSjis + FontDataSjis->sheetImage);
        break;
    case 2:
    default:
        break;
    }
    return 1;
}
