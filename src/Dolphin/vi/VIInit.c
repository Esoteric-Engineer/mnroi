typedef unsigned char u8;
typedef signed char s8;
typedef short s16;
typedef unsigned short u16;
typedef unsigned long u32;
typedef long s32;
typedef unsigned long long u64;

extern volatile u16 __VIRegs[0x100] : 0xCC002000;

typedef struct {
    u8 equ;
    u16 acv;
    u16 prbOdd;
    u16 prbEven;
    u16 psbOdd;
    u16 psbEven;
    u8 bs1;
    u8 bs2;
    u8 bs3;
    u8 bs4;
    u16 be1;
    u16 be2;
    u16 be3;
    u16 be4;
    u16 nhlines;
    u16 hlw;
    u8 hsy;
    u8 hcs;
    u8 hce;
    u8 hbe640;
    u16 hbs640;
    u8 hbeCCIR656;
    u16 hbsCCIR656;
} VITiming;

typedef struct {
    u16 DispPosX;
    u16 DispPosY;
    u16 DispSizeX;
    u16 DispSizeY;
    u16 AdjustedDispPosX;
    u16 AdjustedDispPosY;
    u16 AdjustedDispSizeY;
    u16 AdjustedPanPosY;
    u16 AdjustedPanSizeY;
    u16 FBSizeX;
    u16 FBSizeY;
    u16 PanPosX;
    u16 PanPosY;
    u16 PanSizeX;
    u16 PanSizeY;
    int FBMode;
    u32 nonInter;
    u32 tv;
    u8 wordPerLine;
    u8 std;
    u8 wpl;
    u32 bufAddr;
    u32 tfbb;
    u32 bfbb;
    u8 xof;
    int black;
    int threeD;
    u32 rbufAddr;
    u32 rtfbb;
    u32 rbfbb;
    VITiming* timing;
} SomeVIStruct;

typedef struct OSSram {
    u16 checkSum;
    u16 checkSumInv;
    u32 ead0;
    u32 ead1;
    u32 counterBias;
    s8 dispH;
    u8 ntd;
    u8 language;
    u8 flags;
} OSSram;

typedef struct {
    void* head;
    void* tail;
} OSThreadQueue;

// getTiming, __VIInit and VIInit: the start of the SDK's vi.c after the retrace callbacks. MWCC
// pools a unit's .data (version string, timing, taps) and .bss (regs, shdwRegs, HorVer), and
// VIInit only matches with both pools defined here.
char lbl_804D2880[] = "<< Dolphin SDK - VI\trelease build: Apr 17 2003 12:33:22 (0x2301) >>";

static VITiming timing[10] = {
    { 6, 240, 24, 25, 3, 2, 12, 13, 12, 13, 520, 519, 520, 519, 525, 429, 64, 71, 105, 162, 373, 122, 412 },
    { 6, 240, 24, 24, 4, 4, 12, 12, 12, 12, 520, 520, 520, 520, 526, 429, 64, 71, 105, 162, 373, 122, 412 },
    { 5, 287, 35, 36, 1, 0, 13, 12, 11, 10, 619, 618, 617, 620, 625, 432, 64, 75, 106, 172, 380, 133, 420 },
    { 5, 287, 33, 33, 2, 2, 13, 11, 13, 11, 619, 621, 619, 621, 624, 432, 64, 75, 106, 172, 380, 133, 420 },
    { 6, 240, 24, 25, 3, 2, 16, 15, 14, 13, 518, 517, 516, 519, 525, 429, 64, 78, 112, 162, 373, 122, 412 },
    { 6, 240, 24, 24, 4, 4, 16, 14, 16, 14, 518, 520, 518, 520, 526, 429, 64, 78, 112, 162, 373, 122, 412 },
    { 12, 480, 48, 48, 6, 6, 24, 24, 24, 24, 1038, 1038, 1038, 1038, 1050, 429, 64, 71, 105, 162, 373, 122, 412 },
    { 12, 480, 44, 44, 10, 10, 24, 24, 24, 24, 1038, 1038, 1038, 1038, 1050, 429, 64, 71, 105, 168, 379, 122, 412 },
    { 6, 241, 24, 25, 1, 0, 12, 13, 12, 13, 520, 519, 520, 519, 525, 429, 64, 71, 105, 159, 370, 122, 412 },
    { 12, 480, 48, 48, 6, 6, 24, 24, 24, 24, 1038, 1038, 1038, 1038, 1050, 429, 64, 71, 105, 180, 391, 122, 412 },
};

u16 taps_804D2A40[25] = { 0x01F0, 0x01DC, 0x01AE, 0x0174, 0x0129, 0x00DB, 0x008E, 0x0046, 0x000C,
                          0x00E2, 0x00CB, 0x00C0, 0x00C4, 0x00CF, 0x00DE, 0x00EC, 0x00FC, 0x0008,
                          0x000F, 0x0013, 0x0013, 0x000F, 0x000C, 0x0008, 0x0001 };

u16 lbl_8057D418[59];
u16 shdwRegs[59];
SomeVIStruct HorVer;

extern char* lbl_8066C488;
extern int lbl_8066F378;
extern u32 lbl_8066F398;
extern volatile u32 lbl_8066F37C;
extern volatile u32 lbl_8066F380;
extern OSThreadQueue lbl_8066F384;
extern void* CoverCallback;
extern void* ResetCoverCallback;
extern s16 lbl_8066F39C;
extern s16 lbl_8066F39E;
extern volatile u32 lbl_8066F3A0;
extern volatile u64 lbl_8066F3A8;
extern volatile u32 lbl_8066F3B0;
extern volatile u64 lbl_8066F3B8;
extern VITiming* lbl_8066F3C0;
extern u32 CurrTvMode;

#define regs lbl_8057D418
#define taps taps_804D2A40
#define __VIVersion lbl_8066C488
#define IsInitialized lbl_8066F378
#define encoderType lbl_8066F398
#define retraceCount lbl_8066F37C
#define flushFlag lbl_8066F380
#define retraceQueue lbl_8066F384
#define displayOffsetH lbl_8066F39C
#define displayOffsetV lbl_8066F39E
#define changeMode lbl_8066F3A0
#define changed lbl_8066F3A8
#define shdwChangeMode lbl_8066F3B0
#define shdwChanged lbl_8066F3B8
#define CurrTiming lbl_8066F3C0

void OSRegisterVersion(char* version);
OSSram* __OSLockSram(void);
void __OSUnlockSram(int commit);
void OSInitThreadQueue(OSThreadQueue* queue);
void __OSSetInterruptHandler(int interrupt, void* handler);
void __OSUnmaskInterrupts(u32 mask);
void __VIRetraceHandler(short interrupt, void* context);

#pragma dont_inline on
VITiming* getTiming(unsigned long mode)
{
    // Emit nothing. They pin the pooled .bss order (regs, shdwRegs, HorVer) and make the .bss
    // base the unit's first pool use, as __VIRetraceHandler does at the top of the real vi.c;
    // otherwise VIInit gets the .data and .bss base registers swapped.
    (void)regs;
    (void)shdwRegs;
    (void)HorVer;
    switch (mode) {
    case 0:
        return &timing[0];
    case 1:
        return &timing[1];
    case 4:
        return &timing[2];
    case 5:
        return &timing[3];
    case 20:
        return &timing[0];
    case 21:
        return &timing[1];
    case 8:
        return &timing[4];
    case 9:
        return &timing[5];
    case 2:
        return &timing[6];
    case 3:
        return &timing[7];
    case 16:
        return &timing[2];
    case 17:
        return &timing[3];
    case 24:
        return &timing[8];
    case 26:
        return &timing[9];
    default:
        return 0;
    }
}
#pragma dont_inline reset

void __VIInitPhilips(void);
// Constant in this SDK, so the Philips branches fold away; its local still puts `a` at 0x1c.
inline static u32 getEncoderType(void) { return 1; }

void __VIInit(int mode)
{
    VITiming* tm;
    u32 nonInter;
    u32 tv;
    volatile u32 a;
    u16 hct;
    u16 vct;
    u32 encoderType;

    encoderType = getEncoderType();
    if (encoderType == 0) {
        __VIInitPhilips();
    }

    nonInter = mode & 2;
    tv = (u32)mode >> 2;
    *(u32*)0x800000CC = tv;
    if (encoderType == 0) {
        tv = 3;
    }
    tm = getTiming(mode);
    __VIRegs[1] = 2;

    for (a = 0; a < 1000; a++) { }

    __VIRegs[1] = 0;
    __VIRegs[3] = (u32)tm->hlw;
    __VIRegs[2] = tm->hce | (tm->hcs << 8);
    __VIRegs[5] = tm->hsy | (tm->hbe640 << 7);
    __VIRegs[4] = (tm->hbs640 & 0x7FFF) << 1;
    if (encoderType == 0) {
        __VIRegs[0x39] = tm->hbeCCIR656 | 0x8000;
        __VIRegs[0x3A] = (u32)tm->hbsCCIR656;
    }
    __VIRegs[0] = (u32)tm->equ;
    __VIRegs[7] = (u32)(tm->prbOdd + (tm->acv * 2) - 2);
    __VIRegs[6] = (u32)(tm->psbOdd + 2);
    __VIRegs[9] = (u32)(tm->prbEven + (tm->acv * 2) - 2);
    __VIRegs[8] = (u32)(tm->psbEven + 2);
    __VIRegs[11] = tm->bs1 | (tm->be1 << 5);
    __VIRegs[10] = tm->bs3 | (tm->be3 << 5);
    __VIRegs[13] = tm->bs2 | (tm->be2 << 5);
    __VIRegs[12] = tm->bs4 | (tm->be4 << 5);
    __VIRegs[36] = 0x2828;
    __VIRegs[27] = 1;
    __VIRegs[26] = 0x1001;
    hct = tm->hlw + 1;
    vct = (tm->nhlines / 2) + 1;
    __VIRegs[25] = (u16)(u32)hct;
    __VIRegs[24] = vct | 0x1000;
    if (mode != 2 && mode != 3 && mode != 0x1A) {
        __VIRegs[1] = (nonInter << 2) | 1 | (tv << 8);
        __VIRegs[54] = 0;
        return;
    }
    __VIRegs[1] = (tv << 8) | 5;
    __VIRegs[54] = 1;
}

#define MAX(a, b) ((a) > (b) ? (a) : (b))
#define MIN(a, b) ((a) < (b) ? (a) : (b))
#define CLAMP(val, min, max) ((val) > (max) ? (max) : (val) < (min) ? (min) : (val))

inline static void AdjustPosition(u16 acv)
{
    s32 coeff;
    s32 frac;

    HorVer.AdjustedDispPosX = CLAMP((s16)HorVer.DispPosX + displayOffsetH, 0, 0x2D0 - HorVer.DispSizeX);
    coeff = (HorVer.FBMode == 0) ? 2 : 1;
    frac = HorVer.DispPosY & 1;
    HorVer.AdjustedDispPosY = MAX((s16)HorVer.DispPosY + displayOffsetV, frac);
    HorVer.AdjustedDispSizeY = HorVer.DispSizeY + MIN((s16)HorVer.DispPosY + displayOffsetV - frac, 0)
                               - MAX((s16)HorVer.DispPosY + (s16)HorVer.DispSizeY + displayOffsetV
                                         - (((s16)acv * 2) - frac),
                                     0);
    HorVer.AdjustedPanPosY = HorVer.PanPosY - (MIN((s16)HorVer.DispPosY + displayOffsetV - frac, 0) / coeff);
    HorVer.AdjustedPanSizeY = HorVer.PanSizeY + (MIN((s16)HorVer.DispPosY + displayOffsetV - frac, 0) / coeff)
                              - (MAX((s16)HorVer.DispPosY + (s16)HorVer.DispSizeY + displayOffsetV
                                         - (((s16)acv * 2) - frac),
                                     0)
                                 / coeff);
}

inline static void ImportAdjustingValues(void)
{
    OSSram* sram = __OSLockSram();

    displayOffsetH = sram->dispH;
    displayOffsetV = 0;
    __OSUnlockSram(0);
}

void VIInit(void)
{
    u16 dspCfg;
    u32 value;
    u32 tv;
    u32 tvInBootrom;

    if (IsInitialized) {
        return;
    }
    OSRegisterVersion(__VIVersion);
    IsInitialized = 1;
    encoderType = getEncoderType();
    if (!(__VIRegs[1] & 1)) {
        __VIInit(0);
    }
    retraceCount = 0;
    changed = 0;
    shdwChanged = 0;
    changeMode = 0;
    shdwChangeMode = 0;
    flushFlag = 0;
    __VIRegs[39] = taps[0] | ((taps[1] & 0x3F) << 10);
    __VIRegs[38] = (taps[1] >> 6) | (taps[2] << 4);
    __VIRegs[41] = taps[3] | ((taps[4] & 0x3F) << 10);
    __VIRegs[40] = (taps[4] >> 6) | (taps[5] << 4);
    __VIRegs[43] = taps[6] | ((taps[7] & 0x3F) << 10);
    __VIRegs[42] = (taps[7] >> 6) | (taps[8] << 4);
    __VIRegs[45] = taps[9] | (taps[10] << 8);
    __VIRegs[44] = taps[11] | (taps[12] << 8);
    __VIRegs[47] = taps[13] | (taps[14] << 8);
    __VIRegs[46] = taps[15] | (taps[16] << 8);
    __VIRegs[49] = taps[17] | (taps[18] << 8);
    __VIRegs[48] = taps[19] | (taps[20] << 8);
    __VIRegs[51] = taps[21] | (taps[22] << 8);
    __VIRegs[50] = taps[23] | (taps[24] << 8);
    __VIRegs[56] = 0x280;

    ImportAdjustingValues();

    tvInBootrom = *(u32*)0x800000CC;
    dspCfg = __VIRegs[1];
    // Mask-then-shift: the `(dspCfg >> 8) & 3` form schedules `cmplwi` one slot early.
    HorVer.nonInter = (dspCfg & 4) >> 2;
    HorVer.tv = (dspCfg & 0x300) >> 8;
    if (tvInBootrom == 1 && HorVer.tv == 0) {
        HorVer.tv = 5;
    }
    tv = (HorVer.tv == 3) ? 0 : HorVer.tv;
    HorVer.timing = getTiming((tv << 2) + HorVer.nonInter);

    regs[1] = dspCfg;

    CurrTiming = HorVer.timing;
    CurrTvMode = HorVer.tv;

    HorVer.DispSizeX = 0x280;
    HorVer.DispSizeY = CurrTiming->acv * 2;

    HorVer.DispPosX = (0x2D0 - HorVer.DispSizeX) / 2;
    HorVer.DispPosY = 0;

    AdjustPosition(CurrTiming->acv);

    HorVer.FBSizeX = 0x280;
    HorVer.FBSizeY = CurrTiming->acv * 2;
    HorVer.PanPosX = 0;
    HorVer.PanPosY = 0;
    HorVer.PanSizeX = 0x280;
    HorVer.PanSizeY = CurrTiming->acv * 2;
    HorVer.FBMode = 0;
    HorVer.wordPerLine = 0x28;
    HorVer.std = 0x28;
    HorVer.wpl = 0x28;
    HorVer.xof = 0;
    HorVer.black = 1;
    HorVer.threeD = 0;

    OSInitThreadQueue(&retraceQueue);

    value = __VIRegs[24];
    value &= ~0x8000;
    value = (u16)value;
    __VIRegs[24] = value;

    value = __VIRegs[26];
    value = value & ~0x8000;
    value = (u16)value;
    __VIRegs[26] = value;

    CoverCallback = 0;
    ResetCoverCallback = 0;
    __OSSetInterruptHandler(0x18, __VIRetraceHandler);
    __OSUnmaskInterrupts(0x80);
}
