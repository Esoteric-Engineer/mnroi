typedef unsigned char u8;
typedef unsigned short u16;
typedef long s32;

typedef struct CARDControl {
    u8 pad0[0x10];
    u16 cBlock;
    u8 pad1[0x110 - 0x12];
} CARDControl;

typedef struct CARDDir {
    u8 pad0[0x34];
    u8 permission;
    u8 pad1;
    u16 startBlock;
    u8 pad2[0x40 - 0x38];
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
extern s32 __CARDIsWritable(CARDControl* card, CARDDir* ent);

s32 CARDFastOpen(s32 chan, s32 fileNo, CARDFileInfo* fileInfo)
{
    CARDControl* card;
    CARDDir* dir;
    CARDDir* ent;
    s32 result;

    if (fileNo < 0 || fileNo >= 127)
        return -128;

    fileInfo->chan = -1;
    result = __CARDGetControlBlock(chan, &card);
    if (result < 0)
        return result;

    dir = __CARDGetDirBlock(card);
    ent = &dir[fileNo];
    result = __CARDIsWritable(card, ent);
    if (result == -10 && (ent->permission & 4))
        result = 0;

    if (result >= 0) {
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
