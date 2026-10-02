typedef long s32;

typedef struct CARDFileInfo {
    s32 chan;
    s32 fileNo;
    s32 offset;
    s32 length;
    unsigned short iBlock;
    unsigned short pad;
} CARDFileInfo;

extern s32 __CARDGetControlBlock(s32 chan, void** card);
extern s32 __CARDPutControlBlock(void* card, s32 result);

s32 CARDClose(CARDFileInfo* fileInfo)
{
    void* card;
    s32 result = __CARDGetControlBlock(fileInfo->chan, &card);

    if (result < 0)
        return result;
    fileInfo->chan = -1;
    return __CARDPutControlBlock(card, 0);
}
