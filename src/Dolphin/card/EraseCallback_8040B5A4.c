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
    u16* currentFat;
    u8 pad8C[0xD0 - 0x8C];
    CARDCallback apiCallback;
    u8 padD4[0xD8 - 0xD4];
    CARDCallback eraseCallback;
    u8 padDC[0x110 - 0xDC];
} CARDControl;

extern CARDControl __CARDBlock[2];

extern void WriteCallback_8040B4D0(s32 chan, s32 result);
extern s32 __CARDPutControlBlock(CARDControl* card, s32 result);
extern s32 __CARDWrite(s32 chan, u32 addr, s32 length, void* dst, CARDCallback callback);

static inline u16* GetFat(CARDControl* card)
{
    u16* f = card->currentFat;
    return f;
}

void EraseCallback_8040B5A4(s32 chan, s32 result)
{
    CARDControl* card;
    CARDCallback callback;
    u16* fat;
    u32 addr;

    card = &__CARDBlock[chan];
    if (result >= 0) {
        fat = GetFat(card);
        addr = (((u32)fat - (u32)card->workArea) / 0x2000) * card->sectorSize;
        result = __CARDWrite(chan, addr, 0x2000, fat, WriteCallback_8040B4D0);
        if (result >= 0)
            return;
    }
    if (!card->apiCallback)
        __CARDPutControlBlock(card, result);

    callback = card->eraseCallback;
    if (callback) {
        card->eraseCallback = 0;
        callback(chan, result);
    }
}
