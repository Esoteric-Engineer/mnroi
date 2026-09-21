typedef unsigned int u32;
typedef int s32;

typedef struct DVDCommandBlock DVDCommandBlock;
struct DVDCommandBlock
{
    unsigned char pad[0x8];
    u32 command;
    s32 state;
    u32 offset;
    unsigned char pad2[0x14];
    void (*callback)(s32 result, DVDCommandBlock* block);
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
extern u32 tmpBuffer[32];
extern void* LastState;
extern char lbl_8066C41C[6];
extern char lbl_804D2184[];
extern volatile u32 NumInternalRetry;
extern u32 lbl_8066F2F0;
extern DVDCommandBlock* executing;
extern DVDCommandBlock DummyCommandBlock;
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
extern void fn_80184508(void);
extern void fn_80184470(u32 intType);
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
        fn_80184508();
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
        fn_80184508();
        return;
    }

    DVDLowRequestError(fn_80184470);
}
