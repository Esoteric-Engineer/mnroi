typedef unsigned char u8;
typedef long s32;

typedef struct DVDDiskID {
    u8 gameName[4];
    u8 company[2];
    u8 pad[0x20 - 6];
} DVDDiskID;

typedef struct CARDControl {
    u8 pad0[0x10C];
    DVDDiskID* diskID;
} CARDControl;

typedef struct CARDDir {
    u8 gameName[4];
    u8 company[2];
    u8 pad[0x40 - 6];
} CARDDir;

extern DVDDiskID __CARDDiskNone;
extern int memcmp(const void* a, const void* b, unsigned long n);

s32 __CARDAccess(CARDControl* card, CARDDir* ent)
{
    DVDDiskID* diskID = card->diskID;

    if (ent->gameName[0] == 0xFF)
        return -4;

    if (diskID == &__CARDDiskNone
        || (memcmp(ent->gameName, diskID->gameName, sizeof(ent->gameName)) == 0
            && memcmp(ent->company, diskID->company, sizeof(ent->company)) == 0))
        return 0;

    return -10;
}
