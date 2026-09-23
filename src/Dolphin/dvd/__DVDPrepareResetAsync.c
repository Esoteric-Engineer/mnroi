typedef int BOOL;
typedef struct DVDCommandBlock {
    char pad0[0x28];
    void (*callback)(long, struct DVDCommandBlock*);
} DVDCommandBlock;

extern DVDCommandBlock* executing;
extern volatile int PauseFlag;
extern volatile int PausingFlag;
extern volatile unsigned long lbl_8066F2E0;
extern void (*lbl_8066F2E4)(long, DVDCommandBlock*);

BOOL OSDisableInterrupts(void);
void OSRestoreInterrupts(BOOL level);
void __DVDClearWaitingQueue(void);
DVDCommandBlock* __DVDPopWaitingQueue(void);
int fn_80186028(DVDCommandBlock* block, void (*callback)(long, DVDCommandBlock*)); // DVDCancelAsync
void stateReady(void);

static inline void DVDPause(void)
{
    BOOL level;

    level = OSDisableInterrupts();
    PauseFlag = 1;
    if (executing == 0) {
        PausingFlag = 1;
    }
    OSRestoreInterrupts(level);
}

static inline void DVDResume(void)
{
    BOOL level;

    level = OSDisableInterrupts();
    PauseFlag = 0;
    if (PausingFlag != 0) {
        PausingFlag = 0;
        stateReady();
    }
    OSRestoreInterrupts(level);
}

static inline int DVDCancelAllAsync(void (*callback)(long, DVDCommandBlock*))
{
    BOOL enabled;
    DVDCommandBlock* p;
    int retVal;

    enabled = OSDisableInterrupts();
    DVDPause();
    while ((p = __DVDPopWaitingQueue()) != 0) {
        fn_80186028(p, 0);
    }
    if (executing) {
        retVal = fn_80186028(executing, callback);
    } else {
        retVal = 1;
        if (callback) {
            callback(0, 0);
        }
    }
    DVDResume();
    OSRestoreInterrupts(enabled);
    return retVal;
}

void __DVDPrepareResetAsync(void (*callback)(long, DVDCommandBlock*))
{
    BOOL enabled;

    enabled = OSDisableInterrupts();
    __DVDClearWaitingQueue();
    if (lbl_8066F2E0) {
        lbl_8066F2E4 = callback;
    } else {
        if (executing) {
            executing->callback = 0;
        }
        DVDCancelAllAsync(callback);
    }
    OSRestoreInterrupts(enabled);
}
