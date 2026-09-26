typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned long u32;
typedef long s32;

typedef void (*CARDCallback)(s32, s32);

typedef struct CARDControl {
    u8 pad0[0xB4];
    void* buffer;
    u8 pad1[0xD0 - 0xB8];
    CARDCallback apiCallback;
} CARDControl;

typedef struct CARDControlX {
    u8 pad0[0xC];
    s32 sectorSize;
} CARDControlX;

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
extern s32 __CARDIsWritable(CARDControl* card, CARDDir* ent);
extern void DCStoreRange(void* addr, u32 nBytes);
extern void __CARDDefaultApiCallback(s32 chan, s32 result);
extern s32 fn_8040AF24(s32 chan, u32 addr, CARDCallback callback);
extern void EraseCallback_8040EDB4(s32 chan, s32 result);

s32 CARDWriteAsync(CARDFileInfo* fileInfo, const void* buf, s32 length, s32 offset, CARDCallback callback)
{
    CARDControl* card;
    s32 result;
    CARDDir* dir;
    CARDDir* ent;

    result = fn_8040E7D0(fileInfo, length, offset, &card);
    if (result < 0)
        return result;

    if ((offset & (((CARDControlX*)card)->sectorSize - 1)) != 0 || (length & (((CARDControlX*)card)->sectorSize - 1)) != 0)
        return __CARDPutControlBlock(card, -128);

    dir = __CARDGetDirBlock(card);
    ent = &dir[fileInfo->fileNo];
    result = __CARDIsWritable(card, ent);
    if (result < 0)
        return __CARDPutControlBlock(card, result);

    DCStoreRange((void*)buf, (u32)length);
    card->apiCallback = callback ? callback : __CARDDefaultApiCallback;
    card->buffer = (void*)buf;
    result = fn_8040AF24(fileInfo->chan, ((CARDControlX*)card)->sectorSize * (u32)fileInfo->iBlock, EraseCallback_8040EDB4);
    if (result < 0)
        __CARDPutControlBlock(card, result);
    return result;
}
