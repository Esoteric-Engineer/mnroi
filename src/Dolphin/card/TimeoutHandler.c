typedef unsigned char u8;
typedef long s32;

typedef void (*CARDCallback)(s32, s32);

typedef struct CARDControl {
    s32 attached;
    u8 pad0[0xCC - 4];
    CARDCallback exiCallback;
    u8 pad1[0xE0 - 0xD0];
    u8 alarm[0x110 - 0xE0];
} CARDControl;

extern CARDControl __CARDBlock[2];

extern void* EXISetExiCallback(s32 chan, void* callback);

void TimeoutHandler(void* alarm, void* context)
{
    s32 chan;
    CARDControl* card;
    CARDCallback callback;

    for (chan = 0; chan < 2; ++chan) {
        card = &__CARDBlock[chan];
        if (alarm == card->alarm) {
            break;
        }
    }

    if (card->attached) {
        EXISetExiCallback(chan, 0);
        callback = card->exiCallback;
        if (callback) {
            card->exiCallback = 0;
            callback(chan, -5);
        }
    }
}
