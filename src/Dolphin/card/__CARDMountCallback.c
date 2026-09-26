typedef unsigned char u8;
typedef unsigned long u32;
typedef long s32;
typedef s32 BOOL;

typedef void (*CARDCallback)(s32, s32);

typedef struct CARDControl {
    u8 pad0[0x24];
    int mountStep;
    u8 pad28[0xD0 - 0x28];
    CARDCallback apiCallback;
    u8 padD4[0xDC - 0xD4];
    CARDCallback unlockCallback;
    u8 padE0[0x110 - 0xE0];
} CARDControl;

extern CARDControl __CARDBlock[2];

extern s32 fn_8040CCE0(s32 chan);
extern s32 __CARDVerify(CARDControl* card);
extern s32 __CARDPutControlBlock(CARDControl* card, s32 result);
extern void __CARDUnlockedHandler(s32 chan);
extern void DoUnmount(s32 chan, s32 result);
extern BOOL EXILock(s32 chan, u32 dev, void* unlockedCallback);

void __CARDMountCallback(s32 chan, s32 result)
{
    CARDControl* card;
    CARDCallback callback;

    card = &__CARDBlock[chan];
    switch (result) {
    case 0:
        if (++card->mountStep < 7) {
            result = fn_8040CCE0(chan);
            if (0 <= result)
                return;
        } else
            result = __CARDVerify(card);
        break;
    case 1:
        card->unlockCallback = __CARDMountCallback;
        if (!EXILock(chan, 0, __CARDUnlockedHandler)) {
            return;
        }
        card->unlockCallback = 0;

        result = fn_8040CCE0(chan);
        if (result >= 0)
            return;
        break;
    case -5:
    case -3:
        DoUnmount(chan, result);
        break;
    }

    callback = card->apiCallback;
    card->apiCallback = 0;
    __CARDPutControlBlock(card, result);
    callback(chan, result);
}
