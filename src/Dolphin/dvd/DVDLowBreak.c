typedef int BOOL;

extern volatile BOOL StopAtNextInt;
extern volatile BOOL lbl_8066F350;

BOOL DVDLowBreak(void) {
    StopAtNextInt = 1;
    lbl_8066F350 = 1;
    return 1;
}
