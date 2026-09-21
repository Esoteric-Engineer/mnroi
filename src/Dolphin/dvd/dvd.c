typedef unsigned int u32;
typedef int s32;

typedef struct OSBootInfo
{
    unsigned char pad[0x20];
    u32 magic;
} OSBootInfo;

extern int DVDInitialized;
extern int FirstTimeInBootrom;
extern OSBootInfo* bootInfo;
extern void* IDShouldBe;
extern u32 __DVDThreadQueue[2];
extern char* __DVDVersion;

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
