typedef long s32;
typedef unsigned long u32;

extern u32 OSGetTick(void);

// Seed shared with the other inlined srand/rand users in CARDUnlock.
extern volatile u32 lbl_8066CF00;

static inline void srand(u32 seed)
{
    lbl_8066CF00 = seed;
}

static inline s32 rand(void)
{
    u32 r;
    lbl_8066CF00 = lbl_8066CF00 * 1103515245 + 12345;
    r = lbl_8066CF00;
    return (r >> 16) & 0x7FFF;
}

s32 DummyLen(void)
{
    u32 tick;
    u32 wk;
    s32 tmp;
    u32 max;

    wk = 1;
    max = 0;
    tick = OSGetTick();
    srand(tick);

    tmp = rand();
    tmp &= 0x0000001f;
    tmp += 1;
    while ((tmp < 4) && (max < 10)) {
        tick = OSGetTick();
        tmp = (s32)(tick << wk);
        wk++;
        if (wk > 16)
            wk = 1;
        srand((u32)tmp);
        tmp = rand();
        tmp &= 0x0000001f;
        tmp += 1;
        max++;
    }
    if (tmp < 4)
        tmp = 4;

    return tmp;
}
