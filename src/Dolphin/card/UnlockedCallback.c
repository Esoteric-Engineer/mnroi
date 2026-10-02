typedef unsigned char u8;
typedef long s32;

typedef void (*CARDCallback)(s32, s32);

typedef struct CARDControl {
    u8 pad0[0x94];
    u8 cmd[9];
    u8 pad1[0xC8 - 0x9D];
    CARDCallback txCallback;
    CARDCallback exiCallback;
    u8 pad2[0xDC - 0xD0];
    CARDCallback unlockCallback;
    u8 pad3[0x110 - 0xE0];
} CARDControl;

extern CARDControl __CARDBlock[2];

extern int EXILock(s32 chan, s32 dev, void (*unlockedCb)(s32));
extern void __CARDUnlockedHandler(s32 chan);
extern s32 Retry(s32 chan);

void UnlockedCallback(s32 chan, s32 result)
{
    CARDCallback callback;
    CARDControl* card;

    card = &__CARDBlock[chan];
    if (result >= 0) {
        card->unlockCallback = UnlockedCallback;
        if (!EXILock(chan, 0, __CARDUnlockedHandler)) {
            result = 0;
        } else {
            card->unlockCallback = 0;
            result = Retry(chan);
        }
    }

    if (result < 0) {
        switch (card->cmd[0]) {
        case 0x52:
            callback = card->txCallback;
            if (callback) {
                card->txCallback = 0;
                callback(chan, result);
            }
            break;
        case 0xF2:
        case 0xF4:
        case 0xF1:
            callback = card->exiCallback;
            if (callback) {
                card->exiCallback = 0;
                callback(chan, result);
            }
            break;
        }
    }
}
