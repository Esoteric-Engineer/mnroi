typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned long u32;
typedef long s32;

typedef void (*CARDCallback)(s32, s32);

typedef struct CARDControl {
    u8 pad0[0xC];
    s32 sectorSize;
    u8 pad1[0xD0 - 0x10];
    CARDCallback apiCallback;
} CARDControl;

typedef struct CARDFileInfo {
    s32 chan;
    s32 fileNo;
    s32 offset;
    s32 length;
    u16 iBlock;
} CARDFileInfo;

typedef struct CARDDir {
    u8 pad0[0x40];
} CARDDir;

extern s32 fn_8040E7D0(CARDFileInfo* fileInfo, s32 length, s32 offset, CARDControl** card);
extern s32 __CARDPutControlBlock(CARDControl* card, s32 result);
extern CARDDir* __CARDGetDirBlock(CARDControl* card);
extern s32 fn_8040DF78(CARDControl* card, CARDDir* ent);
extern void DCInvalidateRange(void* addr, u32 nBytes);
extern void __CARDDefaultApiCallback(s32 chan, s32 result);
extern s32 __CARDRead(s32 chan, u32 addr, s32 length, void* dst, CARDCallback callback);
extern void ReadCallback(s32 chan, s32 result);

s32 CARDReadAsync(CARDFileInfo* fileInfo, void* buf, s32 length, s32 offset, CARDCallback callback)
{
    CARDControl* card;
    s32 result;
    CARDDir* dir;
    CARDDir* ent;

    if ((offset & 0x1FF) != 0 || (length & 0x1FF) != 0)
        return -128;
    result = fn_8040E7D0(fileInfo, length, offset, &card);
    if (result < 0)
        return result;

    dir = __CARDGetDirBlock(card);
    ent = &dir[fileInfo->fileNo];
    result = fn_8040DF78(card, ent);
    if (result < 0)
        return __CARDPutControlBlock(card, result);

    DCInvalidateRange(buf, (u32)length);
    card->apiCallback = callback ? callback : __CARDDefaultApiCallback;

    offset = (s32)(fileInfo->offset & (card->sectorSize - 1));
    length = (length < card->sectorSize - offset) ? length : card->sectorSize - offset;
    result = __CARDRead(fileInfo->chan, card->sectorSize * (u32)fileInfo->iBlock + offset, length, buf, ReadCallback);
    if (result < 0)
        __CARDPutControlBlock(card, result);
    return result;
}
