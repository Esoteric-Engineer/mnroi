typedef unsigned char u8;
typedef unsigned long u32;
typedef long s32;
typedef int BOOL;

typedef struct CARDControl {
    u8 pad0[0x14];
    s32 latency;
    u8 pad1[0x80 - 0x18];
    void* workArea;
    u8 pad2[0x110 - 0x84];
} CARDControl;

extern CARDControl __CARDBlock[2];

extern void* memset(void* dst, int val, u32 n);
extern int EXISelect(s32 chan, u32 dev, u32 freq);
extern int EXIImmEx(s32 chan, void* buf, s32 len, s32 type);
extern int EXIDeselect(s32 chan);

#define SEC_AD1(x) ((u8)(((x) >> 29) & 0x03))
#define SEC_AD2(x) ((u8)(((x) >> 21) & 0xff))
#define SEC_AD3(x) ((u8)(((x) >> 19) & 0x03))
#define SEC_BA(x) ((u8)(((x) >> 12) & 0x7f))

s32 ReadArrayUnlock(s32 chan, u32 data, void* rbuf, s32 rlen, s32 mode)
{
    CARDControl* card;
    BOOL err;
    u8 cmd[5];

    card = &__CARDBlock[chan];
    if (!EXISelect(chan, 0, 4))
        return -3;

    data &= 0xfffff000;
    memset(cmd, 0, 5);
    cmd[0] = 0x52;
    if (mode == 0) {
        cmd[1] = SEC_AD1(data);
        cmd[2] = SEC_AD2(data);
        cmd[3] = SEC_AD3(data);
        cmd[4] = SEC_BA(data);
    } else {
        cmd[1] = (u8)((data & 0xff000000) >> 24);
        cmd[2] = (u8)((data & 0x00ff0000) >> 16);
    }

    err = 0;
    err |= !EXIImmEx(chan, cmd, 5, 1);
    err |= !EXIImmEx(chan, (u8*)card->workArea + 0x200, card->latency, 1);
    err |= !EXIImmEx(chan, rbuf, rlen, 0);
    err |= !EXIDeselect(chan);

    return err ? -3 : 0;
}
