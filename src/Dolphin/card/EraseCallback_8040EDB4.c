typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned long u32;
typedef long s32;

typedef void (*CARDCallback)(s32, s32);

typedef struct CARDFileInfo {
    s32 chan;
    s32 fileNo;
    s32 offset;
    s32 length;
    u16 iBlock;
} CARDFileInfo;

typedef struct CARDControl {
    u8 pad0[0xC];
    s32 sectorSize;
    u8 pad1[0xB4 - 0x10];
    void* buffer;
    u8 pad2[0xC0 - 0xB8];
    CARDFileInfo* fileInfo;
    u8 pad3[0xD0 - 0xC4];
    CARDCallback apiCallback;
    u8 pad4[0x110 - 0xD4];
} CARDControl;

extern CARDControl __CARDBlock[2];

extern void WriteCallback_8040EC44(s32 chan, s32 result);
extern s32 __CARDPutControlBlock(CARDControl* card, s32 result);
extern s32 __CARDWrite(s32 chan, u32 addr, s32 length, void* dst, CARDCallback callback);

void EraseCallback_8040EDB4(s32 chan, s32 result)
{
    CARDControl* card;
    CARDCallback callback;
    CARDFileInfo* fileInfo;

    card = &__CARDBlock[chan];
    if (result >= 0) {
        fileInfo = card->fileInfo;
        result = __CARDWrite(chan, card->sectorSize * fileInfo->iBlock, card->sectorSize, card->buffer, WriteCallback_8040EC44);
        if (result < 0)
            goto error;
    } else {
error:
        callback = card->apiCallback;
        card->apiCallback = 0;
        __CARDPutControlBlock(card, result);
        callback(chan, result);
    }
}
