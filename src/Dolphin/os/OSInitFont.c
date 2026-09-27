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
extern OSFontHeader* lbl_8066F9A8;
extern OSFontHeader* lbl_8066F9AC;
extern volatile u16 __VIRegs[0x100] : 0xCC002000;

extern u32 ReadFont(void* src, u16 encode, OSFontHeader* dst);
extern void fn_8040394C(OSFontHeader* font, u8* src, u8* dst);

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

int OSInitFont(OSFontHeader* fontData)
{
    u8* data;
    u8* src;

    switch (GetFontEncode()) {
    case 0:
        lbl_8066F9A8 = fontData;
        data = (u8*)fontData + 0x1D120;
        if (ReadFont(data, 0, lbl_8066F9A8) == 0) {
            return 0;
        }
        src = (u8*)lbl_8066F9A8 + lbl_8066F9A8->sheetImage;
        lbl_8066F9A8->sheetImage = (lbl_8066F9A8->sheetImage + 0x1F) & ~0x1F;
        fn_8040394C(lbl_8066F9A8, src, (u8*)lbl_8066F9A8 + lbl_8066F9A8->sheetImage);
        break;
    case 1:
        lbl_8066F9AC = fontData;
        data = (u8*)fontData + 0xD3F00;
        if (ReadFont(data, 1, lbl_8066F9AC) == 0) {
            return 0;
        }
        src = (u8*)lbl_8066F9AC + lbl_8066F9AC->sheetImage;
        lbl_8066F9AC->sheetImage = (lbl_8066F9AC->sheetImage + 0x1F) & ~0x1F;
        fn_8040394C(lbl_8066F9AC, src, (u8*)lbl_8066F9AC + lbl_8066F9AC->sheetImage);
        break;
    case 3:
    case 4:
    case 5:
        lbl_8066F9A8 = fontData;
        data = (u8*)fontData + 0xF4020;
        if (ReadFont(data, 0, lbl_8066F9A8) == 0) {
            return 0;
        }
        src = (u8*)lbl_8066F9A8 + lbl_8066F9A8->sheetImage;
        lbl_8066F9A8->sheetImage = (lbl_8066F9A8->sheetImage + 0x1F) & ~0x1F;
        fn_8040394C(lbl_8066F9A8, src, (u8*)lbl_8066F9A8 + lbl_8066F9A8->sheetImage);
        lbl_8066F9AC = (OSFontHeader*)((u8*)lbl_8066F9A8 + 0x20120);
        if (ReadFont(data, 1, lbl_8066F9AC) == 0) {
            return 0;
        }
        src = (u8*)lbl_8066F9AC + lbl_8066F9AC->sheetImage;
        lbl_8066F9AC->sheetImage = (lbl_8066F9AC->sheetImage + 0x1F) & ~0x1F;
        fn_8040394C(lbl_8066F9AC, src, (u8*)lbl_8066F9AC + lbl_8066F9AC->sheetImage);
        break;
    case 2:
    default:
        break;
    }
    return 1;
}
