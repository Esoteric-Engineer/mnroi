typedef unsigned char u8;
typedef unsigned short u16;
typedef short s16;
typedef int s32;
typedef unsigned long u32;
typedef unsigned long long u64;

typedef struct {
    u8 equ;
    u16 acv;
    u16 prbOdd;
    u16 prbEven;
    u16 psbOdd;
    u16 psbEven;
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

u16 lbl_8057D418[59];
u16 shdwRegs[59];
SomeVIStruct HorVer;
extern volatile u64 lbl_8066F3A8;
extern s16 lbl_8066F39C;
extern s16 lbl_8066F39E;
extern u32 lbl_8066F3D0;

int OSDisableInterrupts(void);
void OSRestoreInterrupts(int level);
void setFbbRegs(SomeVIStruct* horVer, u32* tfbb, u32* bfbb, u32* rtfbb, u32* rbfbb);
void setVerticalRegs(u16 dispPosY, u16 dispSizeY, u8 equ, u16 acv, u16 prbOdd, u16 prbEven,
                     u16 psbOdd, u16 psbEven, int black);

#define regs lbl_8057D418
#define displayOffsetH lbl_8066F39C
#define displayOffsetV lbl_8066F39E
#define FBSet lbl_8066F3D0
#define changed lbl_8066F3A8

#define MAX(a, b) ((a) > (b) ? (a) : (b))
#define MIN(a, b) ((a) < (b) ? (a) : (b))
#define CLAMP(val, min, max) ((val) > (max) ? (max) : (val) < (min) ? (min) : (val))

static inline void AdjustPosition(u16 acv)
{
    s32 coeff;
    s32 frac;

    HorVer.AdjustedDispPosX = CLAMP((s16)HorVer.DispPosX + displayOffsetH, 0,
                                    0x2D0 - HorVer.DispSizeX);
    coeff = (HorVer.FBMode == 0) ? 2 : 1;
    frac = HorVer.DispPosY & 1;
    HorVer.AdjustedDispPosY = MAX((s16)HorVer.DispPosY + displayOffsetV, frac);
    HorVer.AdjustedDispSizeY =
        HorVer.DispSizeY + MIN((s16)HorVer.DispPosY + displayOffsetV - frac, 0) -
        MAX((s16)HorVer.DispPosY + (s16)HorVer.DispSizeY + displayOffsetV - (((s16)acv * 2) - frac),
            0);
    HorVer.AdjustedPanPosY =
        HorVer.PanPosY - (MIN((s16)HorVer.DispPosY + displayOffsetV - frac, 0) / coeff);
    HorVer.AdjustedPanSizeY =
        HorVer.PanSizeY + (MIN((s16)HorVer.DispPosY + displayOffsetV - frac, 0) / coeff) -
        (MAX((s16)HorVer.DispPosY + (s16)HorVer.DispSizeY + displayOffsetV -
                 (((s16)acv * 2) - frac),
             0) /
         coeff);
}

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
