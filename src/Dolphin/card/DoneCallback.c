typedef unsigned char u8;
typedef long s32;
typedef unsigned long u32;
typedef int BOOL;

typedef struct DSPTaskInfo {
    u32 pad[0x50 / 4];
} DSPTaskInfo;

typedef struct CARDControl {
    u8 pad0[0x14];
    s32 latency;
    u8 pad18[0x2C - 0x18];
    u32 scramble;
    DSPTaskInfo task;
    void* workArea;
    u8 pad84[0x110 - 0x84];
} CARDControl;

extern CARDControl __CARDBlock[2];

extern s32 DummyLen(void);
extern s32 ReadArrayUnlock(s32 chan, u32 data, void* rbuf, s32 rlen, s32 mode);
extern s32 __CARDReadStatus(s32 chan, u8* status);
extern void __CARDMountCallback(s32 chan, s32 result);
extern void EXIUnlock(s32 chan);
extern BOOL EXIProbe(s32 chan);

static u32 exnor(u32 data, u32 lshift)
{
    u32 wk;
    u32 work;
    u32 i;

    work = data;
    for (i = 0; i < lshift; i++) {
        wk = ~(work ^ (work << 7) ^ (work << 15) ^ (work << 23));
        work = (work << 1) | ((wk >> 30) & 0x00000002);
    }
    return work;
}

void DoneCallback(void* _task)
{
    u8 rbuf[64];
    u32 data;
    s32 dummy;
    s32 rlen;
    u32 rshift;

    u8 unk;
    u32 wk, wk1;
    u32 Ans2;

    s32 chan;
    CARDControl* card;
    s32 result;
    DSPTaskInfo* task;
    void* param;

    u8* input;
    u8* output;
    task = _task;
    for (chan = 0; chan < 2; ++chan) {
        card = &__CARDBlock[chan];
        if ((DSPTaskInfo*)&card->task == task)
            break;
    }

    param = card->workArea;
    input = (u8*)param + 0x10;
    input = (u8*)(((u32)input + 31) & ~31);
    output = input + 32;

    Ans2 = *(u32*)output;
    dummy = DummyLen();
    rlen = dummy;
    data = ((Ans2 ^ card->scramble) & 0xffff0000);
    if (ReadArrayUnlock(chan, data, rbuf, rlen, 1) < 0) {
        EXIUnlock(chan);
        __CARDMountCallback(chan, -3);
        return;
    }

    rshift = (u32)((dummy + 4 + card->latency) * 8 + 1);
    wk = exnor(card->scramble, rshift);
    wk1 = ~(wk ^ (wk << 7) ^ (wk << 15) ^ (wk << 23));
    card->scramble = (wk | ((wk1 >> 31) & 0x00000001));

    dummy = DummyLen();
    rlen = dummy;
    data = (((Ans2 << 16) ^ card->scramble) & 0xffff0000);
    if (ReadArrayUnlock(chan, data, rbuf, rlen, 1) < 0) {
        EXIUnlock(chan);
        __CARDMountCallback(chan, -3);
        return;
    }
    result = __CARDReadStatus(chan, &unk);
    if (!EXIProbe(chan)) {
        EXIUnlock(chan);
        __CARDMountCallback(chan, -3);
        return;
    }
    if (result == 0 && !(unk & 0x40)) {
        EXIUnlock(chan);
        result = -5;
    }
    __CARDMountCallback(chan, result);
}
