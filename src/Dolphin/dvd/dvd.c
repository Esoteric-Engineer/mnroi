typedef unsigned int u32;
typedef int s32;

typedef struct DVDCommandBlock DVDCommandBlock;
struct DVDCommandBlock
{
    unsigned char pad[0x8];
    u32 command;
    s32 state;
    u32 offset;
    unsigned char pad2[0x10];
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
extern char lbl_804D2184[];
extern volatile u32 NumInternalRetry;
extern u32 lbl_8066F2F0;
extern DVDCommandBlock* executing;
void stateTimeout(void);
void stateGettingError(void);
extern void stateReady(void);
extern void fn_80186A50(void);
extern void __DVDStoreErrorCode(u32 error);
extern void DVDReset(void);
extern void DVDLowRequestError(void* callback);
void cbForStateGettingError(u32 intType);
extern volatile u32 ResumeFromHere;
extern void DVDLowStopMotor(void* callback);
extern void DVDLowSeek(u32 offset, void* callback);
void stateGoToRetry(void);
void cbForStateGoToRetry(u32 intType);
extern volatile u32 CurrCommand;
extern int ResetRequired;
void cbForUnrecoveredErrorRetry(u32 intType);
extern void fn_80184D20(void);
extern void fn_80184BB4(void);
extern void cbForUnrecoveredError(u32 intType);
void cbForStateError(u32 intType);
extern int FatalErrorFlag;
extern volatile u32 lbl_8066F2E0;
extern void (*lbl_8066F2E4)(s32 result, DVDCommandBlock* block);

extern void fn_8017CBFC(const char* file, int line, const char* msg, ...);
extern void DVDLowRead(void* addr, u32 length, u32 offset, void* callback);
void cbForStateReadingFST(u32 intType);

extern int fn_80186958(void* id1, void* id2);
extern void* memcpy(void* dst, const void* src, u32 n);
extern int fn_801721F8(const void* a, const void* b, u32 n);
extern void DCInvalidateRange(void* addr, u32 nBytes);
extern void DVDLowAudioBufferConfig(u32 enable, u32 size, void* callback);
extern void fn_80184A74(u32 intType);
void cbForStateCheckID2a(u32 intType);
extern void fn_80184844(DVDCommandBlock* block);
void stateCheckID2(DVDCommandBlock* block);
void stateCheckID3(DVDCommandBlock* block);
extern void fn_8018487C(u32 intType);

extern void OSRegisterVersion(const char* version);
extern void __DVDFSInit(void);
extern void __DVDClearWaitingQueue(void);
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
        fn_8017CBFC(lbl_8066C41C, 0x28A, lbl_804D2184);
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
    fn_80186A50();
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
        fn_80184D20();
    } else if (status == 0x02000000) {
        executing->state = 3;
        fn_80184BB4();
    } else if (status == 0x03000000) {
        executing->state = 4;
        fn_80184D20();
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
        fn_80184D20();
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
            DVDLowStopMotor(fn_8018487C);
        }
        break;
    default:
        if (fn_801721F8(lbl_8057D240, IDShouldBe, 0x20)) {
            DVDLowStopMotor(fn_8018487C);
        } else {
            LastState = stateCheckID3;
            stateCheckID3(executing);
        }
        break;
    }
}

void stateCheckID3(DVDCommandBlock* block)
{
    DVDLowAudioBufferConfig(((unsigned char*)IDShouldBe)[8], 10, fn_80184A74);
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
        fn_80184844(executing);
    } else {
        DVDLowRequestError(cbForStateGettingError);
    }
}
