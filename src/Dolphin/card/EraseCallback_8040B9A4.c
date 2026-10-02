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

extern void WriteCallback_8040B8D4(s32 chan, s32 result);
extern s32 __CARDPutControlBlock(CARDControl* card, s32 result);
extern s32 __CARDWrite(s32 chan, u32 addr, s32 length, void* dst, CARDCallback callback);

static inline void* GetDir(CARDControl* card)
{
    void* d = card->currentDir;
    return d;
}

void EraseCallback_8040B9A4(s32 chan, s32 result)
{
    CARDControl* card;
    CARDCallback callback;
    void* dir;
    u32 addr;

    card = &__CARDBlock[chan];
    if (result >= 0) {
        dir = GetDir(card);
        addr = (((u32)dir - (u32)card->workArea) / 0x2000) * card->sectorSize;
        result = __CARDWrite(chan, addr, 0x2000, dir, WriteCallback_8040B8D4);
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
