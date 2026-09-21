typedef unsigned int u32;
typedef int s32;

typedef struct DVDCommandBlock DVDCommandBlock;
struct DVDCommandBlock
{
    unsigned char pad[0xC];
    s32 state;
    unsigned char pad2[0x18];
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
extern u32 NumInternalRetry;
extern DVDCommandBlock* executing;
extern DVDCommandBlock DummyCommandBlock;
extern void stateTimeout(void);
extern void stateGettingError(void);
extern void stateReady(void);

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
