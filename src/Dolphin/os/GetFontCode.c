typedef unsigned char u8;
typedef unsigned short u16;

extern u16 lbl_804DD198[];
extern u16 lbl_804DD318[];

static inline int IsSjisTrailByte(u8 c)
{
    return (c >= 0x40 && c <= 0xFC && c != 0x7F);
}

int GetFontCode(u16 encode, u16 code)
{
    if (encode == 1) {
        if (code >= 0x20 && code <= 0xDF) {
            return lbl_804DD198[code - 0x20];
        }

        if (code > 0x889E && code <= 0x9872) {
            int i = ((code >> 8) - 0x88) * 188;
            int j = code & 0xFF;

            if (!IsSjisTrailByte(j)) {
                return 0;
            }
            j -= 0x40;
            if (j >= 0x40) {
                j--;
            }
            return i + j + 0x2BE;
        }

        if (code >= 0x8140 && code < 0x879E) {
            int i = ((code >> 8) - 0x81) * 188;
            int j = code & 0xFF;

            if (!IsSjisTrailByte(j)) {
                return 0;
            }
            j -= 0x40;
            if (j >= 0x40) {
                j--;
            }
            return lbl_804DD318[i + j];
        }
    } else if (code > 0x20 && code <= 0xFF) {
        return code - 0x20;
    }
    return 0;
}
