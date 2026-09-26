typedef unsigned char u8;
typedef unsigned long u32;
typedef long s32;

typedef void (*CARDCallback)(s32, s32);

typedef struct CARDControl {
    u8 pad0[0xAC];
    s32 repeat;
    u32 addr;
    u8* buffer;
    s32 xferred;
    u8 pad1[0xD0 - 0xBC];
    CARDCallback apiCallback;
    CARDCallback xferCallback;
    u8 pad2[0x110 - 0xD8];
} CARDControl;

extern CARDControl __CARDBlock[2];

extern s32 __CARDReadSegment(s32 chan, CARDCallback callback);
extern s32 __CARDPutControlBlock(CARDControl* card, s32 result);

void BlockReadCallback(s32 chan, s32 result)
{
    CARDControl* card;
    CARDCallback callback;

    card = &__CARDBlock[chan];

    if (result >= 0) {
        card->xferred += 0x200;
        card->addr += 0x200;
        card->buffer += 0x200;

        if (--card->repeat > 0) {
            result = __CARDReadSegment(chan, BlockReadCallback);
            if (result >= 0) {
                return;
            }
        }
    }
    if (!card->apiCallback) {
        __CARDPutControlBlock(card, result);
    }
    callback = card->xferCallback;
    if (callback) {
        card->xferCallback = 0;
        callback(chan, result);
    }
}
