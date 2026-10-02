#pragma inline_depth(3)
#pragma peephole off
typedef signed long s32;
typedef unsigned long u32;
typedef unsigned char u8;
typedef struct DVDCommandBlock DVDCommandBlock;

typedef struct OSExecParams {
    u32 valid;
    u32 restartCode;
    u32 bootDol;
    void* regionStart;
    void* regionEnd;
    s32 argsUseDefault;
    void* argsAddr;
} OSExecParams;

typedef struct ApploaderHeader {
    char date[16];
    void (*entry)(void (**)(void (*)(const char*, ...)), s32 (**)(void**, u32*, s32*), void* (**)(void));
    u32 size;
    u32 rebootSize;
    u32 reserved2;
} ApploaderHeader;

typedef struct DVDDiskID {
    char gameName[4];
    char company[2];
    u8 diskNumber;
    u8 gameVersion;
    u8 streaming;
    u8 streamingBufSize;
} DVDDiskID;

extern s32 OSDisableInterrupts(void);
extern s32 OSEnableInterrupts(void);
extern void* OSAllocFromArenaLo(u32 size, u32 align);
extern void OSSetArenaLo(void* addr);
extern void OSReport(const char* msg, ...);
extern void* memcpy(void* dst, const void* src, u32 n);
extern s32 strncmp(const char* a, const char* b, u32 n);
extern void ICInvalidateRange(void* addr, u32 nBytes);
extern void ICFlashInvalidate(void);
extern void DVDInit(void);
extern void DVDSetAutoInvalidation(s32 autoInval);
extern void DVDResume(void);
extern void __DVDPrepareResetAsync(void (*callback)(void));
extern DVDDiskID* DVDGetCurrentDiskID(void);
extern s32 DVDCheckDisk(void);
extern s32 DVDCancelStreamAsync(DVDCommandBlock* block, void* callback);
extern s32 DVDReadAbsAsyncPrio(DVDCommandBlock* block, void* addr, s32 length, s32 offset, void* callback, s32 prio);
extern s32 DVDGetCommandBlockStatus(DVDCommandBlock* block);
extern void AISetStreamVolLeft(u32 vol);
extern void AISetStreamVolRight(u32 vol);
extern void AISetStreamPlayState(u32 state);
extern void __OSMaskInterrupts(u32 mask);
extern void __OSUnmaskInterrupts(u32 mask);
extern void __OSDoHotReset(s32 resetCode);
extern void __OSSetAlarmState(void);
extern s32 PackArgs(void* addr, s32 argc, char** argv);
extern void ReadDiscBlocking(void* addr, s32 length, s32 offset);
extern s32 fn_8017D4A4(void);
extern void fn_8017D3B0(void* addr);
extern s32 __OSIsGcam;
extern s32 lbl_8066F218;
extern s32 lbl_8066F21C;
volatile u32 __PIRegs[0x20] : 0xCC003000;
void* __OSExecParamsPtr : 0x800030F0;

static inline s32 IsStreaming(void)
{
    return DVDGetCurrentDiskID()->streaming ? 1 : 0;
}

static inline s32 IsNewApploader(ApploaderHeader* header)
{
    return strncmp(header->date, "2004/02/01", 10) > 0 ? 1 : 0;
}

static inline void ReadDisc(void* addr, s32 length, s32 offset)
{
    u8 block[0x30];

    DVDReadAbsAsyncPrio((DVDCommandBlock*)block, addr, length, offset, 0, 0);
    while (DVDGetCommandBlockStatus((DVDCommandBlock*)block)) {
        if (!DVDCheckDisk()) {
            __OSDoHotReset(0);
        }
    }
}

/* unused locals below only reproduce the original's stack slots */
static inline void ReadChunkBody(void* addr, s32 length, s32 offset)
{
    void* p = addr;
    void* q = addr;
    u8 block[0x30];

    DVDReadAbsAsyncPrio((DVDCommandBlock*)block, addr, length, offset, 0, 0);
    while (DVDGetCommandBlockStatus((DVDCommandBlock*)block)) {
        if (!DVDCheckDisk()) {
            __OSDoHotReset(0);
        }
    }
    (void)p;
    (void)q;
}

static inline void ReadChunk(void* a, s32 l, s32 o)
{
    ReadChunkBody(a, l, o);
}

static inline void ReadRebootCode(void* addr, s32 length, s32 offset)
{
    u8 block[0x30];
    void* p = addr;

    DVDReadAbsAsyncPrio((DVDCommandBlock*)block, addr, length, offset, 0, 0);
    while (DVDGetCommandBlockStatus((DVDCommandBlock*)block)) {
        if (!DVDCheckDisk()) {
            __OSDoHotReset(0);
        }
    }
    (void)p;
}

static inline s32 GetApploaderPositionI(void)
{
    u8* buf;

    if (lbl_8066F21C != 0) {
        return lbl_8066F21C;
    }
    if (*(s32*)0x800030F4 != 0) {
        buf = (u8*)OSAllocFromArenaLo(0x40, 0x20);
        ReadDisc(buf, 0x40, *(s32*)0x800030F4);
        lbl_8066F21C = *(u32*)0x800030F4 + *(u32*)(buf + 0x38);
    } else {
        lbl_8066F21C = 0x2440;
    }
    return lbl_8066F21C;
}

void __OSBootDolSimple(u32 doloffset, u32 restartCode, void* regionStart, void* regionEnd, s32 argsUseDefault, s32 argc, char** argv)
{
    u8 dvdCmd[0x30];
    u32 unused;
    OSExecParams* params;
    OSExecParams* image;
    ApploaderHeader* header;
    s32 offset;
    u32 length;
    void* addr;
    void* (*appClose)(void);
    s32 (*appMain)(void**, u32*, s32*);
    void (*appInit)(void (*)(const char*, ...));
    void* entry;

    OSDisableInterrupts();

    params = (OSExecParams*)OSAllocFromArenaLo(sizeof(OSExecParams), 1);
    params->valid = 1;
    params->restartCode = restartCode;
    params->regionStart = regionStart;
    params->regionEnd = regionEnd;
    params->argsUseDefault = argsUseDefault;
    if (argsUseDefault == 0) {
        params->argsAddr = OSAllocFromArenaLo(0x2000, 1);
        PackArgs(params->argsAddr, argc, argv);
    }

    DVDInit();
    DVDSetAutoInvalidation(1);
    DVDResume();
    lbl_8066F218 = 0;
    __DVDPrepareResetAsync(__OSSetAlarmState);
    __OSMaskInterrupts(0xFFFFFFE0);
    __OSUnmaskInterrupts(0x400);
    OSEnableInterrupts();

    while (lbl_8066F218 != 1) {
        if (!DVDCheckDisk()) {
            __OSDoHotReset(0);
        }
    }

    if (__OSIsGcam == 0 && IsStreaming()) {
        AISetStreamVolLeft(0);
        AISetStreamVolRight(0);
        DVDCancelStreamAsync((DVDCommandBlock*)dvdCmd, 0);
        while (DVDGetCommandBlockStatus((DVDCommandBlock*)dvdCmd)) {
            if (!DVDCheckDisk()) {
                __OSDoHotReset(0);
            }
        }
        AISetStreamPlayState(0);
    }

    header = (ApploaderHeader*)OSAllocFromArenaLo(0x20, 0x20);
    ReadDiscBlocking(header, 0x20, fn_8017D4A4());
    ReadDiscBlocking((void*)0x81200000, (header->size + 0x1F) & ~0x1F, fn_8017D4A4() + 0x20);
    ICInvalidateRange((void*)0x81200000, (header->size + 0x1F) & ~0x1F);

    if (IsNewApploader(header)) {
        if (doloffset == -1) {
            doloffset = GetApploaderPositionI() + 0x20 + header->size;
        }
        params->bootDol = doloffset;
        header->entry(&appInit, &appMain, &appClose);

        image = (OSExecParams*)OSAllocFromArenaLo(sizeof(OSExecParams), 1);
        memcpy(image, params, sizeof(OSExecParams));
        __OSExecParamsPtr = image;
        appInit(OSReport);
        OSSetArenaLo(image);

        while (appMain(&addr, &length, &offset)) {
            ReadChunk(addr, length, offset);
        }
        entry = appClose();

        image = (OSExecParams*)OSAllocFromArenaLo(sizeof(OSExecParams), 1);
        memcpy(image, params, sizeof(OSExecParams));
        __OSExecParamsPtr = image;
        __PIRegs[9] = 7;
        OSDisableInterrupts();
        fn_8017D3B0(entry);
    } else {
        *(void**)0x812FDFF0 = regionStart;
        *(void**)0x812FDFEC = regionEnd;
        *(u8*)0x800030E2 = 1;
        ReadRebootCode((void*)0x81300000, (header->rebootSize + 0x1F) & ~0x1F, fn_8017D4A4() + 0x20 + header->size);
        ICInvalidateRange((void*)0x81300000, (header->rebootSize + 0x1F) & ~0x1F);
        OSDisableInterrupts();
        ICFlashInvalidate();
        fn_8017D3B0((void*)0x81300000);
    }
}
