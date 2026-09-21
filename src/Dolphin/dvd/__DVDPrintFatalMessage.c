extern void (*lbl_8066F318)(void);

void __DVDPrintFatalMessage(void) {
    if (lbl_8066F318 != 0) {
        lbl_8066F318();
    }
}
