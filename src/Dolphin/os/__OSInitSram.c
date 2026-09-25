typedef int BOOL;

typedef struct SramControlBlock {
    unsigned char sram[64];
    unsigned long offset;
    BOOL enabled;
    BOOL locked;
    BOOL sync;
    void (*callback)(void);
} SramControlBlock;

typedef struct OSSram {
    unsigned short checkSum;
    unsigned short checkSumInv;
    unsigned long ead0;
    unsigned long ead1;
    long counterBias;
    signed char displayOffsetH;
    unsigned char ntd;
    unsigned char language;
    unsigned char flags;
} OSSram;

typedef struct OSSramEx {
    unsigned char pad[0x28];
    unsigned short gbsMode;
} OSSramEx;

// Defined here, not extern: the pooled .bss address gives the original's `addi r3,r30,0`
// in __OSInitSram and the hoisted `addi r30,r31,0x40` (&Scb.offset) in UnlockSram.
SramControlBlock Scb __attribute__((aligned(32)));

extern void DCInvalidateRange(void* addr, unsigned long nBytes);
extern BOOL EXILock(long chan, unsigned long dev, void* callback);
extern BOOL EXISelect(long chan, unsigned long dev, unsigned long freq);
extern BOOL EXIUnlock(long chan);
extern BOOL EXIImm(long chan, void* buf, long len, unsigned long type, void* callback);
extern BOOL EXISync(long chan);
extern BOOL EXIDma(long chan, void* buf, long len, unsigned long type, void* callback);
extern BOOL EXIImmEx(long chan, void* buf, long len, unsigned long type);
extern BOOL EXIDeselect(long chan);
extern void WriteSramCallback(long chan, void* ctx);
extern BOOL OSDisableInterrupts(void);
extern void OSRestoreInterrupts(BOOL level);
extern unsigned long OSGetGbsMode(void);
extern void OSSetGbsMode(unsigned long mode);

static inline BOOL ReadSram(void* buffer)
{
    unsigned long cmd;
    BOOL err;

    DCInvalidateRange(buffer, 64);

    if (!EXILock(0, 1, 0)) {
        return 0;
    }

    if (!EXISelect(0, 1, 3)) {
        EXIUnlock(0);
        return 0;
    }

    cmd = 0x20000100;
    err = !EXIImm(0, &cmd, 4, 1, 0);
    err |= !EXISync(0);
    err |= !EXIDma(0, buffer, 64, 0, 0);
    err |= !EXISync(0);
    err |= !EXIDeselect(0);
    EXIUnlock(0);

    return !err;
}

static inline BOOL WriteSram(void* buffer, unsigned long offset, unsigned long size)
{
    unsigned long cmd;
    BOOL err;

    if (EXILock(0, 1, WriteSramCallback) == 0) {
        return 0;
    }

    if (EXISelect(0, 1, 3) == 0) {
        EXIUnlock(0);
        return 0;
    }

    offset *= 64;
    cmd = offset + 0x100 | 0xA0000000;
    err = !EXIImm(0, &cmd, 4, 1, 0);
    err |= !EXISync(0);
    err |= !EXIImmEx(0, buffer, size, 1);
    err |= !EXIDeselect(0);
    EXIUnlock(0);
    return !err;
}

void __OSInitSram(void)
{
    SramControlBlock* scb = &Scb;
    scb->enabled = 0;
    scb->locked = 0;
    scb->sync = ReadSram(Scb.sram);
    scb->offset = 64;
    OSSetGbsMode(OSGetGbsMode());
}

static inline void* LockSram(unsigned long offset)
{
    unsigned char* base = Scb.sram;
    BOOL enabled = OSDisableInterrupts();

    if (Scb.locked != 0) {
        OSRestoreInterrupts(enabled);
        return 0;
    }

    Scb.enabled = enabled;
    Scb.locked = 1;
    return base + offset;
}

void* __OSLockSram(void)
{
    unsigned char* sram = Scb.sram;
    BOOL enabled = OSDisableInterrupts();

    if (Scb.locked != 0) {
        OSRestoreInterrupts(enabled);
        sram = 0;
    } else {
        Scb.enabled = enabled;
        Scb.locked = 1;
    }
    return sram;
}

void* __OSLockSramEx(void)
{
    return LockSram(0x14);
}

BOOL UnlockSram(BOOL commit, unsigned long offset)
{
    unsigned short* chksum_p;

    if (commit) {
        if (offset == 0) {
            OSSram* sram = (OSSram*)Scb.sram;
            if ((sram->flags & 3u) > 2u) {
                sram->flags &= ~3u;
            }

            sram->checkSum = sram->checkSumInv = 0;
            for (chksum_p = (unsigned short*)&sram->counterBias; chksum_p < (unsigned short*)(Scb.sram + sizeof(OSSram)); chksum_p++) {
                sram->checkSum += *chksum_p;
                sram->checkSumInv += ~*chksum_p;
            }
        }

        if (offset < Scb.offset) {
            Scb.offset = offset;
        }

        if (Scb.offset <= sizeof(OSSram)) {
            OSSramEx* ex = (OSSramEx*)(Scb.sram + sizeof(OSSram));
            if ((ex->gbsMode & 0x7C00u) == 0x5000 || (ex->gbsMode & 0xC0u) == 0xC0) {
                ex->gbsMode = 0;
            }
        }

        Scb.sync = WriteSram(Scb.sram + Scb.offset, Scb.offset, 64 - Scb.offset);
        if (Scb.sync) {
            Scb.offset = 64;
        }
    }

    Scb.locked = 0;
    OSRestoreInterrupts(Scb.enabled);
    return Scb.sync;
}

void __OSUnlockSram(BOOL commit)
{
    UnlockSram(commit, 0);
}

void __OSUnlockSramEx(BOOL commit)
{
    UnlockSram(commit, 0x14);
}
