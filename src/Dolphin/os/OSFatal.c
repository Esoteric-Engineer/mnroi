typedef unsigned char u8;
typedef unsigned long u32;
typedef long s32;
typedef long long s64;
typedef int BOOL;

typedef struct GXColor {
    u8 r, g, b, a;
} GXColor;

struct FatalParam {
    GXColor fg;
    GXColor bg;
    char* msg;
    u32 pad;
    long long context[0x2C8 / 8];
} FatalParam;

u32 __OSBusClock : 0x800000F8;
typedef struct OSBootInfo {
    u8 pad[0x38];
    void* fstLocation;
} OSBootInfo;
#define OSMillisecondsToTicks(msec) ((s64)((__OSBusClock / 4) / 1000 * (msec)))

extern BOOL OSDisableInterrupts(void);
extern BOOL OSEnableInterrupts(void);
extern void OSDisableScheduler(void);
extern void OSClearContext(void* context);
extern void* OSSetCurrentContext(void* context);
extern void __OSStopAudioSystem(void);
extern void AISetStreamVolLeft(u32 vol);
extern void AISetStreamVolRight(u32 vol);
extern void VIInit(void);
extern u32 __OSUnmaskInterrupts(u32 mask);
extern void VISetBlack(BOOL black);
extern void VIFlush(void);
extern void DVDLowSetCoverCallback(void* cb);
extern void DVDLowSetResetCoverCallback(void* cb);
extern s32 VIGetRetraceCount(void);
extern s64 OSGetTime(void);
extern BOOL CallResetFunctions(BOOL final);
extern void* EXISetExiCallback(s32 chan, void* callback);
extern BOOL EXISync(s32 chan);
extern BOOL EXIDeselect(s32 chan);
extern BOOL EXIUnlock(s32 chan);
extern BOOL EXILock(s32 chan, u32 dev, void* unlockedCallback);
extern void __OSSetExceptionHandler(u8 exception, void* handler);
extern void OSDefaultExceptionHandler(void);
extern void GXAbortFrame(void);
extern void OSSetArenaLo(void* lo);
extern void OSSetArenaHi(void* hi);
extern void* OSGetArenaHi(void);
extern void OSSwitchStack(void* pc, void* newsp);
extern void Halt(void);

volatile u32 __EXIRegs[0x40] : 0xCC006800;

void OSFatal(GXColor fg, GXColor bg, const char* msg)
{
    struct FatalParam* b = &FatalParam;
    OSBootInfo* bootInfo = (OSBootInfo*)0x80000000;
    s32 retraceCount;
    s64 start;

    OSDisableInterrupts();
    OSDisableScheduler();
    OSClearContext(&b->context);
    OSSetCurrentContext(&b->context);
    __OSStopAudioSystem();
    AISetStreamVolLeft(0);
    AISetStreamVolRight(0);
    VIInit();
    __OSUnmaskInterrupts(0x80);
    VISetBlack(1);
    VIFlush();
    DVDLowSetCoverCallback(0);
    DVDLowSetResetCoverCallback(0);
    OSEnableInterrupts();
    retraceCount = VIGetRetraceCount();
    while ((VIGetRetraceCount() - retraceCount) < 1)
        ;
    start = OSGetTime();
    do {
        if (CallResetFunctions(0) != 0)
            break;
    } while ((OSGetTime() - start) < OSMillisecondsToTicks(1000));
    OSDisableInterrupts();
    CallResetFunctions(1);
    EXISetExiCallback(0, 0);
    EXISetExiCallback(2, 0);
    while (!EXILock(0, 1, 0)) {
        EXISync(0);
        EXIDeselect(0);
        EXIUnlock(0);
    }
    EXIUnlock(0);
    while ((__EXIRegs[3] & 1) == 1)
        ;
    __OSSetExceptionHandler(8, OSDefaultExceptionHandler);
    GXAbortFrame();
    OSSetArenaLo((void*)0x81400000);
    OSSetArenaHi(bootInfo->fstLocation);
    b->fg = fg;
    b->bg = bg;
    b->msg = (char*)msg;
    OSSwitchStack(Halt, OSGetArenaHi());
}
