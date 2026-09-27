typedef unsigned char u8;
typedef unsigned short u16;
typedef short s16;
typedef long s32;
typedef unsigned long u32;

typedef void (*CARDCallback)(s32, s32);

typedef struct CARDDirCheck {
    u8 padding[0x3A];
    s16 checkCode;
    u16 checkSum;
    u16 checkSumInv;
} CARDDirCheck;

typedef struct CARDControl {
    s32 attached;
    u8 pad4[0x8];
    u32 sectorSize;
    u8 pad10[0x80 - 0x10];
    void* workArea;
    void* currentDir;
    u8 pad88[0xD8 - 0x88];
    CARDCallback eraseCallback;
    u8 padDC[0x110 - 0xDC];
} CARDControl;

extern CARDControl __CARDBlock[2];

extern void __CARDCheckSum(void* ptr, s32 length, u16* checksum, u16* checksumInv);
extern void DCStoreRange(void* addr, u32 nBytes);
extern s32 __CARDEraseSector(s32 chan, u32 addr, CARDCallback callback);
extern void EraseCallback_8040B9A4(s32 chan, s32 result);

static inline void* __CARDGetDirBlock(CARDControl* card)
{
    void* dir = card->currentDir;
    return dir;
}

s32 __CARDUpdateDir(s32 chan, CARDCallback callback)
{
    CARDControl* card;
    CARDDirCheck* check;
    u32 addr;
    void* dir;

    card = &__CARDBlock[chan];
    if (!card->attached)
        return -3;

    dir = __CARDGetDirBlock(card);
    check = (CARDDirCheck*)((u8*)dir + 0x1FC0);
    ++check->checkCode;
    __CARDCheckSum(dir, 0x1FFC, &check->checkSum, &check->checkSumInv);
    DCStoreRange(dir, 0x2000);
    card->eraseCallback = callback;
    addr = (((u32)dir - (u32)card->workArea) / 0x2000) * card->sectorSize;
    return __CARDEraseSector(chan, addr, EraseCallback_8040B9A4);
}
