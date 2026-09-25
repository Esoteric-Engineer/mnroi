typedef unsigned char u8;
typedef unsigned long u32;
typedef long s32;

typedef void (*CARDCallback)(s32, s32);

typedef struct CARDControl {
    u8 pad0[0x94];
    u8 cmd[5];
    u8 pad1[0xA0 - 0x99];
    s32 cmdlen;
    s32 mode;
    s32 retry;
    u8 pad2[0xB0 - 0xAC];
    u32 addr;
    void* buffer;
    u8 pad3[0xCC - 0xB8];
    CARDCallback exiCallback;
    u8 pad4[0x110 - 0xD0];
} CARDControl;

extern CARDControl __CARDBlock[2];

extern s32 fn_8040AB20(s32 chan, s32 dev, CARDCallback callback);
extern void fn_8040A3B8(s32 chan, s32 result);
extern int EXIImmEx(s32 chan, void* buf, s32 len, s32 type);
extern int EXIDma(s32 chan, void* buf, s32 len, s32 type, CARDCallback callback);
extern int EXIDeselect(s32 chan);
extern int EXIUnlock(s32 chan);

s32 __CARDWritePage(s32 chan, CARDCallback callback)
{
    CARDControl* card;
    s32 result;

    card = &__CARDBlock[chan];
    card->cmd[0] = 0xF2;
    card->cmd[1] = (u8)((card->addr >> 17) & 0x7f);
    card->cmd[2] = (u8)((card->addr >> 9) & 0xff);
    card->cmd[3] = (u8)((card->addr >> 7) & 0x03);
    card->cmd[4] = (u8)(card->addr & 0x7f);
    card->cmdlen = 5;
    card->mode = 1;
    card->retry = 3;

    result = fn_8040AB20(chan, 0, callback);
    if (result == -1) {
        result = 0;
    } else if (result >= 0) {
        if (!EXIImmEx(chan, card->cmd, card->cmdlen, 1) || !EXIDma(chan, card->buffer, 128, card->mode, fn_8040A3B8)) {
            card->exiCallback = 0;
            EXIDeselect(chan);
            EXIUnlock(chan);
            result = -3;
        } else {
            result = 0;
        }
    }
    return result;
}
