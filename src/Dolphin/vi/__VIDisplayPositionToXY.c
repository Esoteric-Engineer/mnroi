typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned long u32;
typedef short s16;

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
} VITiming;

typedef struct {
    u16 pad[15];
    int FBMode;
    u32 nonInter;
} VIHorVer;

extern VIHorVer HorVer;
extern VITiming* lbl_8066F3C0;

void __VIDisplayPositionToXY(u32 hcount, u32 vcount, s16* x, s16* y)
{
    u32 halfLine;
    u32 equ3;

    halfLine = ((vcount - 1) * 2) + ((hcount - 1) / lbl_8066F3C0->hlw);
    if (HorVer.nonInter == 0) {
        if (halfLine < lbl_8066F3C0->nhlines) {
            equ3 = lbl_8066F3C0->equ * 3;
            if (halfLine < lbl_8066F3C0->prbOdd + equ3) {
                *y = -1;
            } else if (halfLine >= lbl_8066F3C0->nhlines - lbl_8066F3C0->psbOdd) {
                *y = -1;
            } else {
                *y = (halfLine - equ3 - lbl_8066F3C0->prbOdd) & ~1;
            }
        } else {
            halfLine -= lbl_8066F3C0->nhlines;
            equ3 = lbl_8066F3C0->equ * 3;
            if (halfLine < lbl_8066F3C0->prbEven + equ3) {
                *y = -1;
            } else if (halfLine >= lbl_8066F3C0->nhlines - lbl_8066F3C0->psbEven) {
                *y = -1;
            } else {
                *y = ((halfLine - equ3 - lbl_8066F3C0->prbEven) & ~1) + 1;
            }
        }
    } else if (HorVer.nonInter == 1) {
        if (halfLine >= lbl_8066F3C0->nhlines) {
            halfLine -= lbl_8066F3C0->nhlines;
        }
        equ3 = lbl_8066F3C0->equ * 3;
        if (halfLine < lbl_8066F3C0->prbOdd + equ3) {
            *y = -1;
        } else if (halfLine >= lbl_8066F3C0->nhlines - lbl_8066F3C0->psbOdd) {
            *y = -1;
        } else {
            *y = (halfLine - equ3 - lbl_8066F3C0->prbOdd) & ~1;
        }
    } else if (HorVer.nonInter == 2) {
        if (halfLine < lbl_8066F3C0->nhlines) {
            equ3 = lbl_8066F3C0->equ * 3;
            if (halfLine < lbl_8066F3C0->prbOdd + equ3) {
                *y = -1;
            } else if (halfLine >= lbl_8066F3C0->nhlines - lbl_8066F3C0->psbOdd) {
                *y = -1;
            } else {
                *y = halfLine - equ3 - lbl_8066F3C0->prbOdd;
            }
        } else {
            halfLine -= lbl_8066F3C0->nhlines;
            equ3 = lbl_8066F3C0->equ * 3;
            if (halfLine < lbl_8066F3C0->prbEven + equ3) {
                *y = -1;
            } else if (halfLine >= lbl_8066F3C0->nhlines - lbl_8066F3C0->psbEven) {
                *y = -1;
            } else {
                *y = (halfLine - equ3 - lbl_8066F3C0->prbEven) & ~1;
            }
        }
    }
    *x = hcount - 1;
}
