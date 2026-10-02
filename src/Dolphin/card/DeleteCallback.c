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

extern CARDControl __CARDBlock[2];

extern s32 __CARDFreeBlock(s32 chan, u16 block, CARDCallback callback);
extern s32 __CARDPutControlBlock(CARDControl* card, s32 result);

void DeleteCallback(s32 chan, s32 result)
{
    CARDControl* card;
    CARDCallback callback;

    card = &__CARDBlock[chan];
    callback = card->apiCallback;
    card->apiCallback = 0;

    if (result < 0)
        goto error;

    result = __CARDFreeBlock(chan, card->startBlock, callback);
    if (result < 0)
        goto error;
    return;

error:
    __CARDPutControlBlock(card, result);
    if (callback)
        callback(chan, result);
}
