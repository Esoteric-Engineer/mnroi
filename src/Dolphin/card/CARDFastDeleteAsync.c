typedef unsigned char u8;
typedef unsigned short u16;
typedef long s32;

typedef void (*CARDCallback)(s32, s32);

typedef struct CARDControl {
    u8 pad0[0xBE];
    u16 startBlock;
    u8 pad1[0xD0 - 0xC0];
    CARDCallback apiCallback;
    u8 pad2[0x110 - 0xD4];
} CARDControl;

typedef struct CARDDir {
    u8 pad0[0x36];
    u16 startBlock;
    u8 pad1[0x40 - 0x38];
} CARDDir;

extern s32 fn_8040B0F0(s32 chan, CARDControl** card);
extern s32 __CARDPutControlBlock(CARDControl* card, s32 result);
extern int __CARDIsOpened(CARDControl* card, s32 fileNo);
extern CARDDir* __CARDGetDirBlock(CARDControl* card);
extern s32 fn_8040DE44(CARDControl* card, CARDDir* ent);
extern void* memset(void* dst, int val, unsigned long n);
extern s32 fn_8040BA6C(s32 chan, CARDCallback callback);
extern void __CARDDefaultApiCallback(s32 chan, s32 result);
extern void DeleteCallback(s32 chan, s32 result);

s32 CARDFastDeleteAsync(s32 chan, s32 fileNo, CARDCallback callback)
{
    CARDControl* card;
    CARDDir* dir;
    CARDDir* ent;
    s32 result;

    if (fileNo < 0 || 127 <= fileNo)
        return -128;
    result = fn_8040B0F0(chan, &card);
    if (result < 0)
        return result;

    dir = __CARDGetDirBlock(card);
    ent = &dir[fileNo];
    result = fn_8040DE44(card, ent);
    if (result < 0)
        return __CARDPutControlBlock(card, result);
    if (__CARDIsOpened(card, fileNo))
        return __CARDPutControlBlock(card, -1);
    card->startBlock = ent->startBlock;
    memset(ent, 0xff, sizeof(CARDDir));

    card->apiCallback = callback ? callback : __CARDDefaultApiCallback;
    result = fn_8040BA6C(chan, DeleteCallback);
    if (result < 0)
        __CARDPutControlBlock(card, result);
    return result;
}
