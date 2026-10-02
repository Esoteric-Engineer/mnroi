typedef unsigned char u8;
typedef unsigned long u32;
typedef long s32;
typedef long long s64;

typedef void (*CARDCallback)(s32, s32);

typedef struct CARDControl {
    s32 attached;
    u8 pad0[0xC - 4];
    s32 sectorSize;
    u8 pad1[0x94 - 0x10];
    u8 cmd[5];
    u8 pad2[0xC8 - 0x99];
    CARDCallback txCallback;
    CARDCallback exiCallback;
    u8 pad3[0xDC - 0xD0];
    CARDCallback unlockCallback;
    u8 alarm[0x110 - 0xE0];
} CARDControl;

extern CARDControl __CARDBlock[2];

u32 __OSBusClock : 0x800000F8;

extern int OSDisableInterrupts(void);
extern void OSRestoreInterrupts(int level);
extern int EXILock(s32 chan, s32 dev, void (*unlockedCb)(s32));
extern int EXISelect(s32 chan, s32 dev, s32 freq);
extern int EXIUnlock(s32 chan);
extern void OSCancelAlarm(void* alarm);
extern void OSSetAlarm(void* alarm, s64 tick, void (*handler)(void*, void*));
extern void __CARDUnlockedHandler(s32 chan);
extern void UnlockedCallback(s32 chan, s32 result);
extern void TimeoutHandler(void* alarm, void* context);

#define OSSecondsToTicks(sec) ((s64)((__OSBusClock / 4) * (sec)))
#define OSMillisecondsToTicks(msec) ((s64)((__OSBusClock / 4) / 1000 * (msec)))

static void SetupTimeoutAlarm(CARDControl* card)
{
    OSCancelAlarm(&card->alarm);
    switch (card->cmd[0]) {
    case 0xF2:
        OSSetAlarm(&card->alarm, OSMillisecondsToTicks(100), TimeoutHandler);
        break;
    case 0xF3:
        break;
    case 0xF4:
    case 0xF1:
        OSSetAlarm(&card->alarm, OSSecondsToTicks((s64)2) * (card->sectorSize / 8192), TimeoutHandler);
        break;
    }
}

s32 __CARDStart(s32 chan, CARDCallback txCallback, CARDCallback exiCallback)
{
    int enabled;
    CARDControl* card;
    s32 result;

    enabled = OSDisableInterrupts();

    card = &__CARDBlock[chan];
    if (!card->attached) {
        result = -3;
    } else {
        if (txCallback) {
            card->txCallback = txCallback;
        }
        if (exiCallback) {
            card->exiCallback = exiCallback;
        }
        card->unlockCallback = UnlockedCallback;
        if (!EXILock(chan, 0, __CARDUnlockedHandler)) {
            result = -1;
        } else {
            card->unlockCallback = 0;

            if (!EXISelect(chan, 0, 4)) {
                EXIUnlock(chan);
                result = -3;
            } else {
                SetupTimeoutAlarm(card);
                result = 0;
            }
        }
    }

    OSRestoreInterrupts(enabled);
    return result;
}
