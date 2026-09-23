typedef int BOOL;
typedef void (*__OSInterruptHandler)(short interrupt, void* context);

extern int OSDisableInterrupts(void);
extern int OSRestoreInterrupts(int level);
extern BOOL fn_80181DA4(BOOL enable); // SIEnablePollingInterrupt, not split yet

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
            fn_80181DA4(1);
            OSRestoreInterrupts(enabled);
            return 1;
        }
    }

    OSRestoreInterrupts(enabled);
    return 0;
}
