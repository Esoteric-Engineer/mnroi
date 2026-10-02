typedef unsigned char u8;
typedef short s16;
typedef long s32;
typedef unsigned short u16;
typedef unsigned long u32;

typedef void (*CARDCallback)(s32, s32);

typedef struct CARDControl {
    s32 attached;
    u8 pad4[0xC];
    u16 cBlock;
    u8 pad12[0x88 - 0x12];
    u16* currentFat;
    u8 pad8C[0xBE - 0x8C];
    u16 startBlock;
    u8 padC0[0x110 - 0xC0];
} CARDControl;

extern CARDControl __CARDBlock[2];
extern s32 __CARDUpdateFatBlock(s32 chan, u16* fat, CARDCallback callback);

static inline u16* GetFat(CARDControl* card)
{
    return card->currentFat;
}

s32 __CARDAllocBlock(s32 chan, u32 cBlock, CARDCallback callback)
{
    CARDControl* card;
    u16* fat;
    u16 iBlock;
    u16 startBlock;
    u16 prevBlock;
    u16 count;

    card = &__CARDBlock[chan];
    if (!card->attached)
        return -3;

    fat = GetFat(card);
    if (fat[3] < cBlock)
        return -9;

    fat[3] -= cBlock;
    startBlock = 0xFFFF;
    iBlock = fat[4];
    count = 0;
    while (0 < cBlock) {
        if (card->cBlock - 5 < ++count)
            return -6;

        iBlock++;
        if (!(iBlock >= 5 && iBlock < card->cBlock))
            iBlock = 5;

        if (fat[iBlock] == 0) {
            if (startBlock == 0xFFFF)
                startBlock = iBlock;
            else
                fat[prevBlock] = iBlock;
            prevBlock = iBlock;
            fat[iBlock] = 0xFFFF;
            --cBlock;
        }
    }
    fat[4] = iBlock;
    card->startBlock = startBlock;

    return __CARDUpdateFatBlock(chan, fat, callback);
}
