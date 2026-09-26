typedef unsigned char u8;
typedef long s32;

typedef void (*CARDCallback)(s32, s32);

typedef struct CARDControl {
    s32 attached;
    s32 result;
    u8 pad0[0x24 - 8];
    s32 mountStep;
    u8 pad1[0xC4 - 0x28];
    CARDCallback extCallback;
    u8 pad2[0xCC - 0xC8];
    CARDCallback exiCallback;
    u8 pad3[0xE0 - 0xD0];
    u8 alarm[0x110 - 0xE0];
} CARDControl;

extern CARDControl __CARDBlock[2];

extern void* EXISetExiCallback(s32 chan, void* callback);
extern void OSCancelAlarm(void* alarm);

void __CARDExtHandler(s32 chan, void* context)
{
    CARDControl* card;
    CARDCallback callback;

    card = &__CARDBlock[chan];
    if (card->attached) {
        card->attached = 0;
        EXISetExiCallback(chan, 0);
        OSCancelAlarm(&card->alarm);
        callback = card->exiCallback;

        if (callback) {
            card->exiCallback = 0;
            callback(chan, -3);
        }

        if (card->result != -1) {
            card->result = -3;
        }

        callback = card->extCallback;
        if (callback && card->mountStep >= 7) {
            card->extCallback = 0;
            callback(chan, -3);
        }
    }
}
