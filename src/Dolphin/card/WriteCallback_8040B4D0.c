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
    u8 pad84[0x88 - 0x84];
    void* currentFat;
    u8 pad8C[0xD0 - 0x8C];
    CARDCallback apiCallback;
    u8 padD4[0xD8 - 0xD4];
    CARDCallback eraseCallback;
    u8 padDC[0x110 - 0xDC];
} CARDControl;

extern CARDControl __CARDBlock[2];

extern s32 __CARDPutControlBlock(CARDControl* card, s32 result);
extern void* memcpy(void* dst, const void* src, u32 n);

void WriteCallback_8040B4D0(s32 chan, s32 result)
{
    CARDControl* card = &__CARDBlock[chan];
    CARDCallback callback;

    if (result >= 0) {
        u8* fat0 = (u8*)card->workArea + 0x6000;
        u8* fat1 = (u8*)card->workArea + 0x8000;

        if (card->currentFat == fat0) {
            card->currentFat = fat1;
            memcpy(fat1, fat0, 0x2000);
        } else {
            card->currentFat = fat0;
            memcpy(fat0, fat1, 0x2000);
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
