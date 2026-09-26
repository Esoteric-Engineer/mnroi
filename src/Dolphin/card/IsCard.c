typedef long s32;
typedef unsigned long u32;
typedef unsigned short u16;

extern u16 lbl_8066CEF8;
extern s32 lbl_804F2BD8[8];

s32 IsCard(u32 id)
{
    u32 size;
    s32 sectorSize;

    if (id & 0xFFFF0000 && (id != 0x80000004 || lbl_8066CEF8 == 0xFFFF)) {
        return 0;
    }

    if ((id & 3) != 0) {
        return 0;
    }

    size = id & 0xFC;
    switch (size) {
    case 4:
    case 8:
    case 16:
    case 32:
    case 64:
    case 128:
        break;
    default:
        return 0;
    }

    sectorSize = lbl_804F2BD8[(id & 0x3800) >> 11];
    if (sectorSize == 0) {
        return 0;
    }

    if ((size * 1024 * 1024 / 8) / sectorSize < 8) {
        return 0;
    }

    return 1;
}
