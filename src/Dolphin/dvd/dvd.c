typedef unsigned int u32;
typedef int s32;
typedef long long s64;

typedef struct DVDCommandBlock DVDCommandBlock;
struct DVDCommandBlock
{
    unsigned char pad[0x8];
    u32 command;
    s32 state;
    u32 offset;
    u32 length;
    void* addr;
    u32 currTransferSize;
    u32 transferredSize;
    void* id;
    void (*callback)(s32 result, DVDCommandBlock* block);
    void* userData;
};

typedef struct OSBootInfo
{
    unsigned char pad[0x20];
    u32 magic;
    unsigned char pad2[0x14];
    u32 fstLocation;
    u32 fstLength;
} OSBootInfo;

extern int DVDInitialized;
extern int FirstTimeInBootrom;
extern OSBootInfo* bootInfo;
extern void* IDShouldBe;
extern u32 __DVDThreadQueue[2];
extern char* __DVDVersion;
extern void* LastState;
extern char lbl_8066C41C[6];
extern volatile u32 NumInternalRetry;
extern u32 lbl_8066F2F0;
extern DVDCommandBlock* executing;
void stateTimeout(void);
void stateGettingError(void);
extern void stateReady(void);
extern u32 CancelLastError;
extern int PauseFlag;
extern int PausingFlag;
extern DVDCommandBlock* __DVDPopWaitingQueue(void);
extern int __DVDCheckWaitingQueue(void);
extern void __DVDPrintFatalMessage(void);
extern void __DVDStoreErrorCode(u32 error);
extern void DVDReset(void);
extern void DVDLowRequestError(void* callback);
void cbForStateGettingError(u32 intType);
extern volatile u32 ResumeFromHere;
extern void DVDLowStopMotor(void* callback);
extern void DVDLowReset(void);
extern void DVDLowSeek(u32 offset, void* callback);
void stateGoToRetry(void);
void cbForStateGoToRetry(u32 intType);
extern volatile u32 CurrCommand;
extern int ResetRequired;
void cbForUnrecoveredErrorRetry(u32 intType);
extern void cbForStateMotorStopped(u32 intType);
extern int DVDLowWaitCoverClose(void* callback);
void stateMotorStopped(void);
void stateCoverClosed(void);
extern void cbForUnrecoveredError(u32 intType);
extern int FatalErrorFlag;
extern volatile u32 lbl_8066F2E0;
extern void (*lbl_8066F2E4)(s32 result, DVDCommandBlock* block);

extern void OSPanic(const char* file, int line, const char* msg, ...);
extern void DVDLowRead(void* addr, u32 length, u32 offset, void* callback);
void cbForStateReadingFST(u32 intType);

extern int fn_80186958(void* id1, void* id2);
extern void* memcpy(void* dst, const void* src, u32 n);
extern int memcmp(const void* a, const void* b, u32 n);
extern void DCInvalidateRange(void* addr, u32 nBytes);
extern void DVDLowAudioBufferConfig(u32 enable, u32 size, void* callback);
void cbForStateCheckID3(u32 intType);
extern void stateBusy(DVDCommandBlock* block);
void cbForStateBusy(u32 intType);
extern u32 lbl_804D21F8[3];
extern u32 lbl_8066C424[1];
extern void fn_801875BC(void* buf, void* callback);
extern void fn_801878AC(u32 cmd, void* callback);
extern void fn_80187814(u32 cmd, u32 length, u32 offset, void* callback);
extern void fn_80187778(void* buf, void* callback);
extern void (*lbl_8066C418)(DVDCommandBlock* block, void* callback);
extern int lbl_8066F2D4;
void cbForStateCheckID2a(u32 intType);
void stateCheckID2a(DVDCommandBlock* block);
void cbForStateCheckID2(u32 intType);
void stateCheckID2(DVDCommandBlock* block);
void stateCheckID3(DVDCommandBlock* block);
void cbForStateCheckID1(u32 intType);

extern void OSRegisterVersion(const char* version);
extern void __DVDFSInit(void);
extern void __DVDClearWaitingQueue(void);
extern void OSCreateAlarm(void* alarm);
extern void OSSetAlarm(void* alarm, s64 tick, void* handler);
extern void __DVDInitWA(void);
extern void __DVDInterruptHandler(void);
extern void OSInitThreadQueue(void* queue);
extern void __fstLoad(void);
extern void __OSSetInterruptHandler(int interrupt, void* handler);
extern void __OSUnmaskInterrupts(u32 mask);
extern void OSReport(const char* msg, ...);

volatile u32 __DIRegs[0x20] : 0xCC006000;

// The SDK has these as statics (BB2, CurrDiskID, DummyCommandBlock, ResetAlarm), which stay global here for the unmatched asm.
// MWCC lays out referenced globals in first-use order and the rest in reverse declaration order, so cbForStateReadingFST carries a no-code use of lbl_8057D240 to keep it second.
unsigned char lbl_8057D290[0x28];
DVDCommandBlock DummyCommandBlock;
unsigned char lbl_8057D240[0x20] __attribute__((aligned(32)));
u32 tmpBuffer[8] __attribute__((aligned(32)));

void fn_80183DC8(void)
{
}

void DVDInit(void)
{
    u32* magic;

    if (DVDInitialized == 0) {
        OSRegisterVersion(__DVDVersion);
        DVDInitialized = 1;
        __DVDFSInit();
        __DVDClearWaitingQueue();
        __DVDInitWA();
        bootInfo = (OSBootInfo*)0x80000000;
        IDShouldBe = (void*)0x80000000;
        __OSSetInterruptHandler(0x15, __DVDInterruptHandler);
        __OSUnmaskInterrupts(0x400);
        OSInitThreadQueue(__DVDThreadQueue);
        __DIRegs[0] = 0x2A;
        __DIRegs[1] = 0;
        magic = &bootInfo->magic;
        if (*magic == 0xE5207C22) {
            OSReport("load fst\n");
            __fstLoad();
        } else if (*magic != 0x0D15EA5E) {
            FirstTimeInBootrom = 1;
        }
    }
}

void stateReadingFST(void)
{
    LastState = stateReadingFST;
    if (bootInfo->fstLength < tmpBuffer[2]) {
        OSPanic(lbl_8066C41C, 0x28A, "DVDChangeDisk(): FST in the new disc is too big.   ");
    }
    DVDLowRead((void*)bootInfo->fstLocation, (tmpBuffer[2] + 0x1F) & ~0x1F, tmpBuffer[1], cbForStateReadingFST);
}

void cbForStateReadingFST(u32 intType)
{
    DVDCommandBlock* finished;
    (void)lbl_8057D240;

    if (intType == 16) {
        executing->state = -1;
        stateTimeout();
        return;
    }
    if (intType & 1) {
        NumInternalRetry = 0;
        __DVDFSInit();
        finished = executing;
        executing = &DummyCommandBlock;
        finished->state = 0;
        if (finished->callback) {
            finished->callback(0, finished);
        }
        stateReady();
        return;
    }
    stateGettingError();
}

void cbForStateError(u32 intType)
{
    DVDCommandBlock* finished;

    if (intType == 16) {
        executing->state = -1;
        stateTimeout();
        return;
    }
    __DVDPrintFatalMessage();
    FatalErrorFlag = 1;
    finished = executing;
    executing = &DummyCommandBlock;
    if (finished->callback) {
        finished->callback(-1, finished);
    }
    if (lbl_8066F2E0) {
        lbl_8066F2E0 = 0;
        if (lbl_8066F2E4) {
            lbl_8066F2E4(0, finished);
        }
    }
    stateReady();
}

void stateTimeout(void)
{
    __DVDStoreErrorCode(0x01234568);
    DVDReset();
    cbForStateError(0);
}

void stateGettingError(void)
{
    DVDLowRequestError(cbForStateGettingError);
}

u32 CategorizeError(u32 error)
{
    if (error == 0x20400) {
        lbl_8066F2F0 = error;
        return 1;
    }

    error &= 0x00FFFFFF;
    if (error == 0x62800 || error == 0x23A00 || error == 0xB5A01) {
        return 0;
    }
    NumInternalRetry += 1;
    if ((s32)NumInternalRetry == 2) {
        if (error == lbl_8066F2F0) {
            lbl_8066F2F0 = error;
            return 1;
        }
        lbl_8066F2F0 = error;
        return 2;
    }

    lbl_8066F2F0 = error;

    if (error == 0x31100 || executing->command == 5) {
        return 2;
    }

    return 3;
}

static inline void stateError(u32 error)
{
    __DVDStoreErrorCode(error);
    DVDLowStopMotor(cbForStateError);
}

static inline int CheckCancel(u32 resume)
{
    DVDCommandBlock* finished;

    if (lbl_8066F2E0) {
        ResumeFromHere = resume;
        lbl_8066F2E0 = 0;
        finished = executing;
        executing = &DummyCommandBlock;
        finished->state = 10;
        if (finished->callback) {
            finished->callback(-3, finished);
        }
        if (lbl_8066F2E4) {
            lbl_8066F2E4(0, finished);
        }
        stateReady();
        return 1;
    }
    return 0;
}

void cbForStateGettingError(u32 intType)
{
    u32 error;
    u32 status;
    u32 errorCategory;
    u32 resume;

    if (intType == 16) {
        executing->state = -1;
        stateTimeout();
        return;
    }
    if (intType & 2) {
        executing->state = -1;
        stateError(0x1234567);
        return;
    }

    error = __DIRegs[8];
    status = error & 0xFF000000;
    errorCategory = CategorizeError(error);

    if (errorCategory == 1) {
        executing->state = -1;
        stateError(error);
        return;
    }

    if (errorCategory == 2 || errorCategory == 3) {
        resume = 0;
    } else if (status == 0x01000000) {
        resume = 4;
    } else if (status == 0x02000000) {
        resume = 6;
    } else if (status == 0x03000000) {
        resume = 3;
    } else {
        resume = 5;
    }

    if (CheckCancel(resume)) {
        return;
    }

    if (errorCategory == 2) {
        __DVDStoreErrorCode(error);
        stateGoToRetry();
        return;
    }
    if (errorCategory == 3) {
        if ((error & 0x00FFFFFF) == 0x00031100) {
            DVDLowSeek(executing->offset, cbForUnrecoveredError);
        } else {
            ((void (*)(DVDCommandBlock*))LastState)(executing);
        }
        return;
    }

    if (status == 0x01000000) {
        executing->state = 5;
        stateMotorStopped();
    } else if (status == 0x02000000) {
        executing->state = 3;
        stateCoverClosed();
    } else if (status == 0x03000000) {
        executing->state = 4;
        stateMotorStopped();
    } else {
        executing->state = -1;
        stateError(0x1234567);
    }
}

void cbForUnrecoveredError(u32 intType)
{
    if (intType == 16) {
        executing->state = -1;
        stateTimeout();
        return;
    }

    if (intType & 1) {
        stateGoToRetry();
        return;
    }

    DVDLowRequestError(cbForUnrecoveredErrorRetry);
}

void cbForUnrecoveredErrorRetry(u32 intType)
{
    if (intType == 16) {
        executing->state = -1;
        __DVDStoreErrorCode(0x01234568);
        DVDReset();
        cbForStateError(0);
    } else {
        executing->state = -1;
        if (intType & 2) {
            __DVDStoreErrorCode(0x01234567);
            DVDLowStopMotor(cbForStateError);
            return;
        }
        __DVDStoreErrorCode(__DIRegs[8]);
        DVDLowStopMotor(cbForStateError);
    }
}

void stateGoToRetry(void)
{
    DVDLowStopMotor(cbForStateGoToRetry);
}

void cbForStateGoToRetry(u32 intType)
{
    if (intType == 16) {
        executing->state = -1;
        __DVDStoreErrorCode(0x01234568);
        DVDReset();
        cbForStateError(0);
        return;
    }

    if (intType & 2) {
        executing->state = -1;
        __DVDStoreErrorCode(0x01234567);
        DVDLowStopMotor(cbForStateError);
        return;
    }

    NumInternalRetry = 0;

    if ((CurrCommand == 4) || (CurrCommand == 5) || (CurrCommand == 13) || (CurrCommand == 15)) {
        ResetRequired = 1;
    }

    if (!CheckCancel(2)) {
        executing->state = 11;
        stateMotorStopped();
    }
}

void stateCheckID(void)
{
    switch ((int)CurrCommand) {
    case 3:
        if (fn_80186958(lbl_8057D240, executing->id)) {
            memcpy(IDShouldBe, lbl_8057D240, 0x20);
            executing->state = 1;
            DCInvalidateRange(tmpBuffer, 0x20);
            LastState = stateCheckID2;
            stateCheckID2(executing);
        } else {
            DVDLowStopMotor(cbForStateCheckID1);
        }
        break;
    default:
        if (memcmp(lbl_8057D240, IDShouldBe, 0x20)) {
            DVDLowStopMotor(cbForStateCheckID1);
        } else {
            LastState = stateCheckID3;
            stateCheckID3(executing);
        }
        break;
    }
}

void stateCheckID3(DVDCommandBlock* block)
{
    DVDLowAudioBufferConfig(((unsigned char*)IDShouldBe)[8], 10, cbForStateCheckID3);
}

void stateCheckID2(DVDCommandBlock* block)
{
    DVDLowAudioBufferConfig(((unsigned char*)IDShouldBe)[8], 10, cbForStateCheckID2a);
}

void cbForStateCheckID2a(u32 intType)
{
    if (intType == 0x10) {
        executing->state = -1;
        __DVDStoreErrorCode(0x01234568);
        DVDReset();
        cbForStateError(0);
        return;
    }

    if (intType & 1) {
        NumInternalRetry = 0;
        stateCheckID2a(executing);
    } else {
        DVDLowRequestError(cbForStateGettingError);
    }
}

void stateCheckID2a(DVDCommandBlock* block)
{
    DVDLowRead(tmpBuffer, 0x20, 0x420, cbForStateCheckID2);
}

void cbForStateCheckID1(u32 intType)
{
    if (intType == 16) {
        executing->state = -1;
        __DVDStoreErrorCode(0x01234568);
        DVDReset();
        cbForStateError(0);
        return;
    }

    if (intType & 2) {
        executing->state = -1;
        __DVDStoreErrorCode(0x01234567);
        DVDLowStopMotor(cbForStateError);
        return;
    }

    NumInternalRetry = 0;

    if (!CheckCancel(1)) {
        executing->state = 6;
        stateMotorStopped();
    }
}

void cbForStateCheckID2(u32 intType)
{
    if (intType == 16) {
        executing->state = -1;
        __DVDStoreErrorCode(0x01234568);
        DVDReset();
        cbForStateError(0);
        return;
    }

    if (intType & 1) {
        NumInternalRetry = 0;
        LastState = stateReadingFST;
        if (bootInfo->fstLength < tmpBuffer[2]) {
            OSPanic(lbl_8066C41C, 0x28A, "DVDChangeDisk(): FST in the new disc is too big.   ");
        }
        DVDLowRead((void*)bootInfo->fstLocation, (tmpBuffer[2] + 0x1F) & ~0x1F, tmpBuffer[1], cbForStateReadingFST);
    } else {
        DVDLowRequestError(cbForStateGettingError);
    }
}

void cbForStateCheckID3(u32 intType)
{
    if (intType == 16) {
        executing->state = -1;
        __DVDStoreErrorCode(0x01234568);
        DVDReset();
        cbForStateError(0);
        return;
    }

    if (intType & 1) {
        NumInternalRetry = 0;
        if (!CheckCancel(0)) {
            executing->state = 1;
            stateBusy(executing);
        }
    } else {
        DVDLowRequestError(cbForStateGettingError);
    }
}

extern void stateReadingID(DVDCommandBlock* block);

void AlarmHandler_80184B70(void* alarm, void* context)
{
    DVDReset();
    DCInvalidateRange(lbl_8057D240, 0x20);
    LastState = stateReadingID;
    stateReadingID(executing);
}

void stateCoverClosed(void)
{
    DVDCommandBlock* finished;

    switch ((int)CurrCommand) {
    case 4:
    case 5:
    case 13:
    case 15:
        __DVDClearWaitingQueue();
        finished = executing;
        executing = &DummyCommandBlock;
        if (finished->callback) {
            finished->callback(-4, finished);
        }
        stateReady();
        break;
    default:
        DVDReset();
        OSCreateAlarm(lbl_8057D290);
        OSSetAlarm(lbl_8057D290, (s64)(((*(u32*)0x800000F8 / 4) / 1000) * 1150), AlarmHandler_80184B70);
        break;
    }
}

extern void cbForStateReadingID(u32 intType);
#pragma dont_inline on
void stateReadingID(DVDCommandBlock* block)
{
    fn_801875BC(lbl_8057D240, cbForStateReadingID);
}
#pragma dont_inline reset

void cbForStateReadingID(u32 intType)
{
    if (intType == 0x10) {
        executing->state = -1;
        __DVDStoreErrorCode(0x01234568);
        DVDReset();
        cbForStateError(0);
        return;
    }

    if (intType & 1) {
        NumInternalRetry = 0;
        stateCheckID();
    } else {
        DVDLowRequestError(cbForStateGettingError);
    }
}

#pragma dont_inline on
void stateMotorStopped(void)
{
    DVDLowWaitCoverClose(cbForStateMotorStopped);
}
#pragma dont_inline reset

void cbForStateMotorStopped(u32 intType)
{
    __DIRegs[1] = 0;
    executing->state = 3;
    stateCoverClosed();
}

void stateReady(void)
{
    DVDCommandBlock* finished;

    if (__DVDCheckWaitingQueue() == 0) {
        executing = 0;
        return;
    }
    if (PauseFlag != 0) {
        PausingFlag = 1;
        executing = 0;
        return;
    }
    executing = __DVDPopWaitingQueue();
    if (FatalErrorFlag) {
        executing->state = -1;
        finished = executing;
        executing = &DummyCommandBlock;
        if (finished->callback) {
            finished->callback(-1, finished);
        }
        stateReady();
        return;
    }
    CurrCommand = executing->command;
    if (ResumeFromHere != 0) {
        switch (ResumeFromHere) {
        case 2:
            executing->state = 11;
            DVDLowWaitCoverClose(cbForStateMotorStopped);
            break;
        case 3:
            executing->state = 4;
            DVDLowWaitCoverClose(cbForStateMotorStopped);
            break;
        case 4:
            executing->state = 5;
            DVDLowWaitCoverClose(cbForStateMotorStopped);
            break;
        case 1:
        case 6:
        case 7:
            executing->state = 3;
            stateCoverClosed();
            break;
        case 5:
            executing->state = -1;
            stateError(CancelLastError);
            break;
        }
        ResumeFromHere = 0;
        return;
    }
    executing->state = 1;
    stateBusy(executing);
}

void stateBusy(DVDCommandBlock* block)
{
    LastState = stateBusy;
    switch (block->command) {
    case 5:
        __DIRegs[1] = __DIRegs[1];
        block->currTransferSize = 0x20;
        fn_801875BC(block->addr, cbForStateBusy);
        return;
    case 1:
    case 4:
        if (block->length == 0) {
            DVDCommandBlock* finished = executing;
            executing = &DummyCommandBlock;
            finished->state = 0;
            if (finished->callback) {
                finished->callback(0, finished);
            }
            stateReady();
            return;
        }
        __DIRegs[1] = __DIRegs[1];
        block->currTransferSize = (block->length - block->transferredSize > 0x80000) ? 0x80000 : (block->length - block->transferredSize);
        DVDLowRead((char*)block->addr + block->transferredSize, block->currTransferSize, block->offset + block->transferredSize, cbForStateBusy);
        return;
    case 2:
        __DIRegs[1] = __DIRegs[1];
        DVDLowSeek(block->offset, cbForStateBusy);
        return;
    case 3:
        DVDLowStopMotor(cbForStateBusy);
        return;
    case 15:
        DVDLowStopMotor(cbForStateBusy);
        return;
    case 6:
        __DIRegs[1] = __DIRegs[1];
        if (lbl_8066F2D4 != 0) {
            executing->currTransferSize = 0;
            fn_801878AC(0, cbForStateBusy);
            return;
        }
        executing->currTransferSize = 1;
        fn_80187814(0, block->length, block->offset, cbForStateBusy);
        return;
    case 7:
        __DIRegs[1] = __DIRegs[1];
        fn_80187814(0x10000, 0, 0, cbForStateBusy);
        return;
    case 8:
        __DIRegs[1] = __DIRegs[1];
        lbl_8066F2D4 = 1;
        fn_80187814(0, 0, 0, cbForStateBusy);
        return;
    case 9:
        __DIRegs[1] = __DIRegs[1];
        fn_801878AC(0, cbForStateBusy);
        return;
    case 10:
        __DIRegs[1] = __DIRegs[1];
        fn_801878AC(0x10000, cbForStateBusy);
        return;
    case 11:
        __DIRegs[1] = __DIRegs[1];
        fn_801878AC(0x20000, cbForStateBusy);
        return;
    case 12:
        __DIRegs[1] = __DIRegs[1];
        fn_801878AC(0x30000, cbForStateBusy);
        return;
    case 13:
        __DIRegs[1] = __DIRegs[1];
        DVDLowAudioBufferConfig(block->offset, block->length, cbForStateBusy);
        return;
    case 14:
        __DIRegs[1] = __DIRegs[1];
        block->currTransferSize = 0x20;
        fn_80187778(block->addr, cbForStateBusy);
        return;
    default:
        lbl_8066C418(block, cbForStateBusy);
        return;
    }
}

static inline int IsDmaCommand(u32 command)
{
    int i;
    if (command == 1 || command == 4 || command == 5 || command == 14) {
        return 1;
    }
    for (i = 0; i < 1; i++) {
        if (command == lbl_8066C424[i]) {
            return 1;
        }
    }
    return 0;
}

static inline int IsImmCommandWithResult(u32 command)
{
    int i;
    if (command - 9 <= 3) {
        return 1;
    }
    for (i = 0; i < 3; i++) {
        if (command == lbl_804D21F8[i]) {
            return 1;
        }
    }
    return 0;
}

void cbForStateBusy(u32 intType)
{
    DVDCommandBlock* finished;

    if (intType == 16) {
        executing->state = -1;
        __DVDStoreErrorCode(0x1234568);
        DVDReset();
        cbForStateError(0);
        return;
    }

    if (CurrCommand == 3 || CurrCommand == 15) {
        if (intType & 2) {
            executing->state = -1;
            stateError(0x1234567);
            return;
        }
        NumInternalRetry = 0;
        if (CurrCommand == 15) {
            ResetRequired = 1;
        }
        if (!CheckCancel(7)) {
            executing->state = 7;
            DVDLowWaitCoverClose(cbForStateMotorStopped);
        }
        return;
    }

    if (IsDmaCommand(CurrCommand)) {
        executing->transferredSize += executing->currTransferSize - __DIRegs[6];
    }

    if (intType & 8) {
        lbl_8066F2E0 = 0;
        finished = executing;
        executing = &DummyCommandBlock;
        finished->state = 10;
        if (finished->callback) {
            finished->callback(-3, finished);
        }
        if (lbl_8066F2E4) {
            lbl_8066F2E4(0, finished);
        }
        stateReady();
        return;
    }

    if (intType & 1) {
        NumInternalRetry = 0;
        if (CheckCancel(0)) {
            return;
        }
        if (IsDmaCommand(CurrCommand)) {
            if (executing->transferredSize != executing->length) {
                stateBusy(executing);
                return;
            }
            finished = executing;
            executing = &DummyCommandBlock;
            finished->state = 0;
            if (finished->callback) {
                finished->callback(finished->transferredSize, finished);
            }
            stateReady();
            return;
        }
        if (IsImmCommandWithResult(CurrCommand)) {
            s32 result;
            if (CurrCommand == 11 || CurrCommand == 10) {
                result = __DIRegs[8] * 4;
            } else {
                result = __DIRegs[8];
            }
            finished = executing;
            executing = &DummyCommandBlock;
            finished->state = 0;
            if (finished->callback) {
                finished->callback(result, finished);
            }
            stateReady();
            return;
        }
        if (CurrCommand == 6) {
            if (executing->currTransferSize == 0) {
                if (__DIRegs[8] & 1) {
                    finished = executing;
                    executing = &DummyCommandBlock;
                    finished->state = 9;
                    if (finished->callback) {
                        finished->callback(-2, finished);
                    }
                    stateReady();
                    return;
                }
                lbl_8066F2D4 = 0;
                executing->currTransferSize = 1;
                fn_80187814(0, executing->length, executing->offset, cbForStateBusy);
                return;
            }
            finished = executing;
            executing = &DummyCommandBlock;
            finished->state = 0;
            if (finished->callback) {
                finished->callback(0, finished);
            }
            stateReady();
            return;
        }
        finished = executing;
        executing = &DummyCommandBlock;
        finished->state = 0;
        if (finished->callback) {
            finished->callback(0, finished);
        }
        stateReady();
        return;
    }

    if (CurrCommand == 14) {
        executing->state = -1;
        stateError(0x1234567);
        return;
    }
    if ((CurrCommand == 1 || CurrCommand == 4 || CurrCommand == 5 || CurrCommand == 14)
        && executing->transferredSize == executing->length) {
        if (CheckCancel(0)) {
            return;
        }
        finished = executing;
        executing = &DummyCommandBlock;
        finished->state = 0;
        if (finished->callback) {
            finished->callback(finished->transferredSize, finished);
        }
        stateReady();
        return;
    }
    DVDLowRequestError(cbForStateGettingError);
}

extern int autoInvalidation;
extern void DCInvalidateRange(void* addr, u32 nBytes);
extern int OSDisableInterrupts(void);
extern void OSRestoreInterrupts(int level);
extern int __DVDPushWaitingQueue(s32 prio, DVDCommandBlock* block);

static int issueCommand(s32 prio, DVDCommandBlock* block)
{
    int level;
    int result;

    if (autoInvalidation != 0
        && (block->command == 1 || block->command == 4 || block->command == 5 || block->command == 14)) {
        DCInvalidateRange(block->addr, block->length);
    }
    level = OSDisableInterrupts();
    block->state = 2;
    result = __DVDPushWaitingQueue(prio, block);
    if (executing == 0 && PauseFlag == 0) {
        stateReady();
    }
    OSRestoreInterrupts(level);
    return result;
}

int DVDReadAbsAsyncPrio(DVDCommandBlock* block, void* addr, s32 length, s32 offset, void* callback, s32 prio)
{
    int idle;

    block->command = 1;
    block->addr = addr;
    block->length = length;
    block->offset = offset;
    block->transferredSize = 0;
    block->callback = callback;
    idle = issueCommand(prio, block);
    return idle;
}

int DVDSeekAbsAsyncPrio(DVDCommandBlock* block, u32 offset, void* callback, s32 prio)
{
    int idle;

    block->command = 2;
    block->offset = offset;
    block->callback = callback;
    idle = issueCommand(prio, block);
    return idle;
}

int DVDReadAbsAsyncForBS(DVDCommandBlock* block, void* addr, s32 length, s32 offset, void* callback)
{
    int idle;

    block->command = 4;
    block->addr = addr;
    block->length = length;
    block->offset = offset;
    block->transferredSize = 0;
    block->callback = callback;
    idle = issueCommand(2, block);
    return idle;
}

int DVDReadDiskID(DVDCommandBlock* block, void* diskID, void* callback)
{
    int idle;

    block->command = 5;
    block->addr = diskID;
    block->length = 0x20;
    block->offset = 0;
    block->transferredSize = 0;
    block->callback = callback;
    idle = issueCommand(2, block);
    return idle;
}

int DVDCancelStreamAsync(DVDCommandBlock* block, void* callback)
{
    int idle;

    block->command = 7;
    block->callback = callback;
    idle = issueCommand(1, block);
    return idle;
}

int DVDInquiryAsync(DVDCommandBlock* block, void* info, void* callback)
{
    int idle;

    block->command = 14;
    block->addr = info;
    block->length = 0x20;
    block->transferredSize = 0;
    block->callback = callback;
    idle = issueCommand(2, block);
    return idle;
}

void DVDReset(void)
{
    DVDLowReset();
    __DIRegs[0] = 0x2A;
    __DIRegs[1] = __DIRegs[1];
    ResetRequired = 0;
    ResumeFromHere = 0;
}

s32 DVDGetCommandBlockStatus(const DVDCommandBlock* block)
{
    int level;
    s32 result;

    level = OSDisableInterrupts();
    if (block->state == 3) {
        result = 1;
    } else {
        result = block->state;
    }
    OSRestoreInterrupts(level);
    return result;
}
