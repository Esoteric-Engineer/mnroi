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

extern u16 lbl_8066CEB8;
extern char* (*lbl_8066F9B4)(u16 encode, char* string, OSFontHeader** fontData, s32* fontCode);
extern char* ParseStringS(u16 encode, char* string, OSFontHeader** fontData, s32* fontCode);
extern volatile u16 __VIRegs[0x100] : 0xCC002000;

static inline u16 GetFontEncode(void)
{
    if (lbl_8066CEB8 != 0xFFFF) {
        return lbl_8066CEB8;
    }
    switch (*(int*)0x800000CC) {
    case 0:
        lbl_8066CEB8 = (__VIRegs[55] & 2) ? 1 : 0;
        break;
    case 1:
    case 2:
    case 3:
    case 4:
    case 5:
    default:
        lbl_8066CEB8 = 0;
    }
    lbl_8066F9B4 = ParseStringS;
    return lbl_8066CEB8;
}

char* OSGetFontTexture(char* string, void** image, s32* x, s32* y, s32* width)
{
    OSFontHeader* fontData;
    s32 fontCode;
    s32 sheet;
    s32 numChars;
    s32 row;
    s32 column;

    string = lbl_8066F9B4(GetFontEncode(), string, &fontData, &fontCode);
    sheet = fontCode / (fontData->sheetColumn * fontData->sheetRow);
    *image = (void*)((u32)fontData + fontData->sheetImage + fontData->sheetSize * sheet);
    numChars = fontCode - sheet * (fontData->sheetColumn * fontData->sheetRow);
    row = numChars / fontData->sheetColumn;
    column = numChars - row * fontData->sheetColumn;
    *x = column * fontData->cellWidth;
    *y = row * fontData->cellHeight;
    if (width) {
        *width = ((u8*)fontData + fontData->widthTable)[fontCode];
    }
    return string;
}
