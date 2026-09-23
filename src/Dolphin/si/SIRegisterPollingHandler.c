typedef int BOOL;
typedef void (*__OSInterruptHandler)(short interrupt, void* context);

extern int OSDisableInterrupts(void);
extern int OSRestoreInterrupts(int level);
extern BOOL SIEnablePollingInterrupt(BOOL enable);

extern __OSInterruptHandler lbl_8057D1B0[4]; // RDSTHandler, start of a larger unclaimed .bss object

BOOL SIRegisterPollingHandler(__OSInterruptHandler handler) {
    BOOL enabled;
    int i;

    enabled = OSDisableInterrupts();
    for (i = 0; i < 4; i++) {
        if (lbl_8057D1B0[i] == handler) {
            OSRestoreInterrupts(enabled);
            return 1;
        }
    }

    for (i = 0; i < 4; i++) {
        if (lbl_8057D1B0[i] == 0) {
            lbl_8057D1B0[i] = handler;
            SIEnablePollingInterrupt(1);
            OSRestoreInterrupts(enabled);
            return 1;
        }
    }

    OSRestoreInterrupts(enabled);
    return 0;
}
