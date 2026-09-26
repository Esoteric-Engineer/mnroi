typedef unsigned char u8;
typedef long s32;

typedef struct DVDDiskID {
    u8 gameName[4];
    u8 company[2];
    u8 pad[0x20 - 6];
} DVDDiskID;

typedef struct CARDControl {
    s32 attached;
    u8 pad1[0x10C - 4];
    DVDDiskID* diskID;
} CARDControl;

typedef struct CARDDir {
    u8 gameName[4];
    u8 company[2];
    u8 pad0[2];
    u8 fileName[32];
    u8 pad1[0x40 - 0x28];
} CARDDir;

extern DVDDiskID __CARDDiskNone;
extern int memcmp(const void* a, const void* b, unsigned long n);
extern CARDDir* __CARDGetDirBlock(CARDControl* card);

static inline s32 CARDAccess(CARDControl* card, CARDDir* ent)
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

static inline int CompareFileName(CARDDir* ent, const char* fileName)
{
    char* entName = (char*)ent->fileName;
    char c1;
    char c2;
    int n = 32;

    while (--n >= 0) {
        if ((c1 = *entName++) != (c2 = *fileName++)) {
            return 0;
        } else if (c2 == '\0') {
            return 1;
        }
    }

    if (*fileName == '\0') {
        return 1;
    }
    return 0;
}

s32 __CARDGetFileNo(CARDControl* card, const char* fileName, s32* pfileNo)
{
    CARDDir* dir;
    s32 fileNo;

    if (!card->attached)
        return -3;

    dir = __CARDGetDirBlock(card);
    for (fileNo = 0; fileNo < 127; fileNo++) {
        CARDDir* ent = &dir[fileNo];
        s32 result = CARDAccess(card, ent);

        if (result < 0)
            continue;
        if (CompareFileName(ent, fileName)) {
            *pfileNo = fileNo;
            return 0;
        }
    }
    return -4;
}
