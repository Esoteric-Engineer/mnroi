typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned long u32;
typedef long s32;
typedef int BOOL;

#define FALSE 0
#define TRUE 1

typedef struct CARDDir {
    u8 gameName[4];
    u8 company[2];
    u8 pad0;
    u8 bannerFormat;
    u8 fileName[0x20];
    u32 time;
    u32 iconAddr;
    u16 iconFormat;
    u16 iconSpeed;
    u8 pad1[0x38 - 0x34];
    u16 length;
    u8 pad2[0x3C - 0x3A];
    u32 commentAddr;
} CARDDir;

typedef struct CARDStat {
    u8 fileName[0x20];
    u32 length;
    u32 time;
    u8 gameName[4];
    u8 company[2];
    u8 bannerFormat;
    u8 pad0;
    u32 iconAddr;
    u16 iconFormat;
    u16 iconSpeed;
    u32 commentAddr;
    u32 offsetBanner;
    u32 offsetBannerTlut;
    u32 offsetIcon[8];
    u32 offsetIconTlut;
    u32 offsetData;
} CARDStat;

#define CARDGetBannerFormat(stat) (((stat)->bannerFormat) & 3)
#define CARDGetIconFormat(stat, n) (((stat)->iconFormat >> (2 * (n))) & 3)

void UpdateIconOffsets(CARDDir* ent, CARDStat* stat)
{
    u32 offset;
    BOOL iconTlut;
    int i;

    offset = ent->iconAddr;
    if (offset == 0xffffffff) {
        stat->bannerFormat = 0;
        stat->iconFormat = 0;
        stat->iconSpeed = 0;
        offset = 0;
    }

    iconTlut = FALSE;
    switch (CARDGetBannerFormat(ent)) {
    case 1:
        stat->offsetBanner = offset;
        offset += 96 * 32;
        stat->offsetBannerTlut = offset;
        offset += 2 * 256;
        break;
    case 2:
        stat->offsetBanner = offset;
        offset += 2 * 96 * 32;
        stat->offsetBannerTlut = 0xffffffff;
        break;
    default:
        stat->offsetBanner = 0xffffffff;
        stat->offsetBannerTlut = 0xffffffff;
        break;
    }
    for (i = 0; i < 8; ++i) {
        switch (CARDGetIconFormat(ent, i)) {
        case 1:
            stat->offsetIcon[i] = offset;
            offset += 32 * 32;
            iconTlut = TRUE;
            break;
        case 2:
            stat->offsetIcon[i] = offset;
            offset += 2 * 32 * 32;
            break;
        default:
            stat->offsetIcon[i] = 0xffffffff;
            break;
        }
    }
    if (iconTlut) {
        stat->offsetIconTlut = offset;
        offset += 2 * 256;
    } else {
        stat->offsetIconTlut = 0xffffffff;
    }
    stat->offsetData = offset;
}
