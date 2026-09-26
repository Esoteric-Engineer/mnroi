typedef unsigned char u8;
typedef short s16;
typedef long s32;
typedef unsigned short u16;
typedef unsigned long u32;

typedef void (*CARDCallback)(s32, s32);

typedef struct CARDControl {
    s32 attached;
    u8 pad4[0x8];
    u32 sectorSize;
    u8 pad10[0x80 - 0x10];
    void* workArea;
    u8 pad84[0xD8 - 0x84];
    CARDCallback eraseCallback;
    u8 padDC[0x110 - 0xDC];
} CARDControl;

extern CARDControl __CARDBlock[2];

extern void fn_8040BB30(void* ptr, s32 length, u16* checksum, u16* checksumInv);
extern void DCStoreRange(void* addr, u32 nBytes);
extern s32 fn_8040AF24(s32 chan, u32 addr, CARDCallback callback);
extern void fn_8040B5A4(s32 chan, s32 result);

s32 __CARDUpdateFatBlock(s32 chan, u16* fat, CARDCallback callback)
{
    CARDControl* card;
    u32 addr;

    card = &__CARDBlock[chan];
    ++fat[2];
    fn_8040BB30(fat + 2, 0x1FFC, fat, fat + 1);
    DCStoreRange(fat, 0x2000);
    card->eraseCallback = callback;
    addr = (((char*)fat - (char*)card->workArea) / 8192u) * card->sectorSize;
    return fn_8040AF24(chan, addr, fn_8040B5A4);
}
