typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned long u32;

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

VITiming* getTiming(unsigned long mode);
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
