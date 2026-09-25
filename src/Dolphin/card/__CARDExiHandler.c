typedef unsigned char u8;
typedef long s32;

typedef void (*CARDCallback)(s32, s32);

typedef struct CARDControl {
    s32 attached;
    u8 pad0[0xA8 - 4];
    s32 retry;
    u8 pad1[0xCC - 0xAC];
    CARDCallback exiCallback;
    u8 pad2[0xE0 - 0xD0];
    u8 alarm[0x30];
} CARDControl;

extern CARDControl __CARDBlock[2];

extern void OSCancelAlarm(void* alarm);
extern int EXILock(s32 chan, s32 dev, void (*unlockedCb)(s32));
extern void EXIUnlock(s32 chan);
extern s32 __CARDReadStatus(s32 chan, u8* status);
extern s32 __CARDClearStatus(s32 chan);
extern s32 Retry(s32 chan);

void __CARDExiHandler(s32 chan, void* context)
{
    CARDControl* card;
    CARDCallback callback;
    u8 status;
    s32 result;

    card = &__CARDBlock[chan];

    OSCancelAlarm(&card->alarm);

    if (!card->attached)
        return;

    if (!EXILock(chan, 0, 0)) {
        result = -0x80;
        goto fatal;
    }

    if ((result = __CARDReadStatus(chan, &status)) < 0 || (result = __CARDClearStatus(chan)) < 0)
        goto error;

    if ((result = (status & 0x18) ? -5 : 0) == -5 && --card->retry > 0) {
        result = Retry(chan);
        if (result >= 0)
            return;
        goto fatal;
    }

error:
    EXIUnlock(chan);

fatal:
    callback = card->exiCallback;
    if (callback) {
        card->exiCallback = 0;
        callback(chan, result);
    }
}
