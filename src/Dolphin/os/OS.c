typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned long u32;
typedef long s32;
typedef long long s64;
typedef float f32;
typedef double f64;
typedef int BOOL;
typedef s64 OSTime;

#define NULL 0
#define TRUE 1
#define FALSE 0

#define OSPhysicalToCached(paddr) ((void*)((u32)(paddr) + 0x80000000))

#define OS_CONSOLE_RETAIL      0x00000000
#define OS_CONSOLE_DEVELOPMENT 0x10000000
#define OS_CONSOLE_TDEV        0x20000000
#define OS_CONSOLE_EMULATOR    0x10000000
#define OS_CONSOLE_PC_EMULATOR 0x10000001
#define OS_CONSOLE_ARTHUR      0x10000002
#define OS_CONSOLE_MINNOW      0x10000003

#define OS_RESETCODE_RESTART 0x80000000
#define OSIsRestart() ((OSGetResetCode() & OS_RESETCODE_RESTART) ? TRUE : FALSE)

#define __OS_EXCEPTION_MAX 15
#define OS_DBJUMPPOINT_ADDR 0x60
#define OS_EXCEPTIONTABLE_ADDR 0x3000
#define NOP 0x60000000

typedef struct OSBootInfo {
    u8 diskID[0x20];
    u32 magic;
    u32 version;
    u32 memorySize;
    u32 consoleType;
    void* arenaLo;
    void* arenaHi;
    void* FSTLocation;
    u32 FSTMaxLength;
} OSBootInfo;

typedef struct BI2Debug {
    s32 debugMonSize;
    s32 simMemSize;
    u32 argOffset;
    u32 debugFlag;
    int trackLocation;
    int trackSize;
    u32 countryCode;
    u8 unk[8];
    u32 padSpec;
} BI2Debug;

typedef struct OSExecParams {
    BOOL valid;
    u32 restartCode;
    u32 bootDol;
    void* regionStart;
    void* regionEnd;
    BOOL argsUseDefault;
    void* argsAddr;
} OSExecParams;

typedef struct DVDDriveInfo {
    u16 revisionLevel;
    u16 deviceCode;
    u32 releaseDate;
    u8 padding[24];
} DVDDriveInfo;

typedef struct DVDCommandBlock {
    u8 pad[0xC];
    s32 state;
    u8 pad2[0x20];
} DVDCommandBlock;

typedef u8 __OSException;
typedef void (*__OSExceptionHandler)(__OSException exception, void* context);
typedef void (*DVDCBCallback)(s32 result, DVDCommandBlock* block);

extern OSTime __OSGetSystemTime(void);
extern BOOL OSDisableInterrupts(void);
extern BOOL OSEnableInterrupts(void);
extern void __OSGetExecParams(OSExecParams* params);
extern void PPCMtmmcr0(u32 val);
extern void PPCMtmmcr1(u32 val);
extern void PPCMtpmc1(u32 val);
extern void PPCMtpmc2(u32 val);
extern void PPCMtpmc3(u32 val);
extern void PPCMtpmc4(u32 val);
extern u32 PPCMfhid2(void);
extern void PPCMthid2(u32 val);
extern void PPCDisableSpeculation(void);
extern void PPCSetFpNonIEEEMode(void);
extern void ICFlashInvalidate(void);
extern void* OSGetArenaLo(void);
extern void* OSGetArenaHi(void);
extern void OSSetArenaLo(void* addr);
extern void OSSetArenaHi(void* addr);
extern void __OSInitSystemCall(void);
extern void OSInitAlarm(void);
extern void __OSModuleInit(void);
extern void __OSInterruptInit(void);
extern void* __OSSetInterruptHandler(short interrupt, void* handler);
extern void __OSResetSWInterruptHandler(short exception, void* context);
extern void __OSContextInit(void);
extern void __OSCacheInit(void);
extern void EXIInit(void);
extern void SIInit(void);
extern void __OSInitSram(void);
extern void __OSThreadInit(void);
extern void __OSInitAudioSystem(void);
extern void __OSInitMemoryProtection(void);
extern void OSReport(const char* msg, ...);
extern void EnableMetroTRKInterrupts(void);
extern u32 OSGetResetCode(void);
extern void* memset(void* dst, int c, u32 n);
extern void* memcpy(void* dst, const void* src, u32 n);
extern void DVDInit(void);
extern void DCInvalidateRange(void* addr, u32 nBytes);
extern void DCFlushRangeNoSync(void* addr, u32 nBytes);
extern void ICInvalidateRange(void* addr, u32 nBytes);
extern BOOL DVDInquiryAsync(DVDCommandBlock* block, DVDDriveInfo* info, DVDCBCallback callback);
extern void DBPrintf(char* format, ...);
extern BOOL __DBIsExceptionMarked(__OSException exception);
extern void __OSUnhandledException(void);

extern u32 __DVDLongFileNameFlag;
extern u32 __PADSpec;

volatile u32 __DIRegs[0x10] : 0xCC006000;

extern u8 __ArenaLo[];
extern u8 __ArenaHi[];
extern char _stack_addr[];

void __OSEVStart(void);
void __OSEVEnd(void);
void __OSEVSetNumber(void);
void __DBVECTOR(void);
void __OSDBINTSTART(void);
void __OSDBINTEND(void);
void __OSDBJUMPSTART(void);
void __OSDBJUMPEND(void);

void OSExceptionInit(void);
__OSExceptionHandler __OSSetExceptionHandler(__OSException exception, __OSExceptionHandler handler);
void OSDefaultExceptionHandler(__OSException exception, void* context);
void OSRegisterVersion(const char* id);

const char* __OSVersion = "<< Dolphin SDK - OS\trelease build: Nov 10 2004 06:26:41 (0x2301) >>";

static OSBootInfo* BootInfo = NULL;
volatile u32* BI2DebugFlag = NULL;
static u32 BI2DebugFlagHolder = 0;
BOOL __OSIsGcam = FALSE;
static f64 ZeroF = 0;
static f32 ZeroPS[2];
static BOOL AreWeInitialized = FALSE;
static __OSExceptionHandler* OSExceptionTable = NULL;
BOOL __OSInIPL = FALSE;
OSTime __OSStartTime = 0;

static DVDDriveInfo DriveInfo __attribute__((aligned(32)));
static DVDCommandBlock DriveBlock;
OSExecParams __OSRebootParams;

asm void __OSInitFPRs(void)
{
    // clang-format off
    nofralloc
    mfmsr   r3
    ori     r3, r3, 8192
    mtmsr   r3
    mfspr   r3, 920
    rlwinm. r3, r3, 3, 31, 31
    beq     scalar_init
    lis     r3, ZeroPS@ha
    addi    r3, r3, ZeroPS@l
    psq_l   f0, 0(r3), 0, 0
    ps_mr   f1, f0
    ps_mr   f2, f0
    ps_mr   f3, f0
    ps_mr   f4, f0
    ps_mr   f5, f0
    ps_mr   f6, f0
    ps_mr   f7, f0
    ps_mr   f8, f0
    ps_mr   f9, f0
    ps_mr   f10, f0
    ps_mr   f11, f0
    ps_mr   f12, f0
    ps_mr   f13, f0
    ps_mr   f14, f0
    ps_mr   f15, f0
    ps_mr   f16, f0
    ps_mr   f17, f0
    ps_mr   f18, f0
    ps_mr   f19, f0
    ps_mr   f20, f0
    ps_mr   f21, f0
    ps_mr   f22, f0
    ps_mr   f23, f0
    ps_mr   f24, f0
    ps_mr   f25, f0
    ps_mr   f26, f0
    ps_mr   f27, f0
    ps_mr   f28, f0
    ps_mr   f29, f0
    ps_mr   f30, f0
    ps_mr   f31, f0
scalar_init:
    lfd     f0, ZeroF
    fmr     f1, f0
    fmr     f2, f0
    fmr     f3, f0
    fmr     f4, f0
    fmr     f5, f0
    fmr     f6, f0
    fmr     f7, f0
    fmr     f8, f0
    fmr     f9, f0
    fmr     f10, f0
    fmr     f11, f0
    fmr     f12, f0
    fmr     f13, f0
    fmr     f14, f0
    fmr     f15, f0
    fmr     f16, f0
    fmr     f17, f0
    fmr     f18, f0
    fmr     f19, f0
    fmr     f20, f0
    fmr     f21, f0
    fmr     f22, f0
    fmr     f23, f0
    fmr     f24, f0
    fmr     f25, f0
    fmr     f26, f0
    fmr     f27, f0
    fmr     f28, f0
    fmr     f29, f0
    fmr     f30, f0
    fmr     f31, f0
    mtfsf   255, f0
    blr
    // clang-format on
}

u32 OSGetConsoleType(void)
{
    if (BootInfo == NULL || BootInfo->consoleType == 0) {
        return OS_CONSOLE_ARTHUR;
    }
    return BootInfo->consoleType;
}

static inline void ClearArena(void)
{
    if (!OSIsRestart()) {
        memset(OSGetArenaLo(), 0, (u32)OSGetArenaHi() - (u32)OSGetArenaLo());
        return;
    }

    if (__OSRebootParams.regionStart == NULL) {
        memset(OSGetArenaLo(), 0, (u32)OSGetArenaHi() - (u32)OSGetArenaLo());
        return;
    }

    if ((u32)OSGetArenaLo() < (u32)__OSRebootParams.regionStart) {
        if ((u32)OSGetArenaHi() <= (u32)__OSRebootParams.regionStart) {
            memset(OSGetArenaLo(), 0, (u32)OSGetArenaHi() - (u32)OSGetArenaLo());
            return;
        }

        memset(OSGetArenaLo(), 0, (u32)__OSRebootParams.regionStart - (u32)OSGetArenaLo());

        if ((u32)OSGetArenaHi() > (u32)__OSRebootParams.regionEnd) {
            memset(__OSRebootParams.regionEnd, 0, (u32)OSGetArenaHi() - (u32)__OSRebootParams.regionEnd);
        }
    }
}

static void InquiryCallback(s32 result, DVDCommandBlock* block)
{
    switch (block->state) {
    case 0:
        *(u16*)0x800030E6 = DriveInfo.deviceCode | 0x8000;
        break;
    default:
        *(u16*)0x800030E6 = 1;
        break;
    }
}

void OSInit(void)
{
    BI2Debug* DebugInfo;
    s32 consoleType;
    u32 tdev;

    if (AreWeInitialized == FALSE) {
        AreWeInitialized = TRUE;

        __OSStartTime = __OSGetSystemTime();
        OSDisableInterrupts();

        __OSGetExecParams(&__OSRebootParams);
        PPCMtmmcr0(0);
        PPCMtmmcr1(0);
        PPCMtpmc1(0);
        PPCMtpmc2(0);
        PPCMtpmc3(0);
        PPCMtpmc4(0);
        PPCDisableSpeculation();
        PPCSetFpNonIEEEMode();

        BI2DebugFlag = NULL;
        BootInfo = (OSBootInfo*)OSPhysicalToCached(0x0000);
        __DVDLongFileNameFlag = 0;

        DebugInfo = *(BI2Debug**)OSPhysicalToCached(0x00F4);
        if (DebugInfo != NULL) {
            BI2DebugFlag = &DebugInfo->debugFlag;
            __PADSpec = DebugInfo->padSpec;
            *(u8*)OSPhysicalToCached(0x30E8) = (u8)*BI2DebugFlag;
            *(u8*)OSPhysicalToCached(0x30E9) = (u8)__PADSpec;
        } else if (BootInfo->arenaHi) {
            BI2DebugFlagHolder = (u32)*(u8*)OSPhysicalToCached(0x30E8);
            BI2DebugFlag = &BI2DebugFlagHolder;
            __PADSpec = (u32)*(u8*)OSPhysicalToCached(0x30E9);
        }

        __DVDLongFileNameFlag = 1;

        OSSetArenaLo((BootInfo->arenaLo == NULL) ? __ArenaLo : BootInfo->arenaLo);

        if ((BootInfo->arenaLo == NULL) && (BI2DebugFlag != NULL) && (*BI2DebugFlag < 2)) {
            OSSetArenaLo((void*)(((u32)_stack_addr + 0x1F) & ~0x1F));
        }

        OSSetArenaHi((BootInfo->arenaHi == NULL) ? __ArenaHi : BootInfo->arenaHi);

        OSExceptionInit();
        __OSInitSystemCall();
        OSInitAlarm();
        __OSModuleInit();
        __OSInterruptInit();
        __OSSetInterruptHandler(0x16, __OSResetSWInterruptHandler);
        __OSContextInit();
        __OSCacheInit();
        EXIInit();
        SIInit();
        __OSInitSram();
        __OSThreadInit();
        __OSInitAudioSystem();
        PPCMthid2(PPCMfhid2() & ~0x40000000);

        if (!__OSInIPL) {
            __OSInitMemoryProtection();
        }

        OSReport("\nDolphin OS\n");
        OSReport("Kernel built : %s %s\n", "Nov 10 2004", "06:26:41");
        OSReport("Console Type : ");

        consoleType = OSGetConsoleType();
        switch (consoleType & 0xF0000000) {
        case OS_CONSOLE_RETAIL:
            OSReport("Retail %d\n", consoleType);
            break;
        case OS_CONSOLE_DEVELOPMENT:
        case OS_CONSOLE_TDEV:
            switch (consoleType & 0x0FFFFFFF) {
            case OS_CONSOLE_EMULATOR:
                OSReport("Mac Emulator\n");
                break;
            case OS_CONSOLE_PC_EMULATOR:
                OSReport("PC Emulator\n");
                break;
            case OS_CONSOLE_ARTHUR:
                OSReport("EPPC Arthur\n");
                break;
            case OS_CONSOLE_MINNOW:
                OSReport("EPPC Minnow\n");
                break;
            default:
                tdev = (u32)consoleType & 0x0FFFFFFF;
                OSReport("Development HW%d (%08x)\n", tdev - 3, consoleType);
                break;
            }
            break;
        default:
            OSReport("%08x\n", consoleType);
            break;
        }

        OSReport("Memory %d MB\n", BootInfo->memorySize >> 20);
        OSReport("Arena : 0x%x - 0x%x\n", OSGetArenaLo(), OSGetArenaHi());
        OSRegisterVersion(__OSVersion);

        if (BI2DebugFlag && *BI2DebugFlag >= 2) {
            EnableMetroTRKInterrupts();
        }

        ClearArena();
        OSEnableInterrupts();

        if (!__OSInIPL) {
            DVDInit();

            if (__OSIsGcam) {
                *(u16*)0x800030E6 = 0x9000;
                return;
            }

            DCInvalidateRange(&DriveInfo, sizeof(DriveInfo));
            DVDInquiryAsync(&DriveBlock, &DriveInfo, InquiryCallback);
        }
    }
}

static u32 __OSExceptionLocations[] = {
    0x00000100, 0x00000200, 0x00000300, 0x00000400, 0x00000500,
    0x00000600, 0x00000700, 0x00000800, 0x00000900, 0x00000C00,
    0x00000D00, 0x00000F00, 0x00001300, 0x00001400, 0x00001700,
};

void OSExceptionInit(void)
{
    __OSException exception;
    void* destAddr;
    u32* opCodeAddr;
    u32 oldOpCode;
    u8* handlerStart;
    u32 handlerSize;

    opCodeAddr = (u32*)__OSEVSetNumber;
    oldOpCode = *opCodeAddr;
    handlerStart = (u8*)__OSEVStart;
    handlerSize = (u32)((u8*)__OSEVEnd - (u8*)__OSEVStart);

    destAddr = OSPhysicalToCached(OS_DBJUMPPOINT_ADDR);
    if (*(u32*)destAddr == 0) {
        DBPrintf("Installing OSDBIntegrator\n");
        memcpy(destAddr, (void*)__OSDBINTSTART, (u32)__OSDBINTEND - (u32)__OSDBINTSTART);
        DCFlushRangeNoSync(destAddr, (u32)__OSDBINTEND - (u32)__OSDBINTSTART);
        __sync();
        ICInvalidateRange(destAddr, (u32)__OSDBINTEND - (u32)__OSDBINTSTART);
    }

    for (exception = 0; exception < __OS_EXCEPTION_MAX; exception++) {
        if (BI2DebugFlag && (*BI2DebugFlag >= 2) && __DBIsExceptionMarked(exception)) {
            DBPrintf(">>> OSINIT: exception %d commandeered by TRK\n", exception);
            continue;
        }

        *opCodeAddr = oldOpCode | exception;

        if (__DBIsExceptionMarked(exception)) {
            DBPrintf(">>> OSINIT: exception %d vectored to debugger\n", exception);
            memcpy((void*)__DBVECTOR, (void*)__OSDBJUMPSTART, (u32)__OSDBJUMPEND - (u32)__OSDBJUMPSTART);
        } else {
            u32* ops = (u32*)__DBVECTOR;
            int cb;

            for (cb = 0; cb < (u32)__OSDBJUMPEND - (u32)__OSDBJUMPSTART; cb += sizeof(u32)) {
                *ops++ = NOP;
            }
        }

        destAddr = OSPhysicalToCached(__OSExceptionLocations[(u32)exception]);
        memcpy(destAddr, handlerStart, handlerSize);
        DCFlushRangeNoSync(destAddr, handlerSize);
        __sync();
        ICInvalidateRange(destAddr, handlerSize);
    }

    OSExceptionTable = OSPhysicalToCached(OS_EXCEPTIONTABLE_ADDR);

    for (exception = 0; exception < __OS_EXCEPTION_MAX; exception++) {
        __OSSetExceptionHandler(exception, OSDefaultExceptionHandler);
    }

    *opCodeAddr = oldOpCode;

    DBPrintf("Exceptions initialized...\n");
}

asm void __OSDBIntegrator(void)
{
    // clang-format off
    nofralloc
entry __OSDBINTSTART
    li      r5, 0x40
    mflr    r3
    stw     r3, 0xc(r5)
    lwz     r3, 0x8(r5)
    oris    r3, r3, 0x8000
    mtlr    r3
    li      r3, 0x30
    mtmsr   r3
    blr
entry __OSDBINTEND
    // clang-format on
}

asm void __OSDBJump(void)
{
    // clang-format off
    nofralloc
entry __OSDBJUMPSTART
    bla     0x60
entry __OSDBJUMPEND
    // clang-format on
}

__OSExceptionHandler __OSSetExceptionHandler(__OSException exception, __OSExceptionHandler handler)
{
    __OSExceptionHandler oldHandler;

    oldHandler = OSExceptionTable[exception];
    OSExceptionTable[exception] = handler;
    return oldHandler;
}

__OSExceptionHandler __OSGetExceptionHandler(__OSException exception)
{
    return OSExceptionTable[exception];
}

asm void OSExceptionVector(void)
{
    // clang-format off
    nofralloc
entry __OSEVStart
    mtsprg  0, r4
    lwz     r4, 0xc0(r0)
    stw     r3, 0xc(r4)
    mfsprg  r3, 0
    stw     r3, 0x10(r4)
    stw     r5, 0x14(r4)
    lhz     r3, 0x1a2(r4)
    ori     r3, r3, 2
    sth     r3, 0x1a2(r4)
    mfcr    r3
    stw     r3, 0x80(r4)
    mflr    r3
    stw     r3, 0x84(r4)
    mfctr   r3
    stw     r3, 0x88(r4)
    mfxer   r3
    stw     r3, 0x8c(r4)
    mfsrr0  r3
    stw     r3, 0x198(r4)
    mfsrr1  r3
    stw     r3, 0x19c(r4)
    mr      r5, r3
entry __DBVECTOR
    nop
    mfmsr   r3
    ori     r3, r3, 0x30
    mtsrr1  r3
entry __OSEVSetNumber
    li      r3, 0
    lwz     r4, 0xd4(r0)
    rlwinm. r5, r5, 0, 30, 30
    bne     recoverable
    lis     r5, OSDefaultExceptionHandler@ha
    addi    r5, r5, OSDefaultExceptionHandler@l
    mtsrr0  r5
    rfi
recoverable:
    rlwinm  r5, r3, 2, 22, 29
    lwz     r5, 0x3000(r5)
    mtsrr0  r5
    rfi
entry __OSEVEnd
    nop
    // clang-format on
}

asm void OSDefaultExceptionHandler(__OSException exception, void* context)
{
    // clang-format off
    nofralloc
    stw     r0, 0(r4)
    stw     r1, 4(r4)
    stw     r2, 8(r4)
    stmw    r6, 0x18(r4)
    mfspr   r0, GQR1
    stw     r0, 0x1a8(r4)
    mfspr   r0, GQR2
    stw     r0, 0x1ac(r4)
    mfspr   r0, GQR3
    stw     r0, 0x1b0(r4)
    mfspr   r0, GQR4
    stw     r0, 0x1b4(r4)
    mfspr   r0, GQR5
    stw     r0, 0x1b8(r4)
    mfspr   r0, GQR6
    stw     r0, 0x1bc(r4)
    mfspr   r0, GQR7
    stw     r0, 0x1c0(r4)
    mfdsisr r5
    mfdar   r6
    stwu    r1, -8(r1)
    b       __OSUnhandledException
    // clang-format on
}

void __OSPSInit(void)
{
    PPCMthid2(PPCMfhid2() | 0x80000000 | 0x20000000);
    ICFlashInvalidate();
    asm {
        sync
        li r3, 0
        mtspr GQR0, r3
        mtspr GQR1, r3
        mtspr GQR2, r3
        mtspr GQR3, r3
        mtspr GQR4, r3
        mtspr GQR5, r3
        mtspr GQR6, r3
        mtspr GQR7, r3
    }
}

u32 __OSGetDIConfig(void)
{
    return __DIRegs[9] & 0xFF;
}

void OSRegisterVersion(const char* id)
{
    OSReport("%s\n", id);
}
