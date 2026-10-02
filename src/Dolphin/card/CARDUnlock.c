typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned long u32;
typedef long s32;

typedef void (*DSPCallback)(void* task);

typedef struct DSPTaskInfo {
    u32 state;
    u32 priority;
    u32 flags;
    u16* iram_mmem_addr;
    u32 iram_length;
    u32 iram_addr;
    u16* dram_mmem_addr;
    u32 dram_length;
    u32 dram_addr;
    u16 dsp_init_vector;
    u16 dsp_resume_vector;
    DSPCallback init_cb;
    DSPCallback res_cb;
    DSPCallback done_cb;
    DSPCallback req_cb;
    void* next;
    void* prev;
    long long t_context;
    long long t_task;
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

typedef struct CARDDecParam {
    u8* inputAddr;
    u32 inputLength;
    u32 aramAddr;
    u8* outputAddr;
} CARDDecParam;

extern CARDControl __CARDBlock[2];

extern u32 OSGetTick(void);
extern s32 DummyLen(void);
extern s32 ReadArrayUnlock(s32 chan, u32 data, void* rbuf, s32 rlen, s32 mode);
extern void DCFlushRange(void* addr, u32 nBytes);
extern void DCInvalidateRange(void* addr, u32 nBytes);
extern DSPTaskInfo* DSPAddTask(DSPTaskInfo* task);
extern void InitCallback(void* task);
extern void DoneCallback(void* task);
extern u32 bitrev(u32 data);

extern volatile u32 next;

u8 CardData[352] __attribute__((aligned(32))) = {
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x21, 0x02, 0xFF, 0x00, 0x21,
    0x13, 0x06, 0x12, 0x03, 0x12, 0x04, 0x13, 0x05, 0x00, 0x92, 0x00, 0xFF, 0x00, 0x88, 0xFF, 0xFF,
    0x00, 0x89, 0xFF, 0xFF, 0x00, 0x8A, 0xFF, 0xFF, 0x00, 0x8B, 0xFF, 0xFF, 0x8F, 0x00, 0x02, 0xBF,
    0x00, 0x88, 0x16, 0xFC, 0xDC, 0xD1, 0x16, 0xFD, 0x00, 0x00, 0x16, 0xFB, 0x00, 0x01, 0x02, 0xBF,
    0x00, 0x8E, 0x25, 0xFF, 0x03, 0x80, 0xFF, 0x00, 0x02, 0x94, 0x00, 0x27, 0x02, 0xBF, 0x00, 0x8E,
    0x1F, 0xDF, 0x24, 0xFF, 0x02, 0x40, 0x0F, 0xFF, 0x00, 0x98, 0x04, 0x00, 0x00, 0x9A, 0x00, 0x10,
    0x00, 0x99, 0x00, 0x00, 0x8E, 0x00, 0x02, 0xBF, 0x00, 0x94, 0x02, 0xBF, 0x86, 0x44, 0x02, 0xBF,
    0x00, 0x88, 0x16, 0xFC, 0xDC, 0xD1, 0x16, 0xFD, 0x00, 0x03, 0x16, 0xFB, 0x00, 0x01, 0x8F, 0x00,
    0x02, 0xBF, 0x00, 0x8E, 0x03, 0x80, 0xCD, 0xD1, 0x02, 0x94, 0x00, 0x48, 0x27, 0xFF, 0x03, 0x80,
    0x00, 0x01, 0x02, 0x95, 0x00, 0x5A, 0x03, 0x80, 0x00, 0x02, 0x02, 0x95, 0x80, 0x00, 0x02, 0x9F,
    0x00, 0x48, 0x00, 0x21, 0x8E, 0x00, 0x02, 0xBF, 0x00, 0x8E, 0x25, 0xFF, 0x02, 0xBF, 0x00, 0x8E,
    0x25, 0xFF, 0x02, 0xBF, 0x00, 0x8E, 0x25, 0xFF, 0x02, 0xBF, 0x00, 0x8E, 0x00, 0xC5, 0xFF, 0xFF,
    0x03, 0x40, 0x0F, 0xFF, 0x1C, 0x9F, 0x02, 0xBF, 0x00, 0x8E, 0x00, 0xC7, 0xFF, 0xFF, 0x02, 0xBF,
    0x00, 0x8E, 0x00, 0xC6, 0xFF, 0xFF, 0x02, 0xBF, 0x00, 0x8E, 0x00, 0xC0, 0xFF, 0xFF, 0x02, 0xBF,
    0x00, 0x8E, 0x20, 0xFF, 0x03, 0x40, 0x0F, 0xFF, 0x1F, 0x5F, 0x02, 0xBF, 0x00, 0x8E, 0x21, 0xFF,
    0x02, 0xBF, 0x00, 0x8E, 0x23, 0xFF, 0x12, 0x05, 0x12, 0x06, 0x02, 0x9F, 0x80, 0xB5, 0x00, 0x21,
    0x27, 0xFC, 0x03, 0xC0, 0x80, 0x00, 0x02, 0x9D, 0x00, 0x88, 0x02, 0xDF, 0x27, 0xFE, 0x03, 0xC0,
    0x80, 0x00, 0x02, 0x9C, 0x00, 0x8E, 0x02, 0xDF, 0x2E, 0xCE, 0x2C, 0xCF, 0x00, 0xF8, 0xFF, 0xCD,
    0x00, 0xF9, 0xFF, 0xC9, 0x00, 0xFA, 0xFF, 0xCB, 0x26, 0xC9, 0x02, 0xC0, 0x00, 0x04, 0x02, 0x9D,
    0x00, 0x9C, 0x02, 0xDF, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
};

static u32 exnor_1st(u32 data, u32 rshift)
{
    u32 wk;
    u32 work;
    u32 i;

    work = data;
    for (i = 0; i < rshift; i++) {
        wk = ~(work ^ (work >> 7) ^ (work >> 15) ^ (work >> 23));
        work = (work >> 1) | ((wk << 30) & 0x40000000);
    }
    return work;
}

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

static inline void srand(u32 seed)
{
    next = seed;
}

static inline s32 rand(void)
{
    u32 r;
    next = next * 1103515245 + 12345;
    r = next;
    return (r >> 16) & 0x7FFF;
}

static u32 GetInitVal(void)
{
    u32 tmp;
    u32 tick;

    tick = OSGetTick();
    srand(tick);
    tmp = 0x7fec8000;
    tmp |= rand();
    tmp &= 0xfffff000;
    return tmp;
}

s32 __CARDUnlock(s32 chan, u8 flashID[12])
{
    u32 init_val;
    u32 data;

    s32 dummy;
    s32 rlen;
    u32 rshift;

    u8 fsts;
    u32 wk, wk1;
    u32 Ans1 = 0;
    u32 Ans2 = 0;
    u32* dp;
    u8 rbuf[64];
    u32 para1A = 0;
    u32 para1B = 0;
    u32 para2A = 0;
    u32 para2B = 0;

    CARDControl* card;
    DSPTaskInfo* task;
    CARDDecParam* param;
    u8* input;
    u8* output;

    card = &__CARDBlock[chan];
    task = &card->task;
    param = (CARDDecParam*)card->workArea;
    input = (u8*)param + sizeof(CARDDecParam);
    input = (u8*)(((u32)input + 31) & ~31);
    output = input + 32;

    fsts = 0;
    init_val = GetInitVal();

    dummy = DummyLen();
    rlen = dummy;
    if (ReadArrayUnlock(chan, init_val, rbuf, rlen, 0) < 0)
        return -3;

    rshift = (u32)(dummy * 8 + 1);
    wk = exnor_1st(init_val, rshift);
    wk1 = ~(wk ^ (wk >> 7) ^ (wk >> 15) ^ (wk >> 23));
    card->scramble = (wk | ((wk1 << 31) & 0x80000000));
    card->scramble = bitrev(card->scramble);
    dummy = DummyLen();
    rlen = 20 + dummy;
    data = 0;
    if (ReadArrayUnlock(chan, data, rbuf, rlen, 1) < 0)
        return -3;

    dp = (u32*)rbuf;
    para1A = *dp++;
    para1B = *dp++;
    Ans1 = *dp++;
    para2A = *dp++;
    para2B = *dp++;
    para1A = (para1A ^ card->scramble);
    rshift = 32;
    wk = exnor(card->scramble, rshift);
    wk1 = ~(wk ^ (wk << 7) ^ (wk << 15) ^ (wk << 23));
    card->scramble = (wk | ((wk1 >> 31) & 0x00000001));
    para1B = (para1B ^ card->scramble);
    rshift = 32;
    wk = exnor(card->scramble, rshift);
    wk1 = ~(wk ^ (wk << 7) ^ (wk << 15) ^ (wk << 23));
    card->scramble = (wk | ((wk1 >> 31) & 0x00000001));
    Ans1 ^= card->scramble;
    rshift = 32;
    wk = exnor(card->scramble, rshift);
    wk1 = ~(wk ^ (wk << 7) ^ (wk << 15) ^ (wk << 23));
    card->scramble = (wk | ((wk1 >> 31) & 0x00000001));
    para2A = (para2A ^ card->scramble);
    rshift = 32;
    wk = exnor(card->scramble, rshift);
    wk1 = ~(wk ^ (wk << 7) ^ (wk << 15) ^ (wk << 23));
    card->scramble = (wk | ((wk1 >> 31) & 0x00000001));
    para2B = (para2B ^ card->scramble);
    rshift = (u32)(dummy * 8);
    wk = exnor(card->scramble, rshift);
    wk1 = ~(wk ^ (wk << 7) ^ (wk << 15) ^ (wk << 23));
    card->scramble = (wk | ((wk1 >> 31) & 0x00000001));
    rshift = 32 + 1;
    wk = exnor(card->scramble, rshift);
    wk1 = ~(wk ^ (wk << 7) ^ (wk << 15) ^ (wk << 23));
    card->scramble = (wk | ((wk1 >> 31) & 0x00000001));

    *(u32*)&input[0] = para2A;
    *(u32*)&input[4] = para2B;

    param->inputAddr = input;
    param->inputLength = 8;
    param->outputAddr = output;
    param->aramAddr = 0;

    DCFlushRange(input, 8);
    DCInvalidateRange(output, 4);
    DCFlushRange(param, sizeof(CARDDecParam));

    task->priority = 255;
    task->iram_mmem_addr = (u16*)((u32)CardData - 0x80000000);
    task->iram_length = 0x160;
    task->iram_addr = 0;
    task->dsp_init_vector = 0x10;
    task->init_cb = InitCallback;
    task->res_cb = 0;
    task->done_cb = DoneCallback;
    task->req_cb = 0;
    DSPAddTask(task);

    dp = (u32*)flashID;
    *dp++ = para1A;
    *dp++ = para1B;
    *dp = Ans1;

    return 0;
}
