typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned long u32;
typedef long s32;

typedef void (*CARDCallback)(s32, s32);

typedef struct DVDDiskID {
    u8 gameName[4];
    u8 company[2];
    u8 pad[0x20 - 6];
} DVDDiskID;

typedef struct CARDFileInfo {
    s32 chan;
    s32 fileNo;
} CARDFileInfo;

typedef struct CARDControl {
    u8 pad0[0xC];
    u32 sectorSize;
    u8 pad1[0xBC - 0x10];
    u16 freeNo;
    u16 startBlock;
    CARDFileInfo* fileInfo;
    u8 pad2[0xD0 - 0xC4];
    CARDCallback apiCallback;
    u8 pad3[0x10C - 0xD4];
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

extern unsigned long strlen(const char* s);
extern char* strncpy(char* dst, const char* src, unsigned long n);
extern int memcmp(const void* a, const void* b, unsigned long n);
extern s32 __CARDGetControlBlock(s32 chan, CARDControl** card);
extern s32 __CARDPutControlBlock(CARDControl* card, s32 result);
extern CARDDir* __CARDGetDirBlock(CARDControl* card);
extern u16* __CARDGetFatBlock(CARDControl* card);
extern s32 __CARDCompareFileName(CARDDir* ent, const char* fileName);
extern s32 __CARDAllocBlock(s32 chan, u32 cBlock, CARDCallback callback);
extern void __CARDDefaultApiCallback(s32 chan, s32 result);
extern void CreateCallbackFat(s32 chan, s32 result);

s32 CARDCreateAsync(s32 chan, const char* fileName, u32 size, CARDFileInfo* fileInfo, CARDCallback callback)
{
    CARDControl* card;
    CARDDir* dir;
    CARDDir* ent;
    u16 fileNo;
    u16 freeNo;
    u16* fat;
    s32 result;

    if (strlen(fileName) > 32) {
        return -12;
    }

    result = __CARDGetControlBlock(chan, &card);
    if (result < 0) {
        return result;
    }

    if (size <= 0 || (size % card->sectorSize) != 0) {
        return -128;
    }

    freeNo = (u16)-1;
    dir = __CARDGetDirBlock(card);
    for (fileNo = 0; fileNo < 127; fileNo++) {
        ent = &dir[fileNo];
        if (ent->gameName[0] == 0xff) {
            if (freeNo == (u16)-1) {
                freeNo = fileNo;
            }
        } else if (memcmp(ent->gameName, card->diskID->gameName, sizeof(ent->gameName)) == 0
                   && memcmp(ent->company, card->diskID->company, sizeof(ent->company)) == 0
                   && __CARDCompareFileName(ent, fileName)) {
            return __CARDPutControlBlock(card, -7);
        }
    }
    if (freeNo == (u16)-1) {
        return __CARDPutControlBlock(card, -8);
    }

    fat = __CARDGetFatBlock(card);
    if (card->sectorSize * fat[3] < size) {
        return __CARDPutControlBlock(card, -9);
    }

    card->apiCallback = callback ? callback : __CARDDefaultApiCallback;
    card->freeNo = freeNo;
    ent = &dir[freeNo];
    ent->length = (u16)(size / card->sectorSize);
    strncpy((char*)ent->fileName, fileName, 32);

    card->fileInfo = fileInfo;
    fileInfo->chan = chan;
    fileInfo->fileNo = freeNo;

    result = __CARDAllocBlock(chan, size / card->sectorSize, CreateCallbackFat);
    if (result < 0) {
        return __CARDPutControlBlock(card, result);
    }
    return result;
}
