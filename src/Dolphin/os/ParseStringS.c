typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned long u32;

extern void* lbl_8066F9A8;
extern void* lbl_8066F9AC;
extern u32 GetFontCode(u16 encode, u16 code);

static inline int IsSjisLeadByte(u8 c)
{
    return ((c >= 0x81 && c <= 0x9F) || (c >= 0xE0 && c <= 0xFC));
}

static inline int IsSjisTrailByte(u8 c)
{
    return (c >= 0x40 && c <= 0xFC && c != 0x7F);
}

char* ParseStringS(u16 encode, char* string, void** fontData, u32* fontCode)
{
    void* font;
    u16 code = 0;

    switch (encode) {
    case 0:
        font = lbl_8066F9A8;
        code = (u8)*string;
        if (code != 0) {
            string++;
        }
        break;
    case 1:
        font = lbl_8066F9AC;
        code = (u8)*string;
        if (code != 0) {
            string++;
            if (IsSjisLeadByte(code) && IsSjisTrailByte(*string)) {
                code = (code << 8) | (u8)*string++;
            }
        }
        break;
    }
    *fontData = font;
    *fontCode = GetFontCode(encode, code);
    return string;
}
