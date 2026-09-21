typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned long u32;
typedef unsigned long long u64;
typedef short s16;
typedef int s32;

typedef struct OSContext OSContext;
typedef void (*VIRetraceCallback)(u32);
typedef void (*VIPositionCallback)(s16, s16);

extern volatile u16 __VIRegs[0x100] : 0xCC002000;

extern volatile u32 lbl_8066F37C;
extern volatile u32 lbl_8066F380;
extern u8 lbl_8066F384[8];
extern VIRetraceCallback CoverCallback;
extern VIRetraceCallback ResetCoverCallback;
extern VIPositionCallback lbl_8066F394;
extern volatile u32 lbl_8066F3B0;
extern volatile u64 lbl_8066F3B8;
extern u32 lbl_8066F3C0;
extern u32 CurrTvMode;
extern u32 lbl_8066F3C8;
extern u32 lbl_8066F3CC;
extern u8 lbl_8057D418[];

void OSClearContext(OSContext* context);
void OSSetCurrentContext(OSContext* context);
void OSWakeupThread(void* queue);
void SIRefreshSamplingRate(void);
void fn_80189BB0(s16* x, s16* y);
u32 getCurrentFieldEvenOdd(void);

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

static inline int VISetRegs(u8* tbl)
{
    s32 regIndex;

    if (lbl_8066F3B0 != 1 || getCurrentFieldEvenOdd() != 0) {
        while (lbl_8066F3B8 != 0) {
            regIndex = cntlzd(lbl_8066F3B8);
            __VIRegs[regIndex] = ((u16*)(tbl + 0x78))[regIndex];
            lbl_8066F3B8 &= ~((u64)1 << (63 - regIndex));
        }
        lbl_8066F3B0 = 0;
        lbl_8066F3C0 = *(u32*)(tbl + 0x144);
        CurrTvMode = *(u32*)(tbl + 0x118);
        lbl_8066F3CC = lbl_8066F3C8;
        return 1;
    }
    return 0;
}

void __VIRetraceHandler(s32 unused, OSContext* context)
{
    u8* tbl = lbl_8057D418;
    u8 ctx[0x2C8];
    u16 reg;
    u32 inter;
    s16 x;
    s16 y;

    inter = 0;
    reg = __VIRegs[0x18];
    if (reg & 0x8000) {
        __VIRegs[0x18] = reg & ~0x8000;
        inter |= 1;
    }
    reg = __VIRegs[0x1A];
    if (reg & 0x8000) {
        __VIRegs[0x1A] = reg & ~0x8000;
        inter |= 2;
    }
    reg = __VIRegs[0x1C];
    if (reg & 0x8000) {
        __VIRegs[0x1C] = reg & ~0x8000;
        inter |= 4;
    }
    reg = __VIRegs[0x1E];
    if (reg & 0x8000) {
        __VIRegs[0x1E] = reg & ~0x8000;
        inter |= 8;
    }

    if ((inter & 4) || (inter & 8)) {
        OSClearContext((OSContext*)ctx);
        OSSetCurrentContext((OSContext*)ctx);
        if (lbl_8066F394) {
            fn_80189BB0(&x, &y);
            lbl_8066F394(x, y);
        }
        OSClearContext((OSContext*)ctx);
        OSSetCurrentContext(context);
        return;
    }

    lbl_8066F37C += 1;
    OSClearContext((OSContext*)ctx);
    OSSetCurrentContext((OSContext*)ctx);
    if (CoverCallback) {
        CoverCallback(lbl_8066F37C);
    }
    if (lbl_8066F380 != 0) {
        if (VISetRegs(tbl) != 0) {
            lbl_8066F380 = 0;
            SIRefreshSamplingRate();
        }
    }
    if (ResetCoverCallback) {
        OSClearContext((OSContext*)ctx);
        ResetCoverCallback(lbl_8066F37C);
    }
    OSWakeupThread(lbl_8066F384);
    OSClearContext((OSContext*)ctx);
    OSSetCurrentContext(context);
}
