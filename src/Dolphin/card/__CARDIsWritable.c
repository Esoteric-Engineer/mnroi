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
    u8 pad[0x34 - 6];
    u8 permission;
    u8 pad1[0x40 - 0x35];
} CARDDir;

extern DVDDiskID __CARDDiskNone;
extern u8 __CARDPermMask;
extern int memcmp(const void* a, const void* b, unsigned long n);

s32 __CARDIsWritable(CARDControl* card, CARDDir* ent)
{
    s32 result;
    DVDDiskID* diskID = card->diskID;
    u8 perm;

    if (ent->gameName[0] == 0xFF) {
        result = -4;
    } else if (diskID == &__CARDDiskNone
               || (memcmp(ent->gameName, diskID->gameName, sizeof(ent->gameName)) == 0
                   && memcmp(ent->company, diskID->company, sizeof(ent->company)) == 0)) {
        result = 0;
    } else {
        result = -10;
    }

    if (result == -10) {
        perm = ent->permission & __CARDPermMask;
        if ((perm & 0x20)
            && memcmp(ent->gameName, __CARDDiskNone.gameName, sizeof(ent->gameName)) == 0
            && memcmp(ent->company, __CARDDiskNone.company, sizeof(ent->company)) == 0)
            return 0;
        if ((perm & 0x40)
            && memcmp(ent->gameName, __CARDDiskNone.gameName, sizeof(ent->gameName)) == 0
            && memcmp(ent->company, diskID->company, sizeof(ent->company)) == 0)
            return 0;
    }
    return result;
}
