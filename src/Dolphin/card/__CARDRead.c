typedef unsigned char u8;
typedef unsigned long u32;
typedef long s32;

typedef void (*CARDCallback)(s32, s32);

typedef struct CARDControl {
    s32 attached;
    u8 pad0[0xAC - 0x4];
    s32 repeat;
    u32 addr;
    void* buffer;
    u8 pad1[0xD4 - 0xB8];
    CARDCallback xferCallback;
    u8 pad2[0x110 - 0xD8];
} CARDControl;

extern CARDControl __CARDBlock[2];

extern void fn_80410C48(s32 chan, s32 result);
extern s32 fn_8040ACD4(s32 chan, CARDCallback callback);

s32 __CARDRead(s32 chan, u32 addr, s32 length, void* dst, CARDCallback callback)
{
    CARDControl* card;

    card = &__CARDBlock[chan];
    if (card->attached == 0) {
        return -3;
    }
    card->xferCallback = callback;
    card->repeat = length / 512u;
    card->addr = addr;
    card->buffer = dst;
    return fn_8040ACD4(chan, fn_80410C48);
}
