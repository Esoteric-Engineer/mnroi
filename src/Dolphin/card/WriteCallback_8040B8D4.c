typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned long u32;
typedef long s32;

typedef void (*CARDCallback)(s32, s32);

typedef struct CARDControl {
    u8 pad0[0xC];
    u32 sectorSize;
    u8 pad10[0x80 - 0x10];
    void* workArea;
    void* currentDir;
    u8 pad88[0xD0 - 0x88];
    CARDCallback apiCallback;
    u8 padD4[0xD8 - 0xD4];
    CARDCallback eraseCallback;
    u8 padDC[0x110 - 0xDC];
} CARDControl;

extern CARDControl __CARDBlock[2];

extern s32 __CARDPutControlBlock(CARDControl* card, s32 result);
extern void* memcpy(void* dst, const void* src, u32 n);

void WriteCallback_8040B8D4(s32 chan, s32 result)
{
    CARDControl* card = &__CARDBlock[chan];
    CARDCallback callback;

    if (result >= 0) {
        u8* dir0 = (u8*)card->workArea + 0x2000;
        u8* dir1 = (u8*)card->workArea + 0x4000;

        if (card->currentDir == dir0) {
            card->currentDir = dir1;
            memcpy(dir1, dir0, 0x2000);
        } else {
            card->currentDir = dir0;
            memcpy(dir0, dir1, 0x2000);
        }
    }

    if (!card->apiCallback)
        __CARDPutControlBlock(card, result);
    callback = card->eraseCallback;
    if (callback) {
        card->eraseCallback = 0;
        callback(chan, result);
    }
}
