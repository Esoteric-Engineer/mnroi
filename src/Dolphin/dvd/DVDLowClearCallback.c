typedef void (*DVDLowCallback)(unsigned long);

extern volatile unsigned long __DIRegs[0x20] : 0xCC006000;
extern DVDLowCallback lbl_8066F338;
extern unsigned long lbl_8066F34C;

DVDLowCallback DVDLowClearCallback(void)
{
    DVDLowCallback old;
    __DIRegs[1] = 0;
    old = lbl_8066F338;
    lbl_8066F34C = 0;
    lbl_8066F338 = 0;
    return old;
}
