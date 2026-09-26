typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned long u32;
typedef long s32;
typedef long long s64;

typedef void (*CARDCallback)(s32, s32);

typedef struct DVDDiskID {
    u8 gameName[4];
    u8 company[2];
    u8 pad[0x20 - 6];
} DVDDiskID;

typedef struct CARDFileInfo {
    s32 chan;
    s32 fileNo;
    s32 offset;
    s32 length;
    u16 iBlock;
} CARDFileInfo;

typedef struct CARDControl {
    u8 pad0[0xBC];
    u16 freeNo;
    u16 startBlock;
    CARDFileInfo* fileInfo;
    u8 pad1[0xD0 - 0xC4];
    CARDCallback apiCallback;
    u8 pad2[0x10C - 0xD4];
    DVDDiskID* diskID;
} CARDControl;

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
    u8 permission;
    u8 copyTimes;
    u16 startBlock;
    u16 length;
    u16 pad1;
    u32 commentAddr;
} CARDDir;

extern u32 __OSBusClock : 0x800000F8;

extern CARDDir* __CARDGetDirBlock(CARDControl* card);
extern s32 __CARDPutControlBlock(CARDControl* card, s32 result);
extern s32 __CARDUpdateDir(s32 chan, CARDCallback callback);
extern s64 OSGetTime(void);
extern void* memcpy(void* dst, const void* src, unsigned long n);
extern CARDControl __CARDBlock[2];

void CreateCallbackFat(s32 chan, s32 result)
{
    CARDControl* card;
    CARDDir* dir;
    CARDDir* ent;
    CARDCallback callback;

    card = &__CARDBlock[chan];
    callback = card->apiCallback;
    card->apiCallback = 0;

    if (result >= 0) {
        dir = __CARDGetDirBlock(card);
        ent = &dir[card->freeNo];
        memcpy(ent->gameName, card->diskID->gameName, sizeof(ent->gameName));
        memcpy(ent->company, card->diskID->company, sizeof(ent->company));
        ent->permission = 4;
        ent->copyTimes = 0;
        ent->startBlock = card->startBlock;
        ent->bannerFormat = 0;
        ent->iconAddr = -1;
        ent->iconFormat = 0;
        ent->iconSpeed = 0;
        ent->commentAddr = -1;
        ent->iconSpeed = (ent->iconSpeed & ~3) | 1;
        card->fileInfo->offset = 0;
        card->fileInfo->iBlock = ent->startBlock;
        ent->time = OSGetTime() / (__OSBusClock / 4);
        result = __CARDUpdateDir(chan, callback);
        if (result < 0)
            goto after;
    } else {
after:
        __CARDPutControlBlock(card, result);
        if (callback)
            callback(chan, result);
    }
}
