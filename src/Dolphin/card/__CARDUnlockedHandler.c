typedef long s32;
typedef unsigned char u8;

typedef void (*CARDCallback)(s32, s32);

typedef struct CARDControl {
    u8 pad0[0xDC];
    CARDCallback unlockCallback;
    u8 pad1[0x110 - 0xE0];
} CARDControl;

extern CARDControl __CARDBlock[2];

extern int EXIProbe(s32 chan);

void __CARDUnlockedHandler(s32 chan, void* context)
{
    CARDControl* card;
    CARDCallback callback;

    card = &__CARDBlock[chan];
    callback = card->unlockCallback;
    if (callback) {
        card->unlockCallback = 0;
        callback(chan, EXIProbe(chan) ? 1 : -3);
    }
}
