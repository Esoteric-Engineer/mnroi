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

typedef struct {
    u16 regs[59];
    u16 shdwRegs[59];
    u8 pad[4];
    SomeVIStruct HorVer;
} VIBss;

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

extern VIBss lbl_8057D418;
extern char lbl_804D2880[];
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

void OSRegisterVersion(char* version);
void __VIInit(int mode);
OSSram* __OSLockSram(void);
void __OSUnlockSram(int commit);
VITiming* getTiming(unsigned long mode);
void OSInitThreadQueue(OSThreadQueue* queue);
void __OSSetInterruptHandler(int interrupt, void* handler);
void __OSUnmaskInterrupts(u32 mask);
void __VIRetraceHandler(short interrupt, void* context);

#define regs ((u16*)tbl)
#define HorVer (((VIBss*)tbl)->HorVer)
#define taps(n) (((u16*)pool)[0xE0 + (n)])
#define displayOffsetH lbl_8066F39C
#define displayOffsetV lbl_8066F39E

#define MAX(a, b) ((a) > (b) ? (a) : (b))
#define MIN(a, b) ((a) < (b) ? (a) : (b))
#define CLAMP(val, min, max) ((val) > (max) ? (max) : (val) < (min) ? (min) : (val))

static inline void AdjustPosition(u8* tbl, u16 acv)
{
    s32 coeff;
    s32 frac;
    s32 offV;

    HorVer.AdjustedDispPosX = CLAMP((s16)HorVer.DispPosX + displayOffsetH, 0, 0x2D0 - HorVer.DispSizeX);
    coeff = (HorVer.FBMode == 0) ? 2 : 1;
    offV = displayOffsetV;
    frac = HorVer.DispPosY & 1;
    HorVer.AdjustedDispPosY = MAX((s16)HorVer.DispPosY + offV, frac);
    HorVer.AdjustedDispSizeY = HorVer.DispSizeY + MIN((s16)HorVer.DispPosY + offV - frac, 0)
                               - MAX((s16)HorVer.DispPosY + (s16)HorVer.DispSizeY + offV
                                         - (((s16)acv * 2) - frac),
                                     0);
    HorVer.AdjustedPanPosY = HorVer.PanPosY - (MIN((s16)HorVer.DispPosY + offV - frac, 0) / coeff);
    HorVer.AdjustedPanSizeY = HorVer.PanSizeY + (MIN((s16)HorVer.DispPosY + offV - frac, 0) / coeff)
                              - (MAX((s16)HorVer.DispPosY + (s16)HorVer.DispSizeY + offV
                                         - (((s16)acv * 2) - frac),
                                     0)
                                 / coeff);
}

static inline void ImportAdjustingValues(void)
{
    OSSram* sram = __OSLockSram();

    displayOffsetH = sram->dispH;
    displayOffsetV = 0;
    __OSUnlockSram(0);
}

void VIInit(void)
{
    u16 dspCfg;
    u8* pool = (u8*)lbl_804D2880;
    u8* tbl = (u8*)&lbl_8057D418;
    u32 value;
    u32 tv;
    u32 bootTv;
    u16* acv;

    if (lbl_8066F378 == 0) {
        OSRegisterVersion(lbl_8066C488);
        lbl_8066F378 = 1;
        lbl_8066F398 = 1;
        if (!(__VIRegs[1] & 1)) {
            __VIInit(0);
        }
        lbl_8066F37C = 0;
        lbl_8066F3A8 = 0;
        lbl_8066F3B8 = 0;
        lbl_8066F3A0 = 0;
        lbl_8066F3B0 = 0;
        lbl_8066F380 = 0;
        __VIRegs[39] = taps(0) | ((taps(1) & 0x3F) << 10);
        __VIRegs[38] = (taps(1) >> 6) | (taps(2) << 4);
        __VIRegs[41] = taps(3) | ((taps(4) & 0x3F) << 10);
        __VIRegs[40] = (taps(4) >> 6) | (taps(5) << 4);
        __VIRegs[43] = taps(6) | ((taps(7) & 0x3F) << 10);
        __VIRegs[42] = (taps(7) >> 6) | (taps(8) << 4);
        __VIRegs[45] = taps(9) | (taps(10) << 8);
        __VIRegs[44] = taps(11) | (taps(12) << 8);
        __VIRegs[47] = taps(13) | (taps(14) << 8);
        __VIRegs[46] = taps(15) | (taps(16) << 8);
        __VIRegs[49] = taps(17) | (taps(18) << 8);
        __VIRegs[48] = taps(19) | (taps(20) << 8);
        __VIRegs[51] = taps(21) | (taps(22) << 8);
        __VIRegs[50] = taps(23) | (taps(24) << 8);
        __VIRegs[56] = 0x280;

        ImportAdjustingValues();

        dspCfg = __VIRegs[1];
        bootTv = *(u32*)0x800000CC;
        HorVer.nonInter = (dspCfg >> 2) & 1;
        HorVer.tv = (dspCfg >> 8) & 3;
        if (bootTv == 1 && HorVer.tv == 0) {
            HorVer.tv = 5;
        }
        tv = (HorVer.tv == 3) ? 0 : HorVer.tv;
        HorVer.timing = getTiming((tv << 2) + HorVer.nonInter);

        regs[1] = dspCfg;

        lbl_8066F3C0 = HorVer.timing;
        CurrTvMode = HorVer.tv;

        HorVer.DispSizeX = 0x280;
        acv = (u16*)lbl_8066F3C0;
        acv++;
        HorVer.DispSizeY = *acv * 2;

        HorVer.DispPosX = (0x2D0 - HorVer.DispSizeX) / 2;
        HorVer.DispPosY = 0;

        AdjustPosition(tbl, *acv);

        HorVer.FBSizeX = 0x280;
        HorVer.FBSizeY = (*acv & 0x7FFF) << 1;
        HorVer.PanPosX = 0;
        HorVer.PanPosY = 0;
        HorVer.PanSizeX = 0x280;
        HorVer.PanSizeY = (*acv & 0x7FFF) << 1;
        HorVer.FBMode = 0;
        HorVer.wordPerLine = 0x28;
        HorVer.std = 0x28;
        HorVer.wpl = 0x28;
        HorVer.xof = 0;
        HorVer.black = 1;
        HorVer.threeD = 0;

        OSInitThreadQueue(&lbl_8066F384);

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
}
