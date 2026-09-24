typedef int BOOL;
typedef struct DVDCommandBlock {
    char pad0[0x8];
    unsigned long command;
    int state;
    char pad1[0x18];
    void (*callback)(long, struct DVDCommandBlock*);
} DVDCommandBlock;

extern volatile unsigned long lbl_8066F2E0; // Canceling
extern void (*lbl_8066F2E4)(long, DVDCommandBlock*); // CancelCallback
extern int ResumeFromHere;
extern DVDCommandBlock* executing;
extern DVDCommandBlock DummyCommandBlock;

BOOL OSDisableInterrupts(void);
void OSRestoreInterrupts(BOOL level);
void DVDLowBreak(void);
void* DVDLowClearCallback(void);
void __DVDDequeueWaitingQueue(DVDCommandBlock* block);
void stateReady(void);
void cbForStateMotorStopped(void);

int DVDCancelAsync(DVDCommandBlock* block, void (*callback)(long, DVDCommandBlock*)) {
    void* old;
    BOOL enabled;
    int state;

    enabled = OSDisableInterrupts();

    state = block->state;
    switch (state) {
    case -1:
    case 0:
    case 10:
        if (callback) {
            (*callback)(0, block);
        }
        break;

    case 1:
        if (lbl_8066F2E0) {
            OSRestoreInterrupts(enabled);
            return 0;
        }
        lbl_8066F2E0 = 1;
        lbl_8066F2E4 = callback;
        if (block->command == 4 || block->command == 1) {
            DVDLowBreak();
        }
        break;

    case 2:
        __DVDDequeueWaitingQueue(block);
        block->state = 10;
        if (block->callback) {
            (block->callback)(-3, block);
        }
        if (callback) {
            (*callback)(0, block);
        }
        break;

    case 3:
        switch (block->command) {
        case 4:
        case 5:
        case 13:
        case 15:
            if (callback) {
                (*callback)(0, block);
            }
            break;

        default:
            if (lbl_8066F2E0) {
                OSRestoreInterrupts(enabled);
                return 0;
            }
            lbl_8066F2E0 = 1;
            lbl_8066F2E4 = callback;
            break;
        }
        break;

    case 4:
    case 5:
    case 6:
    case 7:
    case 11:
        old = DVDLowClearCallback();
        if (old != (void*)cbForStateMotorStopped) {
            OSRestoreInterrupts(enabled);
            return 0;
        }

        if (block->state == 4) {
            ResumeFromHere = 3;
        }
        if (block->state == 5) {
            ResumeFromHere = 4;
        }
        if (block->state == 6) {
            ResumeFromHere = 1;
        }
        if (block->state == 11) {
            ResumeFromHere = 2;
        }
        if (block->state == 7) {
            ResumeFromHere = 7;
        }

        executing = &DummyCommandBlock;
        block->state = 10;
        if (block->callback) {
            (block->callback)(-3, block);
        }
        if (callback) {
            (callback)(0, block);
        }
        stateReady();
        break;
    }

    OSRestoreInterrupts(enabled);
    return 1;
}
