typedef int BOOL;

extern volatile int PauseFlag;
extern volatile int PausingFlag;

BOOL OSDisableInterrupts(void);
BOOL OSRestoreInterrupts(BOOL level);
void stateReady(void);

void DVDResume(void) {
    BOOL level;

    level = OSDisableInterrupts();
    PauseFlag = 0;
    if (PausingFlag != 0) {
        PausingFlag = 0;
        stateReady();
    }
    OSRestoreInterrupts(level);
}
