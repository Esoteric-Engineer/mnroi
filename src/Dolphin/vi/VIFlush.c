typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned long u32;
typedef unsigned long long u64;
typedef long s32;

extern u8 lbl_8057D418[];
extern volatile u32 lbl_8066F3A0;
extern volatile u64 lbl_8066F3A8;
extern volatile u32 lbl_8066F3B0;
extern volatile u64 lbl_8066F3B8;
extern u32 lbl_8066F380;
extern u32 lbl_8066F3C8;

int OSDisableInterrupts(void);
void OSRestoreInterrupts(int level);

static inline s32 cntlzd(u64 bit)
{
    u32 hi;
    u32 lo;
    s32 value;

    hi = bit >> 32;
    lo = bit & 0xFFFFFFFF;
    value = __cntlzw(hi);
    if (value < 32) {
        return value;
    }
    return __cntlzw(lo) + 32;
}

void VIFlush(void)
{
    u8* tbl = lbl_8057D418;
    int enabled;
    s32 regIndex;

    enabled = OSDisableInterrupts();
    lbl_8066F3B0 |= lbl_8066F3A0;
    lbl_8066F3A0 = 0;
    lbl_8066F3B8 |= lbl_8066F3A8;
    while (lbl_8066F3A8 != 0) {
        regIndex = cntlzd(lbl_8066F3A8);
        ((u16*)(tbl + 0x78))[regIndex] = ((u16*)tbl)[regIndex];
        lbl_8066F3A8 &= ~((u64)1 << (63 - regIndex));
    }
    lbl_8066F380 = 1;
    lbl_8066F3C8 = *(u32*)(tbl + 0x120);
    OSRestoreInterrupts(enabled);
}
