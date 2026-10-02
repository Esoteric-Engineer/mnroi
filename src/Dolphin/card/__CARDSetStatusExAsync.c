typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned long u32;
typedef long s32;

typedef void (*CARDCallback)(s32, s32);

typedef struct CARDControl CARDControl;

typedef struct CARDDir {
    u8 gameName[4];
    u8 company[2];
    u8 _padding0;
    u8 bannerFormat;
    u8 fileName[32];
    u32 time;
    u32 iconAddr;
    u16 iconFormat;
    u16 iconSpeed;
    u8 permission;
    u8 copyTimes;
    u16 startBlock;
    u16 length;
    u8 _padding1[2];
    u32 commentAddr;
} CARDDir;

extern s32 __CARDGetControlBlock(s32 chan, CARDControl** card);
extern s32 __CARDPutControlBlock(CARDControl* card, s32 result);
extern CARDDir* __CARDGetDirBlock(CARDControl* card);
extern s32 __CARDIsWritable(CARDControl* card, CARDDir* ent);
extern s32 __CARDUpdateDir(s32 chan, CARDCallback callback);
extern int memcmp(const void* a, const void* b, u32 n);
extern void* memcpy(void* dst, const void* src, u32 n);
extern void* memset(void* dst, int val, u32 n);

s32 __CARDSetStatusExAsync(s32 chan, s32 fileNo, CARDDir* dirent, CARDCallback callback)
{
    CARDControl* card;
    CARDDir* dir;
    CARDDir* ent;
    s32 result;
    u8* p;
    s32 i;

    if (fileNo < 0 || fileNo >= 127 || dirent->fileName[0] == 0xFF
        || dirent->fileName[0] == 0) {
        return -128;
    }

    result = __CARDGetControlBlock(chan, &card);
    if (result < 0) {
        return result;
    }

    dir = __CARDGetDirBlock(card);
    ent = &dir[fileNo];
    result = __CARDIsWritable(card, ent);
    if (result < 0) {
        return __CARDPutControlBlock(card, result);
    }

    for (p = dirent->fileName; p < (u8*)&dirent->time; p++) {
        if (*p != 0) {
            continue;
        }
        while ((++p) < (u8*)&dirent->time) {
            *p = 0;
        }
        break;
    }

    if (dirent->permission & 0x20) {
        memset(dirent->gameName, 0, sizeof(dirent->gameName));
        memset(dirent->company, 0, sizeof(dirent->company));
    }
    if (dirent->permission & 0x40) {
        memset(dirent->gameName, 0, sizeof(dirent->gameName));
    }

    if (memcmp(ent->fileName, dirent->fileName, 32) != 0
        || memcmp(ent->gameName, dirent->gameName, 4) != 0
        || memcmp(ent->company, dirent->company, 2) != 0) {
        for (i = 0; i < 127; i++) {
            if (i != fileNo) {
                CARDDir* ent = &dir[i];

                if (ent->gameName[0] != 0xFF
                    && memcmp(ent->gameName, dirent->gameName, 4) == 0
                    && memcmp(ent->company, dirent->company, 2) == 0
                    && memcmp(ent->fileName, dirent->fileName, 32) == 0) {
                    return __CARDPutControlBlock(card, -7);
                }
            }
        }
        memcpy(ent->fileName, dirent->fileName, 32);
        memcpy(ent->gameName, dirent->gameName, 4);
        memcpy(ent->company, dirent->company, 2);
    }

    ent->time = dirent->time;
    ent->bannerFormat = dirent->bannerFormat;
    ent->iconAddr = dirent->iconAddr;
    ent->iconFormat = dirent->iconFormat;
    ent->iconSpeed = dirent->iconSpeed;
    ent->commentAddr = dirent->commentAddr;
    ent->permission = dirent->permission;
    ent->copyTimes = dirent->copyTimes;

    result = __CARDUpdateDir(chan, callback);
    if (result < 0) {
        __CARDPutControlBlock(card, result);
    }
    return result;
}
