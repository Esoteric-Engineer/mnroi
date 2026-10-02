typedef unsigned short u16;

extern void ParseStringS(void);
extern volatile u16 __VIRegs[0x100] : 0xCC002000;

u16 FontEncode = 0xFFFF;
void (*ParseString)(void);
void* FontDataSjis[2];
void* FontDataAnsi;

u16 OSGetFontEncode(void)
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
