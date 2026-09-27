typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned long u32;
typedef long s32;
typedef long long s64;

typedef void (*CARDCallback)(s32, s32);

typedef struct CARDFileInfo {
    s32 chan;
    s32 fileNo;
    s32 offset;
    s32 length;
    u16 iBlock;
    u16 pad;
} CARDFileInfo;

typedef struct CARDDir {
    u8 pad0[0x28];
    u32 time;
    u8 pad2C[0x40 - 0x2C];
} CARDDir;

typedef struct CARDControl {
    u8 pad0[0xC];
    s32 sectorSize;
    u16 cBlock;
    u8 pad12[0xC0 - 0x12];
    CARDFileInfo* fileInfo;
    u8 padC4[0xD0 - 0xC4];
    CARDCallback apiCallback;
    u8 padD4[0x110 - 0xD4];
} CARDControl;

extern CARDControl __CARDBlock[2];
extern u32 __OSBusClock : 0x800000F8;

extern CARDDir* __CARDGetDirBlock(CARDControl* card);
extern u16* __CARDGetFatBlock(CARDControl* card);
extern s32 __CARDUpdateDir(s32 chan, CARDCallback callback);
extern s32 __CARDEraseSector(s32 chan, u32 addr, CARDCallback callback);
extern s32 __CARDPutControlBlock(CARDControl* card, s32 result);
extern s64 OSGetTime(void);
extern void EraseCallback_8040EDB4(s32 chan, s32 result);

void WriteCallback_8040EC44(s32 chan, s32 result)
{
    CARDControl* card;
    CARDCallback callback;
    u16* fat;
    CARDDir* dir;
    CARDDir* ent;
    CARDFileInfo* fileInfo;

    card = &__CARDBlock[chan];
    if (result >= 0) {
        fileInfo = card->fileInfo;
        if (fileInfo->length < 0) {
            result = -14;
            goto after;
        }
        fileInfo->length -= card->sectorSize;
        if (fileInfo->length <= 0) {
            dir = __CARDGetDirBlock(card);
            ent = dir + fileInfo->fileNo;
            ent->time = OSGetTime() / (__OSBusClock / 4);
            callback = card->apiCallback;
            card->apiCallback = 0;
            result = __CARDUpdateDir(chan, callback);
            goto check;
        } else {
            fat = __CARDGetFatBlock(card);
            fileInfo->offset += card->sectorSize;
            fileInfo->iBlock = fat[fileInfo->iBlock];
            if ((fileInfo->iBlock < 5) || (fileInfo->iBlock >= card->cBlock)) {
                result = -6;
                goto after;
            }
            result = __CARDEraseSector(chan, card->sectorSize * fileInfo->iBlock, EraseCallback_8040EDB4);
check:;
            if (result < 0) {
                goto after;
            }
        }
    } else {
after:;
        callback = card->apiCallback;
        card->apiCallback = 0;
        __CARDPutControlBlock(card, result);
        callback(chan, result);
    }
}
