static void (*FatalFunc)(void) = 0;

void __DVDPrintFatalMessage(void) {
    if (FatalFunc != 0) {
        FatalFunc();
    }
}
