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
    u8 pad8C[0x110 - 0x8C];
} CARDControl;

extern CARDControl __CARDBlock[2];
extern s32 fn_8040B820(s32 chan, u16* fat, CARDCallback callback);

static inline u16* GetFat(CARDControl* card)
{
    u16* f = card->currentFat;
    return f;
}

s32 __CARDFreeBlock(s32 chan, u16 nBlock, CARDCallback callback)
{
    CARDControl* card;
    u16* fat;
    u16 nextBlock;

    card = &__CARDBlock[chan];
    if (!card->attached)
        return -3;

    fat = GetFat(card);
    while (nBlock != 0xFFFF) {
        if (!(nBlock >= 5 && nBlock < card->cBlock))
            return -6;

        nextBlock = fat[nBlock];
        fat[nBlock] = 0;
        nBlock = nextBlock;
        ++fat[3];
    }

    return fn_8040B820(chan, fat, callback);
}
