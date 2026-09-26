typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned long u32;
typedef long s32;

typedef void (*CARDCallback)(s32, s32);

typedef struct CARDControl {
    u8 pad0[0xC];
    s32 sectorSize;
    u8 pad1[0x28 - 0x10];
    s32 formatStep;
    u8 pad2[0x80 - 0x2C];
    void* workArea;
    void* currentDir;
    void* currentFat;
    u8 pad3[0xD0 - 0x8C];
    CARDCallback apiCallback;
    u8 pad4[0x110 - 0xD4];
} CARDControl;

extern CARDControl __CARDBlock[2];

extern void* memcpy(void* dst, const void* src, unsigned long n);
extern s32 fn_8040AF24(s32 chan, u32 addr, CARDCallback callback);
extern s32 __CARDWrite(s32 chan, u32 addr, s32 length, void* dst, CARDCallback callback);
extern s32 __CARDPutControlBlock(CARDControl* card, s32 result);

void FormatCallback(s32 chan, s32 result)
{
    CARDControl* card;
    CARDCallback callback;

    card = &__CARDBlock[chan];
    if (result < 0)
        goto error;

    ++card->formatStep;
    if (card->formatStep < 5) {
        result = fn_8040AF24(chan, (u32)card->sectorSize * card->formatStep, FormatCallback);
        if (result >= 0)
            return;
    } else if (card->formatStep < 10) {
        int step = card->formatStep - 5;
        result = __CARDWrite(chan, (u32)card->sectorSize * step, 0x2000, (u8*)card->workArea + (0x2000 * step), FormatCallback);
        if (result >= 0)
            return;
    } else {
        card->currentDir = (u8*)card->workArea + 0x2000;
        memcpy(card->currentDir, (u8*)card->workArea + 0x4000, 0x2000);
        card->currentFat = (u8*)card->workArea + 0x6000;
        memcpy(card->currentFat, (u8*)card->workArea + 0x8000, 0x2000);
    }

error:
    callback = card->apiCallback;
    card->apiCallback = 0;
    __CARDPutControlBlock(card, result);
    callback(chan, result);
}
