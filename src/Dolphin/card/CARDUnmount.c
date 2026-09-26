typedef unsigned char u8;
typedef long s32;
typedef s32 BOOL;

typedef struct CARDControl {
    BOOL attached;
    s32 result;
    u8 pad8[0x24 - 0x8];
    int mountStep;
    u8 pad28[0xE0 - 0x28];
    u8 alarm[0x28];
    u8 pad108[0x110 - 0x108];
} CARDControl;

extern CARDControl __CARDBlock[2];

extern s32 __CARDGetControlBlock(s32 chan, CARDControl** card);
extern BOOL OSDisableInterrupts(void);
extern BOOL OSRestoreInterrupts(BOOL level);
extern void OSCancelAlarm(void* alarm);
extern void* EXISetExiCallback(s32 chan, void* callback);
extern BOOL EXIDetach(s32 chan);

static inline void DoUnmount(s32 chan, s32 result)
{
    CARDControl* card;
    BOOL enabled;

    card = &__CARDBlock[chan];
    enabled = OSDisableInterrupts();
    if (card->attached) {
        EXISetExiCallback(chan, 0);
        EXIDetach(chan);
        OSCancelAlarm(&card->alarm);
        card->attached = 0;
        card->result = result;
        card->mountStep = 0;
    }
    OSRestoreInterrupts(enabled);
}

s32 CARDUnmount(s32 chan)
{
    CARDControl* card;
    s32 result;

    result = __CARDGetControlBlock(chan, &card);
    if (result < 0) {
        return result;
    }
    DoUnmount(chan, -3);
    return 0;
}
