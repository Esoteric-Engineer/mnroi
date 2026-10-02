typedef unsigned char u8;
typedef unsigned long u32;
typedef long s32;
typedef long long s64;

typedef void (*CARDCallback)(s32, s32);

typedef struct CARDControl {
    s32 attached;
    u8 pad0[0xC - 4];
    s32 sectorSize;
    s32 cardSize;
    s32 latency;
    u8 pad1[0x80 - 0x18];
    void* workArea;
    u8 pad2[0x94 - 0x84];
    u8 cmd[5];
    u8 pad3[0xA0 - 0x99];
    s32 cmdlen;
    u32 mode;
    u8 pad4[0xB4 - 0xA8];
    void* buffer;
    u8 pad5[0xE0 - 0xB8];
    u8 alarm[0x110 - 0xE0];
} CARDControl;

extern CARDControl __CARDBlock[2];

u32 __OSBusClock : 0x800000F8;

extern int EXISelect(s32 chan, s32 dev, s32 freq);
extern int EXIUnlock(s32 chan);
extern int EXIDeselect(s32 chan);
extern int EXIImmEx(s32 chan, void* buf, s32 len, s32 type);
extern int EXIDma(s32 chan, void* buf, s32 len, s32 type, void (*callback)(s32, void*));
extern void OSCancelAlarm(void* alarm);
extern void OSSetAlarm(void* alarm, s64 tick, void (*handler)(void*, void*));
extern void TimeoutHandler(void* alarm, void* context);
extern void __CARDTxHandler(s32 chan, void* context);

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

s32 Retry(s32 chan)
{
    CARDControl* card;

    card = &__CARDBlock[chan];
    if (!EXISelect(chan, 0, 4)) {
        EXIUnlock(chan);
        return -3;
    }

    SetupTimeoutAlarm(card);

    if (!EXIImmEx(chan, card->cmd, card->cmdlen, 1)) {
        EXIDeselect(chan);
        EXIUnlock(chan);
        return -3;
    }

    if (card->cmd[0] == 0x52 && !EXIImmEx(chan, (u8*)card->workArea + 512, card->latency, 1)) {
        EXIDeselect(chan);
        EXIUnlock(chan);
        return -3;
    }

    if (card->mode == 0xFFFFFFFF) {
        EXIDeselect(chan);
        EXIUnlock(chan);
        return 0;
    }

    if (!EXIDma(chan, card->buffer, (card->cmd[0] == 0x52) ? 512 : 128, card->mode, __CARDTxHandler)) {
        EXIDeselect(chan);
        EXIUnlock(chan);
        return -3;
    }

    return 0;
}
