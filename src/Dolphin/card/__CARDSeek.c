typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned long u32;
typedef long s32;

typedef struct CARDFileInfo {
    s32 chan;
    s32 fileNo;
    s32 offset;
    s32 length;
    u16 iBlock;
    u16 pad;
} CARDFileInfo;

typedef struct CARDControl {
    u8 pad0[0xC];
    s32 sectorSize;
    u16 cBlock;
    u8 pad2[0xC0 - 0x12];
    CARDFileInfo* fileInfo;
    u8 pad3[0x110 - 0xC4];
} CARDControl;

typedef struct CARDDir {
    u8 pad0[0x36];
    u16 startBlock;
    u16 length;
    u8 pad1[0x40 - 0x3A];
} CARDDir;

extern s32 __CARDGetControlBlock(s32 chan, CARDControl** card);
extern s32 __CARDPutControlBlock(CARDControl* card, s32 result);
extern CARDDir* __CARDGetDirBlock(CARDControl* card);
extern u16* __CARDGetFatBlock(CARDControl* card);

#define TRUNC(n, a) (((u32)(n)) & ~((a)-1))
#define CARDIsValidBlockNo(card, iBlock) (5 <= (iBlock) && (iBlock) < (card)->cBlock)

s32 __CARDSeek(CARDFileInfo* fileInfo, s32 length, s32 offset, CARDControl** pcard)
{
    CARDControl* card;
    CARDDir* dir;
    CARDDir* ent;
    s32 result;
    u16* fat;

    result = __CARDGetControlBlock(fileInfo->chan, &card);
    if (result < 0)
        return result;

    if (!CARDIsValidBlockNo(card, fileInfo->iBlock) || card->cBlock * card->sectorSize <= fileInfo->offset)
        return __CARDPutControlBlock(card, -128);

    dir = __CARDGetDirBlock(card);
    ent = &dir[fileInfo->fileNo];

    if (ent->length * card->sectorSize <= offset || ent->length * card->sectorSize < offset + length)
        return __CARDPutControlBlock(card, -11);

    card->fileInfo = fileInfo;
    fileInfo->length = length;
    if (offset < fileInfo->offset) {
        fileInfo->offset = 0;
        fileInfo->iBlock = ent->startBlock;
        if (!CARDIsValidBlockNo(card, fileInfo->iBlock))
            return __CARDPutControlBlock(card, -6);
    }
    fat = __CARDGetFatBlock(card);
    while (fileInfo->offset < TRUNC(offset, card->sectorSize)) {
        fileInfo->offset += card->sectorSize;
        fileInfo->iBlock = fat[fileInfo->iBlock];
        if (!CARDIsValidBlockNo(card, fileInfo->iBlock))
            return __CARDPutControlBlock(card, -6);
    }

    fileInfo->offset = offset;

    *pcard = card;
    return 0;
}
