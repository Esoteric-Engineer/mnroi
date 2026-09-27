#pragma force_active on

typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned long u32;
typedef long s32;
typedef int BOOL;

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

extern BOOL __OSReadROM(void* buffer, long length, long offset);
extern void Decode(u8* s, u8* d);
extern int GetFontCode(u16 encode, u16 code);

static inline void ReadROM(void* buf, s32 length, s32 offset)
{
    s32 len;
    while (length > 0) {
        len = (length <= 0x100) ? length : 0x100;
        length -= len;

        while (!__OSReadROM(buf, len, offset)) {
            ;
        }

        offset += len;
        (u8*)buf += len;
    }
}

static inline u32 GetFontSize(u8* buf)
{
    if (buf[0] == 'Y' && buf[1] == 'a' && buf[2] == 'y') {
        return *(u32*)(buf + 0x4);
    }
    return 0;
}

u32 ReadFont(void* img, u16 encode, OSFontHeader* fontData)
{
    u32 size;
    u8* src;
    int column;
    u8* imageSrc;
    int x;
    u8* dst;
    int fontCode;
    int y;
    int sheet;
    int numChars;
    int row;

    if (encode == 1) {
        ReadROM(img, 0x4D000, 0x1AFF00);
    } else {
        ReadROM(img, 0x3000, 0x1FCF00);
    }

    size = GetFontSize(img);
    if (size == 0) {
        return 0;
    }

    Decode(img, (u8*)fontData);

    if (encode == 1) {
        u16 patch[4] = { 0x2ABE, 0x003D, 0x003D, 0x003D };
        fontCode = GetFontCode(encode, 0x54);
        sheet = fontCode / (fontData->sheetColumn * fontData->sheetRow);
        numChars = fontCode - sheet * (fontData->sheetColumn * fontData->sheetRow);
        row = numChars / fontData->sheetColumn;
        column = numChars - row * fontData->sheetColumn;
        row *= fontData->cellHeight;
        column *= fontData->cellWidth;
        imageSrc = (u8*)fontData + fontData->sheetImage;
        imageSrc += (sheet * fontData->sheetSize) / 2;

        for (y = 4; y < 8; y++) {
            src = imageSrc + (((fontData->sheetWidth / 8) * 32) / 2) * ((row + y) / 8);
            src += (column / 8) * 16;
            src += ((row + y) % 8) * 2;
            src += (column % 8) / 4;
            *(u16*)src = patch[y - 4];
        }
    }

    return size;
}
