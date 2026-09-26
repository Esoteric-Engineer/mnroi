typedef unsigned char u8;
typedef unsigned short u16;
typedef long s32;

typedef struct CARDControl {
    s32 attached;
    u8 pad0[0x10 - 4];
    u16 cBlock;
    u8 pad1[0x110 - 0x12];
} CARDControl;

typedef struct CARDDir {
    u8 pad0[0x36];
    u16 startBlock;
    u8 pad1[0x40 - 0x38];
} CARDDir;

typedef struct CARDFileInfo {
    s32 chan;
    s32 fileNo;
    s32 offset;
    s32 length;
    u16 iBlock;
    u16 pad;
} CARDFileInfo;

extern s32 __CARDGetControlBlock(s32 chan, CARDControl** card);
extern s32 __CARDPutControlBlock(CARDControl* card, s32 result);
extern CARDDir* __CARDGetDirBlock(CARDControl* card);
extern s32 __CARDAccess(CARDControl* card, CARDDir* ent);
extern s32 __CARDCompareFileName(CARDDir* ent, const char* fileName);

static inline s32 GetFileNo(CARDControl* card, const char* fileName, s32* pfileNo)
{
    CARDDir* dir;
    CARDDir* ent;
    s32 fileNo;

    if (card->attached == 0)
        return -3;

    dir = __CARDGetDirBlock(card);
    for (fileNo = 0; fileNo < 127; fileNo++) {
        ent = &dir[fileNo];
        if (__CARDAccess(card, ent) >= 0 && __CARDCompareFileName(ent, fileName) != 0) {
            *pfileNo = fileNo;
            return 0;
        }
    }
    return -4;
}

s32 CARDOpen(s32 chan, const char* fileName, CARDFileInfo* fileInfo)
{
    CARDControl* card;
    CARDDir* dir;
    CARDDir* ent;
    s32 result;
    s32 fileNo;

    fileInfo->chan = -1;
    result = __CARDGetControlBlock(chan, &card);
    if (result < 0)
        return result;

    result = GetFileNo(card, fileName, &fileNo);
    if (result >= 0) {
        dir = __CARDGetDirBlock(card);
        ent = &dir[fileNo];
        if (ent->startBlock < 5 || ent->startBlock >= card->cBlock) {
            result = -6;
        } else {
            fileInfo->chan = chan;
            fileInfo->fileNo = fileNo;
            fileInfo->offset = 0;
            fileInfo->iBlock = ent->startBlock;
        }
    }
    return __CARDPutControlBlock(card, result);
}
