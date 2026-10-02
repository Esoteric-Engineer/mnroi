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
    u16 cBlock;
    u8 pad1[0xB4 - 0x12];
    void* buffer;
    u8 pad2[0xC0 - 0xB8];
    CARDFileInfo* fileInfo;
    u8 pad3[0xD0 - 0xC4];
    CARDCallback apiCallback;
    u8 pad4[0x110 - 0xD4];
} CARDControl;

extern CARDControl __CARDBlock[2];

extern u16* __CARDGetFatBlock(CARDControl* card);
extern s32 __CARDPutControlBlock(CARDControl* card, s32 result);
extern s32 __CARDRead(s32 chan, u32 addr, s32 length, void* dst, CARDCallback callback);

void ReadCallback(s32 chan, s32 result)
{
    CARDControl* card;
    CARDCallback callback;
    u16* fat;
    CARDFileInfo* fileInfo;
    s32 length;

    card = &__CARDBlock[chan];
    if (result < 0)
        goto error;

    fileInfo = card->fileInfo;
    if (fileInfo->length < 0) {
        result = -14;
        goto error;
    }

    length = ((u32)(fileInfo->offset + card->sectorSize) & ~(card->sectorSize - 1)) - fileInfo->offset;
    fileInfo->length -= length;
    if (fileInfo->length <= 0)
        goto error;

    fat = __CARDGetFatBlock(card);
    fileInfo->offset += length;
    fileInfo->iBlock = fat[fileInfo->iBlock];
    if (!(fileInfo->iBlock >= 5 && fileInfo->iBlock < card->cBlock)) {
        result = -6;
        goto error;
    }

    result = __CARDRead(chan, card->sectorSize * (u32)fileInfo->iBlock,
                        (fileInfo->length < card->sectorSize) ? fileInfo->length : card->sectorSize, card->buffer,
                        ReadCallback);
    if (result < 0)
        goto error;

    return;

error:
    callback = card->apiCallback;
    card->apiCallback = 0;
    __CARDPutControlBlock(card, result);
    callback(chan, result);
}
