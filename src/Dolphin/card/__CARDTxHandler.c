typedef unsigned char u8;
typedef long s32;

typedef void (*CARDCallback)(s32, s32);

typedef struct CARDControl {
    u8 pad0[0xC8];
    CARDCallback txCallback;
    u8 pad1[0x110 - 0xCC];
} CARDControl;

extern CARDControl __CARDBlock[2];

extern int EXIDeselect(s32 chan);
extern int EXIUnlock(s32 chan);
extern int EXIProbe(s32 chan);

void __CARDTxHandler(s32 chan, void* context)
{
    CARDControl* card;
    CARDCallback callback;
    int err;

    card = &__CARDBlock[chan];
    err = !EXIDeselect(chan);
    EXIUnlock(chan);
    callback = card->txCallback;
    if (callback) {
        card->txCallback = 0;
        callback(chan, !err && EXIProbe(chan) ? 0 : -3);
    }
}
