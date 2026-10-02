typedef int BOOL;
typedef struct DVDCommandBlock {
    char pad[0xC];
    int state;
} DVDCommandBlock;

extern BOOL OSDisableInterrupts(void);
extern void OSRestoreInterrupts(BOOL level);

extern int FatalErrorFlag;
extern int PausingFlag;
extern DVDCommandBlock* executing;
extern DVDCommandBlock DummyCommandBlock;

static inline int DVDGetCommandBlockStatus(const DVDCommandBlock* block) {
    BOOL enabled;
    int retVal;

    enabled = OSDisableInterrupts();
    if (block->state == 3) {
        retVal = 1;
    } else {
        retVal = block->state;
    }
    OSRestoreInterrupts(enabled);
    return retVal;
}

int DVDGetDriveStatus(void) {
    BOOL enabled;
    int retVal;

    enabled = OSDisableInterrupts();
    if (FatalErrorFlag != 0) {
        retVal = -1;
    } else {
        if (PausingFlag != 0) {
            retVal = 8;
        } else {
            if (executing == 0) {
                retVal = 0;
            } else if (executing == &DummyCommandBlock) {
                retVal = 0;
            } else {
                retVal = DVDGetCommandBlockStatus(executing);
            }
        }
    }
    OSRestoreInterrupts(enabled);
    return retVal;
}
