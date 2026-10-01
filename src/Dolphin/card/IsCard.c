typedef long s32;
typedef unsigned long u32;
typedef unsigned short u16;
typedef unsigned char u8;

u16 __CARDVendorID = 0xFFFF;
u8 __CARDPermMask = 0x1C;

s32 SectorSizeTable[8] = {
    0x2000, 0x4000, 0x8000, 0x10000, 0x20000, 0x40000, 0, 0,
};

s32 LatencyTable[8] = {
    4, 8, 0x10, 0x20, 0x40, 0x80, 0x100, 0x200,
};

s32 IsCard(u32 id)
{
    u32 size;
    s32 sectorSize;

    if (id & 0xFFFF0000 && (id != 0x80000004 || __CARDVendorID == 0xFFFF)) {
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

    sectorSize = SectorSizeTable[(id & 0x3800) >> 11];
    if (sectorSize == 0) {
        return 0;
    }

    if ((size * 1024 * 1024 / 8) / sectorSize < 8) {
        return 0;
    }

    return 1;
}
