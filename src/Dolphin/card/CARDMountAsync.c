typedef unsigned char u8;
typedef unsigned long u32;
typedef long s32;
typedef int BOOL;

typedef void (*CARDCallback)(s32, s32);

typedef struct CARDControl {
    BOOL attached;
    s32 result;
    u8 pad8[0x24 - 0x8];
    s32 mountStep;
    u8 pad28[0x80 - 0x28];
    void* workArea;
    CARDCallback currentDir;
    CARDCallback currentFat;
    u8 pad8C[0xC4 - 0x8C];
    CARDCallback extCallback;
    u8 padC8[0xCC - 0xC8];
    CARDCallback exiCallback;
    CARDCallback apiCallback;
    u8 padD4[0xDC - 0xD4];
    CARDCallback unlockCallback;
    u8 alarm[0x28];
    u8 pad108[0x110 - 0x108];
} CARDControl;

extern CARDControl __CARDBlock[2];
extern u8 __gUnknown800030E3 : 0x800030E3;

extern BOOL OSDisableInterrupts(void);
extern BOOL OSRestoreInterrupts(BOOL level);
extern void OSCancelAlarm(void* alarm);
extern u32 EXIGetState(s32 chan);
extern BOOL EXIAttach(s32 chan, void* extHandler);
extern void* EXISetExiCallback(s32 chan, void* callback);
extern BOOL EXILock(s32 chan, u32 dev, void* unlockedCallback);
extern void __CARDDefaultApiCallback(s32 chan, s32 result);
extern void __CARDExtHandler(s32 chan, void* context);
extern void __CARDUnlockedHandler(s32 chan);
extern void __CARDMountCallback(s32 chan, s32 result);
extern s32 DoMount(s32 chan);

s32 CARDMountAsync(s32 chan, void* workArea, CARDCallback detachCallback, CARDCallback attachCallback)
{
    CARDControl* card;
    BOOL enabled;

    if (chan < 0 || 2 <= chan)
        return -128;

    if (__gUnknown800030E3 & 0x80) {
        return -3;
    }

    card = &__CARDBlock[chan];

    enabled = OSDisableInterrupts();
    if (card->result == -1) {
        OSRestoreInterrupts(enabled);
        return -1;
    }

    if (!card->attached && (EXIGetState(chan) & 0x08)) {
        OSRestoreInterrupts(enabled);
        return -2;
    }

    card->result = -1;
    card->workArea = workArea;
    card->extCallback = detachCallback;
    card->apiCallback = attachCallback ? attachCallback : __CARDDefaultApiCallback;
    card->exiCallback = 0;

    if (!card->attached && !EXIAttach(chan, __CARDExtHandler)) {
        card->result = -3;
        OSRestoreInterrupts(enabled);
        return -3;
    }

    card->mountStep = 0;
    card->attached = 1;
    EXISetExiCallback(chan, 0);
    OSCancelAlarm(&card->alarm);

    card->currentDir = 0;
    card->currentFat = 0;

    OSRestoreInterrupts(enabled);

    card->unlockCallback = __CARDMountCallback;
    if (!EXILock(chan, 0, __CARDUnlockedHandler))
        return 0;

    card->unlockCallback = 0;
    return DoMount(chan);
}
