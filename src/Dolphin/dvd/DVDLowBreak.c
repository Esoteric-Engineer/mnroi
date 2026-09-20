typedef int BOOL;

extern volatile BOOL lbl_8066F330;
extern volatile BOOL lbl_8066F350;

BOOL DVDLowBreak(void) {
    lbl_8066F330 = 1;
    lbl_8066F350 = 1;
    return 1;
}
