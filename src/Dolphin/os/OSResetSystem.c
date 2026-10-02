typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned long u32;
typedef signed char s8;
typedef int BOOL;

typedef struct OSSram {
    u16 checkSum;
    u16 checkSumInv;
    u32 ead0;
    u32 ead1;
    u32 counterBias;
    s8 displayOffsetH;
    u8 ntd;
    u8 language;
    u8 flags;
} OSSram;

extern void OSDisableScheduler(void);
extern void OSEnableScheduler(void);
extern void __OSStopAudioSystem(void);
extern BOOL __PADDisableRecalibration(BOOL disable);
extern BOOL CallResetFunctions(BOOL final);
extern BOOL __OSSyncSram(void);
extern OSSram* __OSLockSram(void);
extern void __OSUnlockSram(BOOL commit);
extern BOOL OSDisableInterrupts(void);
extern void LCDisable(void);
extern void KillThreads(void);
extern void ICFlashInvalidate(void);
extern void Reset(u32 resetCode);
extern void OSReport(const char* msg, ...);
extern void __OSReboot(u32 resetCode, u32 bootThisDol);
extern void* memset(void* dst, int val, u32 n);

extern u32 bootThisDol;
volatile u16 __VIRegs[0x100] : 0xCC002000;

#define OSPhysicalToCached(paddr) ((void*)((u32)(paddr) + 0x80000000))

#pragma peephole off
void OSResetSystem(int reset, u32 resetCode, BOOL forceMenu)
{
    BOOL disableRecalibration;
    u32 unused[3];

    OSDisableScheduler();
    if (reset == 1 && forceMenu != 0) {
        OSSram* sram = __OSLockSram();
        sram->flags |= 0x40;
        __OSUnlockSram(1);
        resetCode = 0;
    }
    if (reset == 2 || (reset == 0 && (bootThisDol != 0 || resetCode == 0xC0010000))) {
        __OSStopAudioSystem();
        disableRecalibration = __PADDisableRecalibration(1);
        do {
        } while (CallResetFunctions(0) == 0);
        do {
        } while (__OSSyncSram() == 0);
        OSDisableInterrupts();
        CallResetFunctions(1);
        LCDisable();
        __PADDisableRecalibration(disableRecalibration);
        KillThreads();
    } else {
        __OSStopAudioSystem();
        do {
        } while (CallResetFunctions(0) == 0);
        do {
        } while (__OSSyncSram() == 0);
        OSDisableInterrupts();
        CallResetFunctions(1);
        LCDisable();
        KillThreads();
    }
    if (reset == 1) {
        OSDisableInterrupts();
        __VIRegs[1] = 0;
        ICFlashInvalidate();
        Reset(resetCode * 8);
    } else if (reset == 0) {
        if (forceMenu == 1) {
            OSReport("OSResetSystem(): You can't specify TRUE to forceMenu if you restart. Ignored\n");
        }
        OSEnableScheduler();
        __OSReboot(resetCode, bootThisDol);
    }
    memset(OSPhysicalToCached(0x40), 0, 0xCC - 0x40);
    memset(OSPhysicalToCached(0xD4), 0, 0xE8 - 0xD4);
    memset(OSPhysicalToCached(0xF4), 0, 0xF8 - 0xF4);
    memset(OSPhysicalToCached(0x3000), 0, 0xC0);
    memset(OSPhysicalToCached(0x30C8), 0, 0xD4 - 0xC8);
    memset(OSPhysicalToCached(0x30E2), 0, 1);
}
