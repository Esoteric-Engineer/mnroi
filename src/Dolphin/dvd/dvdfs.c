typedef unsigned int u32;
typedef int s32;

typedef struct OSBootInfo
{
    unsigned char pad[0x38];
    void* FSTLocation;
} OSBootInfo;

typedef struct FSTEntry
{
    u32 isDirAndStringOff;
    u32 parentOrPosition;
    u32 nextEntryOrLength;
} FSTEntry;

typedef struct DVDCommandBlock
{
    unsigned char pad0[0xC];
    s32 state;
    unsigned char pad1[0x10];
    u32 transferredSize;
    unsigned char pad2[0xC];
} DVDCommandBlock;

typedef struct DVDDir
{
    u32 entryNum;
    u32 location;
    u32 next;
} DVDDir;

typedef struct DVDFileInfo
{
    DVDCommandBlock cb; // 0x00, size 0x30
    u32 startAddr;       // 0x30
    u32 length;           // 0x34
    void* callback;       // 0x38
} DVDFileInfo;

#define entryIsDir(i) (((FstStart[i].isDirAndStringOff & 0xff000000) == 0) ? 0 : 1)
#define filePosition(i) (FstStart[i].parentOrPosition)
#define fileLength(i) (FstStart[i].nextEntryOrLength)

extern OSBootInfo* BootInfo;
extern FSTEntry* FstStart;
extern char* FstStringStart;
extern u32 MaxEntryNum;
extern u32 currentDirectory;
extern u32 __DVDLongFileNameFlag;
extern char lbl_8066C408[8]; // this TU's __FILE__ string; unnamed, compiler-synthesized
extern char lbl_804D1D40[]; // the OSPanic() format string below, same reasoning
extern void OSPanic(const char* file, int line, const char* msg, ...);
extern int fn_80400544(int c); // likely tolower, unconfirmed
extern s32 DVDGetCurrentDir(char* path, u32 maxlen);
extern char lbl_804D1ECC[];
extern char lbl_804D1E40[0x34]; // "DVDReadAsync(): specified area is out of the file  "
extern void cbForReadAsync(s32 result, DVDCommandBlock* block);
extern s32 DVDReadAbsAsyncPrio(DVDCommandBlock* block, void* addr, s32 length, s32 offset, void* callback, s32 prio);
extern char lbl_804D1E74[0x58]; // "DVDRead(): specified area is out of the file  "
extern void cbForReadSync(void);
extern void OSWakeupThread(void* queue);
extern char __DVDThreadQueue[8];
extern void fn_80180BFC(void* queue); // likely OSSleepThread, unconfirmed
extern int OSDisableInterrupts(void);
extern int OSRestoreInterrupts(int level);
extern void cbForSeekSync(void);
extern s32 DVDSeekAbsAsyncPrio(DVDCommandBlock* block, u32 offset, void* callback, s32 prio);
extern s32 fn_801862A4(DVDCommandBlock* block); // likely DVDCancel, unconfirmed
extern void OSReport(const char* msg, ...);
extern char lbl_804D1E08[0x38]; // "Warning: DVDOpen(): file '%s' was not found under %s.\n"

void __DVDFSInit(void)
{
    BootInfo = (OSBootInfo*)0x80000000;
    FstStart = BootInfo->FSTLocation;
    if (FstStart) {
        MaxEntryNum = FstStart->nextEntryOrLength;
        FstStringStart = (char*)FstStart + (MaxEntryNum * 0xC);
    }
}

// Walks pathPtr one hierarchy level at a time ("/", ".", ".." handled specially).
// Validates 8-3 filenames unless __DVDLongFileNameFlag is set, then case-insensitively scans the FST's entries at the current directory level (inlined `isSame` helper) for a match.
asm s32 DVDConvertPathToEntrynum(char* pathPtr)
{
    // clang-format off
    nofralloc
    mflr    r0
    stw     r0, 4(r1)
    stwu    r1, -72(r1)
    stmw    r20, 24(r1)
    mr      r23, r3
    lis     r3, lbl_804D1D40@ha
    addi    r25, r23, 0
    addi    r31, r3, lbl_804D1D40@l
    lwz     r26, currentDirectory
L801831B8:
    lbz     r3, 0(r23)
    extsb.  r0, r3
    bne     L801831CC
    mr      r3, r26
    b       L80183474
L801831CC:
    extsb   r0, r3
    cmpwi   r0, 47
    bne     L801831E4
    li      r26, 0
    addi    r23, r23, 1
    b       L801831B8
L801831E4:
    cmpwi   r0, 46
    bne     L8018325C
    lbz     r3, 1(r23)
    extsb   r0, r3
    cmpwi   r0, 46
    bne     L8018323C
    lbz     r3, 2(r23)
    cmpwi   r3, 47
    bne     L80183220
    mulli   r3, r26, 12
    lwz     r4, FstStart
    addi    r0, r3, 4
    lwzx    r26, r4, r0
    addi    r23, r23, 3
    b       L801831B8
L80183220:
    extsb.  r0, r3
    bne     L8018325C
    mulli   r0, r26, 12
    lwz     r3, FstStart
    add     r3, r3, r0
    lwz     r3, 4(r3)
    b       L80183474
L8018323C:
    cmpwi   r0, 47
    bne     L8018324C
    addi    r23, r23, 2
    b       L801831B8
L8018324C:
    extsb.  r0, r3
    bne     L8018325C
    mr      r3, r26
    b       L80183474
L8018325C:
    lwz     r0, __DVDLongFileNameFlag
    cmplwi  r0, 0
    bne     L80183310
    addi    r28, r23, 0
    li      r5, 0
    li      r4, 0
    b       L801832BC
L80183278:
    extsb   r0, r3
    cmpwi   r0, 46
    bne     L801832AC
    subf    r0, r23, r28
    cmpwi   r0, 8
    bgt     L80183298
    cmpwi   r5, 1
    bne     L801832A0
L80183298:
    li      r4, 1
    b       L801832D4
L801832A0:
    addi    r24, r28, 1
    li      r5, 1
    b       L801832B8
L801832AC:
    cmpwi   r0, 32
    bne     L801832B8
    li      r4, 1
L801832B8:
    addi    r28, r28, 1
L801832BC:
    lbz     r3, 0(r28)
    extsb.  r0, r3
    beq     L801832D4
    extsb   r0, r3
    cmpwi   r0, 47
    bne     L80183278
L801832D4:
    cmpwi   r5, 1
    bne     L801832EC
    subf    r0, r24, r28
    cmpwi   r0, 3
    ble     L801832EC
    li      r4, 1
L801832EC:
    cmpwi   r4, 0
    beq     L80183334
    addi    r5, r31, 0
    crclr   4*cr1+eq
    addi    r6, r25, 0
    la      r3, lbl_8066C408
    li      r4, 387
    bl      OSPanic
    b       L80183334
L80183310:
    mr      r28, r23
    b       L8018331C
L80183318:
    addi    r28, r28, 1
L8018331C:
    lbz     r3, 0(r28)
    extsb.  r0, r3
    beq     L80183334
    extsb   r0, r3
    cmpwi   r0, 47
    bne     L80183318
L80183334:
    lbz     r0, 0(r28)
    extsb.  r0, r0
    bne     L80183348
    li      r30, 0
    b       L8018334C
L80183348:
    li      r30, 1
L8018334C:
    mulli   r29, r26, 12
    subf    r27, r23, r28
    addi    r26, r26, 1
    b       L8018343C
L8018335C:
    mulli   r28, r26, 12
    lwzx    r4, r3, r28
    clrrwi. r0, r4, 24
    bne     L80183374
    li      r0, 0
    b       L80183378
L80183374:
    li      r0, 1
L80183378:
    cmpwi   r0, 0
    bne     L80183388
    cmpwi   r30, 1
    beq     L80183404
L80183388:
    lwz     r3, FstStringStart
    clrlwi  r0, r4, 8
    addi    r21, r23, 0
    add     r20, r3, r0
    b       L801833D0
L8018339C:
    lbz     r0, 0(r20)
    addi    r20, r20, 1
    extsb   r3, r0
    bl      fn_80400544
    lbz     r0, 0(r21)
    addi    r22, r3, 0
    addi    r21, r21, 1
    extsb   r3, r0
    bl      fn_80400544
    cmpw    r3, r22
    beq     L801833D0
    li      r0, 0
    b       L801833FC
L801833D0:
    lbz     r0, 0(r20)
    extsb.  r0, r0
    bne     L8018339C
    lbz     r3, 0(r21)
    cmpwi   r3, 47
    beq     L801833F0
    extsb.  r0, r3
    bne     L801833F8
L801833F0:
    li      r0, 1
    b       L801833FC
L801833F8:
    li      r0, 0
L801833FC:
    cmpwi   r0, 1
    beq     L80183458
L80183404:
    lwz     r0, FstStart
    add     r3, r0, r28
    lwz     r0, 0(r3)
    clrrwi. r0, r0, 24
    bne     L80183420
    li      r0, 0
    b       L80183424
L80183420:
    li      r0, 1
L80183424:
    cmpwi   r0, 0
    beq     L80183434
    lwz     r0, 8(r3)
    b       L80183438
L80183434:
    addi    r0, r26, 1
L80183438:
    mr      r26, r0
L8018343C:
    lwz     r3, FstStart
    addi    r0, r3, 8
    lwzx    r0, r29, r0
    cmplw   r26, r0
    blt     L8018335C
    li      r3, -1
    b       L80183474
L80183458:
    cmpwi   r30, 0
    bne     L80183468
    mr      r3, r26
    b       L80183474
L80183468:
    add     r23, r27, r23
    addi    r23, r23, 1
    b       L801831B8
L80183474:
    lmw     r20, 24(r1)
    lwz     r0, 76(r1)
    addi    r1, r1, 72
    mtlr    r0
    blr
    // clang-format on
}

#pragma peephole on

s32 DVDFastOpen(s32 entrynum, DVDFileInfo* fileInfo)
{
    if ((entrynum < 0) || (entrynum >= MaxEntryNum) || entryIsDir(entrynum)) {
        return 0;
    }

    fileInfo->startAddr = filePosition(entrynum);
    fileInfo->length = fileLength(entrynum);
    fileInfo->callback = 0;
    fileInfo->cb.state = 0;

    return 1;
}

s32 DVDOpen(char* fileName, DVDFileInfo* fileInfo)
{
    s32 entry;
    char currentDir[128];

    entry = DVDConvertPathToEntrynum(fileName);

    if (entry < 0) {
        DVDGetCurrentDir(currentDir, 128);
        OSReport(lbl_804D1E08, fileName, currentDir);
        return 0;
    }

    if (entryIsDir(entry)) {
        return 0;
    }

    fileInfo->startAddr = filePosition(entry);
    fileInfo->length = fileLength(entry);
    fileInfo->callback = 0;
    fileInfo->cb.state = 0;

    return 1;
}

s32 DVDClose(DVDFileInfo* fileInfo)
{
    fn_801862A4(&fileInfo->cb);
    return 1;
}

static u32 myStrncpy(char* dest, char* src, u32 maxlen)
{
    u32 i = maxlen;

    while ((i > 0) && (*src != 0)) {
        *dest++ = *src++;
        i--;
    }

    return (maxlen - i);
}

u32 entryToPath(u32 entry, char* path, u32 maxlen)
{
    char* name;
    u32 loc;

    if (entry == 0) {
        return 0;
    }

    name = FstStringStart + (FstStart[entry].isDirAndStringOff & 0xFFFFFF);

    loc = entryToPath(FstStart[entry].parentOrPosition, path, maxlen);

    if (loc == maxlen) {
        return loc;
    }

    *(path + loc++) = '/';

    loc += myStrncpy(path + loc, name, maxlen - loc);

    return loc;
}

s32 DVDConvertEntrynumToPath(s32 entrynum, char* path, u32 maxlen)
{
    u32 loc;

    loc = entryToPath((u32)entrynum, path, maxlen);

    if (loc == maxlen) {
        path[maxlen - 1] = '\0';
        return 0;
    }

    if (entryIsDir(entrynum)) {
        if (loc == maxlen - 1) {
            path[loc] = '\0';
            return 0;
        }

        path[loc++] = '/';
    }

    path[loc] = '\0';
    return 1;
}

s32 DVDGetCurrentDir(char* path, u32 maxlen)
{
    return DVDConvertEntrynumToPath((s32)currentDirectory, path, maxlen);
}

s32 DVDReadAsyncPrio(DVDFileInfo* fileInfo, void* addr, s32 length, s32 offset, void* callback, s32 prio)
{
    if (!((0 <= offset) && (offset <= fileInfo->length))) {
        OSPanic(lbl_8066C408, 0x2EE, lbl_804D1E40);
    }

    if (!((0 <= offset + length) && (offset + length < fileInfo->length + 32))) {
        OSPanic(lbl_8066C408, 0x2F4, lbl_804D1E40);
    }

    fileInfo->callback = callback;
    DVDReadAbsAsyncPrio(&fileInfo->cb, addr, length, fileInfo->startAddr + offset, cbForReadAsync, prio);

    return 1;
}

void cbForReadAsync(s32 result, DVDCommandBlock* block)
{
    DVDFileInfo* fileInfo = (DVDFileInfo*)block;

    if (fileInfo->callback) {
        ((void (*)(s32, DVDFileInfo*))fileInfo->callback)(result, fileInfo);
    }
}

s32 DVDReadPrio(DVDFileInfo* fileInfo, void* addr, s32 length, s32 offset, s32 prio)
{
    s32 result;
    DVDCommandBlock* block;
    s32 state;
    int enabled;
    s32 retVal;

    if (!((0 <= offset) && (offset <= fileInfo->length))) {
        OSPanic(lbl_8066C408, 0x334, lbl_804D1E74);
    }

    if (!((0 <= offset + length) && (offset + length < fileInfo->length + 32))) {
        OSPanic(lbl_8066C408, 0x33A, lbl_804D1E74);
    }

    block = &fileInfo->cb;
    result = DVDReadAbsAsyncPrio(block, addr, length, fileInfo->startAddr + offset, cbForReadSync, prio);
    if (result == 0) {
        return -1;
    }

    enabled = OSDisableInterrupts();

    while (1) {
        state = ((volatile DVDCommandBlock*)block)->state;
        if (state == 0) {
            retVal = (s32)block->transferredSize;
            break;
        } else if (state == -1) {
            retVal = -1;
            break;
        } else if (state == 10) {
            retVal = -3;
            break;
        }
        fn_80180BFC(__DVDThreadQueue);
    }

    OSRestoreInterrupts(enabled);
    return retVal;
}

void cbForReadSync(void)
{
    OSWakeupThread(__DVDThreadQueue);
}

s32 DVDSeekPrio(DVDFileInfo* fileInfo, s32 offset, s32 prio)
{
    s32 result;
    DVDCommandBlock* block;
    s32 state;
    int enabled;
    s32 retVal;

    block = &fileInfo->cb;
    result = DVDSeekAbsAsyncPrio(block, fileInfo->startAddr + offset, cbForSeekSync, prio);
    if (result == 0) {
        return -1;
    }

    enabled = OSDisableInterrupts();

    while (1) {
        state = ((volatile DVDCommandBlock*)block)->state;
        if (state == 0) {
            retVal = 0;
            break;
        } else if (state == -1) {
            retVal = -1;
            break;
        } else if (state == 10) {
            retVal = -3;
            break;
        }
        fn_80180BFC(__DVDThreadQueue);
    }

    OSRestoreInterrupts(enabled);
    return retVal;
}

void cbForSeekSync(void)
{
    OSWakeupThread(__DVDThreadQueue);
}

s32 DVDOpenDir(char* dirName, DVDDir* dir)
{
    s32 entry;
    char currentDir[128];

    entry = DVDConvertPathToEntrynum(dirName);

    if (entry < 0) {
        DVDGetCurrentDir(currentDir, 128);
        OSReport(lbl_804D1ECC, dirName, currentDir);
        return 0;
    }

    if (!entryIsDir(entry)) {
        return 0;
    }

    dir->entryNum = entry;
    dir->location = entry + 1;
    dir->next = fileLength(entry);

    return 1;
}

typedef struct DVDDirEntry
{
    u32 entryNum;
    u32 isDir;
    char* name;
} DVDDirEntry;

#define stringOff(i) (FstStart[i].isDirAndStringOff & ~0xff000000)
#define nextDir(i) (FstStart[i].nextEntryOrLength)

s32 DVDReadDir(DVDDir* dir, DVDDirEntry* dirent)
{
    u32 loc;

    loc = dir->location;
    if ((loc <= dir->entryNum) || (dir->next <= loc)) {
        return 0;
    }
    dirent->entryNum = loc;
    dirent->isDir = entryIsDir(loc);
    dirent->name = FstStringStart + stringOff(loc);
    dir->location = entryIsDir(loc) ? nextDir(loc) : loc + 1;
    return 1;
}

s32 DVDCloseDir(DVDDir* dir)
{
    return 1;
}
