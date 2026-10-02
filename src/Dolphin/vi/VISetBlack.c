typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned long u32;

extern u8 lbl_8057D418[];

int OSDisableInterrupts(void);
void OSRestoreInterrupts(int level);
void setVerticalRegs(u32 posY, u32 sizeY, u32 equ, u32 acv, u32 prbOdd, u32 prbEven, u32 psbOdd,
                 u32 psbEven, u32 black);

typedef struct VITiming {
    u8 equ;
    u16 acv;
    u16 prbOdd;
    u16 prbEven;
    u16 psbOdd;
    u16 psbEven;
} VITiming;

void VISetBlack(u32 black)
{
    int enabled;
    u8* tbl = lbl_8057D418;
    VITiming* tm;

    enabled = OSDisableInterrupts();
    *(u32*)(tbl + 0x130) = black;
    tm = *(VITiming**)(tbl + 0x144);
    setVerticalRegs(*(u16*)(tbl + 0xFA), *(u16*)(tbl + 0xF6), tm->equ, tm->acv, tm->prbOdd, tm->prbEven,
                tm->psbOdd, tm->psbEven, *(u32*)(tbl + 0x130));
    OSRestoreInterrupts(enabled);
}
