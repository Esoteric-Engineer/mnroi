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

// The SDK's vi.c from getTiming through VIConfigurePan (0x80187E38-0x8018960C). MWCC pools a
// unit's .data (version string, timing, taps) and .bss (regs, shdwRegs, HorVer); VIInit and
// VIConfigurePan only match with both pools defined in the same unit. __VIRetraceHandler, the two
// retrace-callback setters before getTiming, and VIFlush onwards are still separate units.
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
extern u32 lbl_8066F3D0;
extern int lbl_8066F3D4;
extern char lbl_8066C48C[5];

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
#define FBSet lbl_8066F3D0

#define MARK_CHANGED(index) (changed |= 1LL << (63 - (index)))

#define MAX(a, b) ((a) > (b) ? (a) : (b))
#define MIN(a, b) ((a) < (b) ? (a) : (b))
#define CLAMP(val, min, max) ((val) > (max) ? (max) : (val) < (min) ? (min) : (val))

void OSRegisterVersion(char* version);
int OSDisableInterrupts(void);
void OSRestoreInterrupts(int level);
void OSSleepThread(void* queue);
void OSReport(const char*, ...);
void OSPanic(const char*, int, const char*, ...);
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

void VIWaitForRetrace(void)
{
    int enabled;
    unsigned long count;

    enabled = OSDisableInterrupts();
    count = retraceCount;
    do {
        OSSleepThread(&retraceQueue);
    } while (count == retraceCount);
    OSRestoreInterrupts(enabled);
}

static inline void calcFbbs(u32 bufAddr, u16 panPosX, u16 panPosY, u8 wordPerLine, int xfbMode,
                            u16 dispPosY, u32* tfbb, u32* bfbb)
{
    u32 bytesPerLine;
    u32 xoffInWords;
    u32 tmp;

    xoffInWords = (panPosX & ~0xF) >> 4;
    bytesPerLine = (wordPerLine & 0xFF) << 5;
    *tfbb = bufAddr + (xoffInWords << 5) + (bytesPerLine * panPosY);
    *bfbb = (xfbMode == 0) ? *tfbb : *tfbb + bytesPerLine;
    if (dispPosY % 2 == 1) {
        tmp = *tfbb;
        *tfbb = *bfbb;
        *bfbb = tmp;
    }
    *tfbb &= 0x3FFFFFFF;
    *bfbb &= 0x3FFFFFFF;
}

void setFbbRegs(SomeVIStruct* HorVer, u32* tfbb, u32* bfbb, u32* rtfbb, u32* rbfbb)
{
    u32 shifted;

    calcFbbs(HorVer->bufAddr, HorVer->PanPosX, HorVer->AdjustedPanPosY, HorVer->wordPerLine,
             HorVer->FBMode, HorVer->AdjustedDispPosY, tfbb, bfbb);
    if (HorVer->threeD) {
        calcFbbs(HorVer->rbufAddr, HorVer->PanPosX, HorVer->AdjustedPanPosY, HorVer->wordPerLine,
                 HorVer->FBMode, HorVer->AdjustedDispPosY, rtfbb, rbfbb);
    }
    if (*tfbb < 0x01000000U && *bfbb < 0x01000000U && *rtfbb < 0x01000000U
        && *rbfbb < 0x01000000U) {
        shifted = 0;
    } else {
        shifted = 1;
    }
    if (shifted) {
        *tfbb >>= 5;
        *bfbb >>= 5;
        *rtfbb >>= 5;
        *rbfbb >>= 5;
    }

    regs[15] = (u16)*tfbb & 0xFFFF;
    MARK_CHANGED(15);
    regs[14] = (shifted << 12) | ((*tfbb >> 16) | (HorVer->xof << 8));
    MARK_CHANGED(14);
    regs[19] = (u16)*bfbb & 0xFFFF;
    MARK_CHANGED(19);
    regs[18] = (*bfbb >> 16);
    MARK_CHANGED(18);
    if (HorVer->threeD) {
        regs[17] = (u16)*rtfbb & 0xFFFF;
        MARK_CHANGED(17);
        regs[16] = *rtfbb >> 16;
        MARK_CHANGED(16);
        regs[21] = (u16)*rbfbb & 0xFFFF;
        MARK_CHANGED(21);
        regs[20] = *rbfbb >> 16;
        MARK_CHANGED(20);
    }
}

void setVerticalRegs(u16 dispPosY, u16 dispSizeY, u8 equ, u16 acv, u16 prbOdd, u16 prbEven,
                     u16 psbOdd, u16 psbEven, int black)
{
    u16 actualPrbOdd;
    u16 actualPrbEven;
    u16 actualPsbOdd;
    u16 actualPsbEven;
    u16 actualAcv;
    u16 c;
    u16 d;

    if (regs[54] & 1) {
        c = 1;
        d = 2;
    } else {
        c = 2;
        d = 1;
    }
    if ((dispPosY % 2) == 0) {
        actualPrbOdd = prbOdd + (d * dispPosY);
        actualPsbOdd = psbOdd + (d * (((c * acv) - dispSizeY) - dispPosY));
        actualPrbEven = prbEven + (d * dispPosY);
        actualPsbEven = psbEven + (d * (((c * acv) - dispSizeY) - dispPosY));
    } else {
        actualPrbOdd = prbEven + (d * dispPosY);
        actualPsbOdd = psbEven + (d * (((c * acv) - dispSizeY) - dispPosY));
        actualPrbEven = prbOdd + (d * dispPosY);
        actualPsbEven = psbOdd + (d * (((c * acv) - dispSizeY) - dispPosY));
    }
    actualAcv = dispSizeY / c;
    if (black) {
        actualPrbOdd += actualAcv * 2 - 2;
        actualPsbOdd += 2;
        actualPrbEven += actualAcv * 2 - 2;
        actualPsbEven += 2;
        actualAcv = 0;
    }
    regs[0] = equ | (actualAcv << 4);
    MARK_CHANGED(0);
    regs[7] = (u16)(u32)actualPrbOdd;
    MARK_CHANGED(7);
    regs[6] = (u16)(u32)actualPsbOdd;
    MARK_CHANGED(6);
    regs[9] = (u16)(u32)actualPrbEven;
    MARK_CHANGED(9);
    regs[8] = (u16)(u32)actualPsbEven;
    MARK_CHANGED(8);
}

// VIConfigure(rm): applies a GXRenderModeObj to the VI shadow state (HorVer/regs) with AdjustPosition,
// setInterruptRegs, setScalingRegs, setHorizontalRegs, setBBIntervalRegs and setPicConfig inlined.
// This game's version panics on an invalid TV mode; the register-heavy body is kept as asm.
asm void VIConfigure(const void* rm)
{
    // clang-format off
    nofralloc
    mflr r0
    lis r5, lbl_804D2880@ha
    stw r0, 0x4(r1)
    lis r4, lbl_8057D418@ha
    stwu r1, -0x78(r1)
    stmw r14, 0x30(r1)
    addi r31, r3, 0x0
    addi r15, r5, lbl_804D2880@l
    addi r29, r4, lbl_8057D418@l
    bl OSDisableInterrupts
    lwz r4, 0x0(r31)
    addi r28, r29, 0x114
    lwz r0, 0x114(r29)
    addi r14, r3, 0x0
    clrlwi r4, r4, 30
    cmplw r0, r4
    beq L_80188AA0
    li r0, 0x1
    stw r0, lbl_8066F3A0
    stw r4, 0x0(r28)
L_80188AA0:
    lwz r0, 0x0(r31)
    lis r3, 0x8000
    lwz r16, 0xcc(r3)
    srwi r0, r0, 2
    cmplwi r0, 0x4
    mr r17, r0
    bne L_80188B24
    lwz r0, lbl_8066F3D4
    cmplwi r0, 0x0
    bne L_80188B24
    li r0, 0x1
    crclr 6
    stw r0, lbl_8066F3D4
    addi r3, r15, 0x260
    bl OSReport
    addi r3, r15, 0x28c
    crclr 6
    bl OSReport
    addi r3, r15, 0x2b8
    crclr 6
    bl OSReport
    addi r3, r15, 0x2e4
    crclr 6
    bl OSReport
    addi r3, r15, 0x310
    crclr 6
    bl OSReport
    addi r3, r15, 0x33c
    crclr 6
    bl OSReport
    addi r3, r15, 0x260
    crclr 6
    bl OSReport
L_80188B24:
    cmpwi r16, 0x2
    beq L_80188B58
    bge L_80188B40
    cmpwi r16, 0x0
    beq L_80188B58
    bge L_80188B74
    b L_80188B84
L_80188B40:
    cmpwi r16, 0x6
    beq L_80188B58
    bge L_80188B84
    cmpwi r16, 0x5
    bge L_80188B74
    b L_80188B84
L_80188B58:
    cmplwi r17, 0x0
    beq L_80188BA0
    cmplwi r17, 0x2
    beq L_80188BA0
    cmplwi r17, 0x6
    bne L_80188B84
    b L_80188BA0
L_80188B74:
    cmplwi r17, 0x1
    beq L_80188BA0
    cmplwi r17, 0x5
    beq L_80188BA0
L_80188B84:
    addi r6, r16, 0x0
    crclr 6
    addi r7, r17, 0x0
    addi r5, r15, 0x368
    la r3, lbl_8066C48C
    li r4, 0x774
    bl OSPanic
L_80188BA0:
    cmplwi r17, 0x0
    beq L_80188BB0
    cmplwi r17, 0x2
    bne L_80188BB8
L_80188BB0:
    stw r16, 0x118(r29)
    b L_80188BBC
L_80188BB8:
    stw r17, 0x118(r29)
L_80188BBC:
    lhz r0, 0xa(r31)
    sth r0, 0xf0(r29)
    lwz r0, 0x0(r28)
    cmplwi r0, 0x1
    bne L_80188BDC
    lhz r0, 0xc(r31)
    clrlslwi r0, r0, 17, 1
    b L_80188BE0
L_80188BDC:
    lhz r0, 0xc(r31)
L_80188BE0:
    sth r0, 0xf2(r29)
    addi r23, r29, 0xf2
    addi r24, r29, 0xf4
    lhz r0, 0xe(r31)
    addi r27, r29, 0x102
    addi r25, r29, 0x110
    sth r0, 0xf4(r29)
    li r0, 0x0
    addi r16, r29, 0x10a
    lhz r3, 0x4(r31)
    addi r26, r29, 0x10c
    addi r15, r29, 0x106
    sth r3, 0x102(r29)
    addi r17, r29, 0x108
    lhz r3, 0x8(r31)
    sth r3, 0x104(r29)
    lwz r3, 0x14(r31)
    stw r3, 0x110(r29)
    lhz r3, 0x102(r29)
    sth r3, 0x10a(r29)
    lhz r3, 0x104(r29)
    sth r3, 0x10c(r29)
    sth r0, 0x106(r29)
    sth r0, 0x108(r29)
    lwz r0, 0x0(r28)
    cmplwi r0, 0x2
    bne L_80188C54
    lhz r0, 0x0(r26)
    b L_80188C80
L_80188C54:
    cmplwi r0, 0x3
    bne L_80188C64
    lhz r0, 0x0(r26)
    b L_80188C80
L_80188C64:
    lwz r0, 0x0(r25)
    cmpwi r0, 0x0
    bne L_80188C7C
    lhz r0, 0x0(r26)
    clrlslwi r0, r0, 17, 1
    b L_80188C80
L_80188C7C:
    lhz r0, 0x0(r26)
L_80188C80:
    addi r22, r29, 0xf6
    sth r0, 0xf6(r29)
    lwz r0, 0x0(r28)
    cmplwi r0, 0x3
    bne L_80188C9C
    li r0, 0x1
    b L_80188CA0
L_80188C9C:
    li r0, 0x0
L_80188CA0:
    addi r18, r29, 0x134
    stw r0, 0x134(r29)
    addi r21, r29, 0x118
    lwz r3, 0x118(r29)
    lwz r0, 0x0(r28)
    slwi r3, r3, 2
    add r3, r3, r0
    bl getTiming
    mr r30, r3
    stw r30, 0x144(r29)
    lhz r0, 0x0(r24)
    lha r4, 0xf0(r29)
    lha r3, lbl_8066F39C
    subfic r5, r0, 0x2d0
    lhz r0, 0x2(r30)
    add r3, r4, r3
    cmpw r3, r5
    ble L_80188CEC
    b L_80188CFC
L_80188CEC:
    cmpwi r3, 0x0
    bge L_80188CF8
    li r3, 0x0
L_80188CF8:
    mr r5, r3
L_80188CFC:
    sth r5, 0xf8(r29)
    addi r3, r29, 0xf8
    lwz r4, 0x0(r25)
    cmpwi r4, 0x0
    bne L_80188D18
    li r4, 0x2
    b L_80188D1C
L_80188D18:
    li r4, 0x1
L_80188D1C:
    lhz r5, 0x0(r23)
    lha r6, lbl_8066F39E
    extsh r7, r5
    clrlwi r5, r5, 31
    add r7, r7, r6
    cmpw r7, r5
    ble L_80188D3C
    b L_80188D40
L_80188D3C:
    mr r7, r5
L_80188D40:
    sth r7, 0xfa(r29)
    extsh r0, r0
    slwi r0, r0, 1
    lhz r8, 0x0(r22)
    subf r0, r5, r0
    lha r7, 0x0(r23)
    addi r19, r29, 0xfa
    extsh r9, r8
    add r10, r9, r6
    add r10, r7, r10
    subf. r9, r0, r10
    ble L_80188D78
    subf r9, r0, r10
    b L_80188D7C
L_80188D78:
    li r9, 0x0
L_80188D7C:
    add r10, r7, r6
    subf. r7, r5, r10
    bge L_80188D90
    subf r7, r5, r10
    b L_80188D94
L_80188D90:
    li r7, 0x0
L_80188D94:
    add r7, r8, r7
    subf r7, r9, r7
    addi r20, r29, 0xfc
    sth r7, 0xfc(r29)
    lha r7, 0x0(r23)
    add r8, r7, r6
    subf. r7, r5, r8
    bge L_80188DBC
    subf r7, r5, r8
    b L_80188DC0
L_80188DBC:
    li r7, 0x0
L_80188DC0:
    divw r8, r7, r4
    lhz r7, 0x0(r17)
    subf r7, r8, r7
    sth r7, 0xfe(r29)
    lha r7, 0x0(r22)
    lha r9, 0x0(r23)
    add r8, r7, r6
    add r8, r9, r8
    subf. r7, r0, r8
    ble L_80188DF0
    subf r7, r0, r8
    b L_80188DF4
L_80188DF0:
    li r7, 0x0
L_80188DF4:
    add r6, r9, r6
    subf. r0, r5, r6
    bge L_80188E08
    subf r0, r5, r6
    b L_80188E0C
L_80188E08:
    li r0, 0x0
L_80188E0C:
    divw r0, r0, r4
    lhz r5, 0x0(r26)
    divw r4, r7, r4
    add r0, r5, r0
    subf r0, r4, r0
    sth r0, 0x100(r29)
    lwz r0, lbl_8066F398
    cmplwi r0, 0x0
    bne L_80188E38
    li r0, 0x3
    stw r0, 0x0(r21)
L_80188E38:
    lhz r5, 0x18(r30)
    srawi r4, r5, 1
    addze r4, r4
    srawi r0, r5, 1
    addze r0, r0
    slwi r0, r0, 1
    subfc r0, r0, r5
    clrlwi. r0, r0, 16
    clrlwi r4, r4, 16
    beq L_80188E68
    lhz r5, 0x1a(r30)
    b L_80188E6C
L_80188E68:
    li r5, 0x0
L_80188E6C:
    addi r0, r5, 0x1
    sth r0, 0x32(r29)
    addi r0, r4, 0x1
    ori r0, r0, 0x1000
    lwz r5, lbl_8066F3A8
    addi r4, r29, 0x2
    lwz r6, lbl_8066F3A8+4
    ori r5, r5, 0x40
    stw r6, lbl_8066F3A8+4
    stw r5, lbl_8066F3A8
    sth r0, 0x30(r29)
    lwz r0, lbl_8066F3A8
    lwz r5, lbl_8066F3A8+4
    ori r0, r0, 0x80
    stw r5, lbl_8066F3A8+4
    stw r0, lbl_8066F3A8
    lwz r0, 0x0(r28)
    lhz r5, 0x2(r29)
    cmplwi r0, 0x2
    beq L_80188EC4
    cmplwi r0, 0x3
    bne L_80188ED0
L_80188EC4:
    rlwinm r0, r5, 0, 30, 28
    ori r5, r0, 0x4
    b L_80188ED8
L_80188ED0:
    rlwinm r5, r5, 0, 30, 28
    rlwimi r5, r0, 2, 29, 29
L_80188ED8:
    lwz r6, 0x0(r21)
    rlwinm r5, r5, 0, 29, 27
    lwz r7, 0x0(r18)
    cmplwi r6, 0x4
    slwi r0, r7, 3
    or r5, r5, r0
    beq L_80188F00
    subi r0, r6, 0x5
    cmplwi r0, 0x1
    bgt L_80188F08
L_80188F00:
    rlwinm r0, r5, 0, 24, 21
    b L_80188F14
L_80188F08:
    rlwinm r5, r5, 0, 24, 21
    slwi r0, r6, 8
    or r0, r5, r0
L_80188F14:
    sth r0, 0x0(r4)
    lis r0, 0x4000
    addi r6, r29, 0x6c
    lwz r4, lbl_8066F3A8
    lwz r5, lbl_8066F3A8+4
    or r0, r4, r0
    stw r5, lbl_8066F3A8+4
    stw r0, lbl_8066F3A8
    lwz r0, 0x0(r31)
    lhz r4, 0x6c(r29)
    cmpwi r0, 0x2
    beq L_80188F54
    cmpwi r0, 0x3
    beq L_80188F54
    cmpwi r0, 0x1a
    bne L_80188F60
L_80188F54:
    clrrwi r0, r4, 1
    ori r0, r0, 0x1
    b L_80188F64
L_80188F60:
    clrrwi r0, r4, 1
L_80188F64:
    sth r0, 0x0(r6)
    cmpwi r7, 0x0
    lwz r4, lbl_8066F3A8
    lwz r0, lbl_8066F3A8+4
    ori r0, r0, 0x200
    stw r0, lbl_8066F3A8+4
    stw r4, lbl_8066F3A8
    lhz r4, 0x0(r24)
    lhz r5, 0x0(r16)
    beq L_80188F94
    slwi r0, r5, 1
    b L_80188F98
L_80188F94:
    mr r0, r5
L_80188F98:
    clrlwi r8, r0, 16
    cmplw r8, r4
    bge L_80188FF0
    slwi r6, r8, 8
    subi r0, r6, 0x1
    add r0, r4, r0
    divwu r0, r0, r4
    ori r0, r0, 0x1000
    sth r0, 0x4a(r29)
    lis r0, 0x400
    lwz r6, lbl_8066F3A8
    lwz r7, lbl_8066F3A8+4
    or r0, r7, r0
    stw r0, lbl_8066F3A8+4
    stw r6, lbl_8066F3A8
    sth r8, 0x70(r29)
    lwz r6, lbl_8066F3A8
    lwz r0, lbl_8066F3A8+4
    ori r0, r0, 0x80
    stw r0, lbl_8066F3A8+4
    stw r6, lbl_8066F3A8
    b L_80189010
L_80188FF0:
    li r0, 0x100
    sth r0, 0x4a(r29)
    lis r0, 0x400
    lwz r6, lbl_8066F3A8
    lwz r7, lbl_8066F3A8+4
    or r0, r7, r0
    stw r0, lbl_8066F3A8+4
    stw r6, lbl_8066F3A8
L_80189010:
    lhz r0, 0x0(r3)
    subfic r12, r4, 0x2d0
    lhz r6, 0x1a(r30)
    lis r3, 0x1000
    lis r8, 0x2000
    sth r6, 0x6(r29)
    lis r9, 0x400
    lis r7, 0x800
    lwz r10, lbl_8066F3A8
    lis r6, 0x10
    lis r4, 0x20
    lwz r11, lbl_8066F3A8+4
    or r10, r10, r3
    lis r3, 0x4
    stw r11, lbl_8066F3A8+4
    stw r10, lbl_8066F3A8
    lbz r10, 0x1d(r30)
    lbz r11, 0x1e(r30)
    rlwimi r11, r10, 8, 16, 23
    sth r11, 0x4(r29)
    lwz r10, lbl_8066F3A8
    lwz r11, lbl_8066F3A8+4
    or r8, r10, r8
    stw r11, lbl_8066F3A8+4
    stw r8, lbl_8066F3A8
    lbz r8, 0x1f(r30)
    lbz r10, 0x1c(r30)
    add r16, r8, r0
    lhz r11, 0x20(r30)
    subi r16, r16, 0x28
    clrlslwi r8, r16, 23, 7
    or r8, r10, r8
    sth r8, 0xa(r29)
    add r8, r11, r0
    addi r0, r8, 0x28
    lwz r10, lbl_8066F3A8
    subf r0, r12, r0
    srwi r8, r16, 9
    lwz r11, lbl_8066F3A8+4
    slwi r0, r0, 1
    or r9, r10, r9
    stw r11, lbl_8066F3A8+4
    or r0, r8, r0
    stw r9, lbl_8066F3A8
    sth r0, 0x8(r29)
    lwz r0, lbl_8066F3A8
    lwz r8, lbl_8066F3A8+4
    or r0, r0, r7
    stw r8, lbl_8066F3A8+4
    stw r0, lbl_8066F3A8
    lhz r0, 0x10(r30)
    lbz r7, 0xc(r30)
    slwi r0, r0, 5
    or r0, r7, r0
    sth r0, 0x16(r29)
    lwz r0, lbl_8066F3A8
    lwz r7, lbl_8066F3A8+4
    or r0, r0, r6
    stw r7, lbl_8066F3A8+4
    stw r0, lbl_8066F3A8
    lhz r0, 0x14(r30)
    lbz r6, 0xe(r30)
    slwi r0, r0, 5
    or r0, r6, r0
    sth r0, 0x14(r29)
    lwz r0, lbl_8066F3A8
    lwz r6, lbl_8066F3A8+4
    or r0, r0, r4
    stw r6, lbl_8066F3A8+4
    stw r0, lbl_8066F3A8
    lhz r0, 0x12(r30)
    lbz r4, 0xd(r30)
    slwi r0, r0, 5
    or r0, r4, r0
    sth r0, 0x1a(r29)
    lwz r0, lbl_8066F3A8
    lwz r4, lbl_8066F3A8+4
    or r0, r0, r3
    stw r4, lbl_8066F3A8+4
    stw r0, lbl_8066F3A8
    lhz r0, 0x16(r30)
    lbz r3, 0xf(r30)
    slwi r0, r0, 5
    or r0, r3, r0
    sth r0, 0x18(r29)
    lwz r3, lbl_8066F3A8
    lis r0, 0x8
    addi r6, r29, 0x11c
    lwz r4, lbl_8066F3A8+4
    or r0, r3, r0
    stw r4, lbl_8066F3A8+4
    stw r0, lbl_8066F3A8
    lhz r3, 0x0(r27)
    lwz r4, 0x0(r25)
    addi r0, r3, 0xf
    lhz r3, 0x0(r15)
    srawi r0, r0, 4
    addze r0, r0
    cmpwi r4, 0x0
    stb r0, 0x11c(r29)
    bne L_801891AC
    lbz r4, 0x0(r6)
    b L_801891B4
L_801891AC:
    lbz r0, 0x0(r6)
    clrlslwi r4, r0, 25, 1
L_801891B4:
    srawi r0, r3, 4
    stb r4, 0x11d(r29)
    addze r0, r0
    slwi r0, r0, 4
    subfc r0, r0, r3
    stb r0, 0x12c(r29)
    addi r0, r5, 0xf
    lis r3, 0x800
    lbz r4, 0x12c(r29)
    add r0, r4, r0
    srawi r0, r0, 4
    addze r0, r0
    stb r0, 0x11e(r29)
    lbz r0, 0x11e(r29)
    lbz r4, 0x11d(r29)
    rlwimi r4, r0, 8, 16, 23
    sth r4, 0x48(r29)
    lwz r4, lbl_8066F3A8
    lwz r0, lbl_8066F3D0
    lwz r5, lbl_8066F3A8+4
    cmplwi r0, 0x0
    or r0, r5, r3
    stw r0, lbl_8066F3A8+4
    stw r4, lbl_8066F3A8
    beq L_80189230
    addi r3, r29, 0xf0
    addi r4, r29, 0x124
    addi r5, r29, 0x128
    addi r6, r29, 0x13c
    addi r7, r29, 0x140
    bl setFbbRegs
L_80189230:
    lwz r0, 0x130(r29)
    stw r0, 0x8(r1)
    lhz r3, 0x0(r19)
    lhz r4, 0x0(r20)
    lbz r5, 0x0(r30)
    lhz r6, 0x2(r30)
    lhz r7, 0x4(r30)
    lhz r8, 0x6(r30)
    lhz r9, 0x8(r30)
    lhz r10, 0xa(r30)
    bl setVerticalRegs
    mr r3, r14
    bl OSRestoreInterrupts
    lmw r14, 0x30(r1)
    lwz r0, 0x7c(r1)
    addi r1, r1, 0x78
    mtlr r0
    blr
    // clang-format on
}

// The asm function above turns peephole optimisation off for the rest of the unit.
#pragma peephole on

static inline void setScalingRegs(u16 panSizeX, u16 dispSizeX, int threeD)
{
    u32 scale;

    panSizeX = threeD ? (panSizeX << 1) : panSizeX;
    if (panSizeX < dispSizeX) {
        scale = (u32)(dispSizeX + (panSizeX << 8) - 1) / dispSizeX;
        regs[37] = scale | 0x1000;
        changed |= 0x04000000;
        regs[56] = (u32)panSizeX;
        changed |= 0x80;
    } else {
        regs[37] = 0x100;
        changed |= 0x04000000;
    }
}

static inline void setPicConfig(u16 fbSizeX, int xfbMode, u16 panPosX, u16 panSizeX,
                                u8* wordPerLine, u8* std, u8* wpl, u8* xof)
{
    *wordPerLine = (fbSizeX + 15) / 16;
    *std = (xfbMode == 0) ? *wordPerLine : (u8)(*wordPerLine * 2);
    *xof = panPosX % 16;
    *wpl = (*xof + panSizeX + 15) / 16;
    regs[0x24] = *std | (*wpl << 8);
    changed |= 0x8000000;
}

void VIConfigurePan(u16 xOrg, u16 yOrg, u16 width, u16 height)
{
    int enabled;
    VITiming* tm;

    (void)lbl_8057D418;
    (void)shdwRegs;
    (void)HorVer;
    enabled = OSDisableInterrupts();
    HorVer.PanPosX = xOrg;
    HorVer.PanPosY = yOrg;
    HorVer.PanSizeX = width;
    HorVer.PanSizeY = height;
    HorVer.DispSizeY = (HorVer.nonInter == 2)  ? HorVer.PanSizeY
                       : (HorVer.nonInter == 3) ? HorVer.PanSizeY
                       : (HorVer.FBMode == 0)   ? (u16)(HorVer.PanSizeY * 2)
                                                : HorVer.PanSizeY;
    tm = HorVer.timing;
    AdjustPosition(tm->acv);
    setScalingRegs(HorVer.PanSizeX, HorVer.DispSizeX, HorVer.threeD);
    setPicConfig(HorVer.FBSizeX, HorVer.FBMode, HorVer.PanPosX, HorVer.PanSizeX,
                 &HorVer.wordPerLine, &HorVer.std, &HorVer.wpl, &HorVer.xof);
    if (FBSet != 0) {
        setFbbRegs(&HorVer, &HorVer.tfbb, &HorVer.bfbb, &HorVer.rtfbb, &HorVer.rbfbb);
    }
    setVerticalRegs(HorVer.AdjustedDispPosY, HorVer.DispSizeY, tm->equ, tm->acv, tm->prbOdd,
                    tm->prbEven, tm->psbOdd, tm->psbEven, HorVer.black);
    OSRestoreInterrupts(enabled);
}
