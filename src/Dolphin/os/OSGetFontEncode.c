typedef unsigned short u16;

extern u16 lbl_8066CEB8;
extern void (*lbl_8066F9B4)(void);
extern void fn_80403570(void);
extern volatile u16 __VIRegs[0x100] : 0xCC002000;

u16 OSGetFontEncode(void)
{
    if (lbl_8066CEB8 != 0xFFFF) {
        return lbl_8066CEB8;
    }
    switch (*(int*)0x800000CC) {
    case 0:
        lbl_8066CEB8 = (__VIRegs[55] & 2) ? 1 : 0;
        break;
    case 1:
    case 2:
    case 3:
    case 4:
    case 5:
    default:
        lbl_8066CEB8 = 0;
    }
    lbl_8066F9B4 = fn_80403570;
    return lbl_8066CEB8;
}
