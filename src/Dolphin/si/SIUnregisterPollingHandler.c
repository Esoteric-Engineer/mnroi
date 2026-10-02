typedef int BOOL;
typedef void (*__OSInterruptHandler)(short interrupt, void* context);

extern int OSDisableInterrupts(void);
extern int OSRestoreInterrupts(int level);
extern BOOL SIEnablePollingInterrupt(BOOL enable);

extern __OSInterruptHandler RDSTHandler[4];

BOOL SIUnregisterPollingHandler(__OSInterruptHandler handler) {
    BOOL enabled;
    int i;

    enabled = OSDisableInterrupts();
    for (i = 0; i < 4; i++) {
        if (RDSTHandler[i] == handler) {
            RDSTHandler[i] = 0;

            for (i = 0; i < 4; i++) {
                if (RDSTHandler[i] != 0) {
                    break;
                }
            }

            if (i == 4) {
                SIEnablePollingInterrupt(0);
            }

            OSRestoreInterrupts(enabled);
            return 1;
        }
    }

    OSRestoreInterrupts(enabled);
    return 0;
}
