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
extern volatile unsigned long ResumeFromHere;
extern volatile int PausingFlag;
extern int FatalErrorFlag;
extern char __DVDThreadQueue[8];
volatile unsigned long __DIRegs[0x20] : 0xCC006000;
extern DVDCommandBlock* executing;
extern DVDCommandBlock DummyCommandBlock;

BOOL OSDisableInterrupts(void);
void OSRestoreInterrupts(BOOL level);
void DVDLowBreak(void);
void* DVDLowClearCallback(void);
void __DVDDequeueWaitingQueue(DVDCommandBlock* block);
void stateReady(void);
void cbForStateMotorStopped(void);
void OSSleepThread(void* queue);
void OSWakeupThread(void* queue);
void cbForCancelSync(long result, DVDCommandBlock* block);

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

long DVDCancel(volatile DVDCommandBlock* block) {
    int result;
    long state;
    unsigned long command;
    BOOL enabled;

    result = DVDCancelAsync((DVDCommandBlock*)block, cbForCancelSync);
    if (result == 0) {
        return -1;
    }
    enabled = OSDisableInterrupts();
    while (1) {
        state = block->state;
        if (state == 0 || state == -1 || state == 10) {
            break;
        }
        if (state == 3) {
            command = block->command;
            if (command == 4 || command == 5 || command == 13 || command == 15) {
                break;
            }
        }
        OSSleepThread(__DVDThreadQueue);
    }
    OSRestoreInterrupts(enabled);
    return 0;
}

void cbForCancelSync(long result, DVDCommandBlock* block) {
    OSWakeupThread(__DVDThreadQueue);
}

void* DVDGetCurrentDiskID(void) {
    return (void*)0x80000000;
}

BOOL DVDCheckDisk(void) {
    BOOL enabled;
    BOOL retVal;
    long state;
    unsigned long coverReg;

    enabled = OSDisableInterrupts();

    if (FatalErrorFlag) {
        state = -1;
    } else if (PausingFlag) {
        state = 8;
    } else {
        if (executing == 0) {
            state = 0;
        } else if (executing == &DummyCommandBlock) {
            state = 0;
        } else {
            state = executing->state;
        }
    }

    switch (state) {
    case 1:
    case 2:
    case 9:
    case 10:
        retVal = 1;
        break;

    case -1:
    case 3:
    case 4:
    case 5:
    case 6:
    case 7:
    case 11:
        retVal = 0;
        break;

    case 0:
    case 8:
        coverReg = __DIRegs[1];
        if (((coverReg >> 2) & 1) || (coverReg & 1)) {
            retVal = 0;
        } else if (ResumeFromHere) {
            retVal = 0;
        } else {
            retVal = 1;
        }
    }

    OSRestoreInterrupts(enabled);
    return retVal;
}
