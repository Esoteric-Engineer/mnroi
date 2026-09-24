typedef int BOOL;

typedef struct SramControlBlock {
    unsigned char sram[64];
    unsigned long offset;
    BOOL enabled;
    BOOL locked;
    BOOL sync;
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

extern SramControlBlock Scb;

extern BOOL EXILock(long chan, unsigned long dev, void* callback);
extern BOOL EXISelect(long chan, unsigned long dev, unsigned long freq);
extern void EXIUnlock(long chan);
extern BOOL EXIImm(long chan, void* buf, long len, unsigned long type, void* callback);
extern BOOL EXISync(long chan);
extern BOOL EXIImmEx(long chan, void* buf, long len, unsigned long type);
extern BOOL EXIDeselect(long chan);
extern void WriteSramCallback(long chan, void* ctx);
extern void OSRestoreInterrupts(BOOL level);

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

BOOL UnlockSram(BOOL commit, unsigned long offset)
{
    SramControlBlock* scb = &Scb;
    unsigned short* chksum_p;

    if (commit) {
        if (offset == 0) {
            OSSram* sram = (OSSram*)scb->sram;
            if ((sram->flags & 3u) > 2u) {
                sram->flags &= ~3u;
            }

            sram->checkSum = sram->checkSumInv = 0;
            for (chksum_p = (unsigned short*)&sram->counterBias; chksum_p < (unsigned short*)(scb->sram + sizeof(OSSram)); chksum_p++) {
                sram->checkSum += *chksum_p;
                sram->checkSumInv += ~*chksum_p;
            }
        }

        {
            unsigned long* poff = &scb->offset;

            if (offset < scb->offset) {
                *poff = offset;
            }

            if (*poff <= sizeof(OSSram)) {
                OSSramEx* ex = (OSSramEx*)(scb->sram + sizeof(OSSram));
                unsigned long mode;
                mode = ex->gbsMode;
                if ((mode & 0x7C00) == 0x5000 || (mode & 0xC0) == 0xC0) {
                    ex->gbsMode = 0;
                }
            }

            scb->sync = WriteSram(scb->sram + *poff, *poff, 64 - *poff);
            if (scb->sync) {
                *poff = 64;
            }
        }
    }

    scb->locked = 0;
    OSRestoreInterrupts(scb->enabled);
    return scb->sync;
}

void __OSUnlockSram(BOOL commit)
{
    UnlockSram(commit, 0);
}

void __OSUnlockSramEx(BOOL commit)
{
    UnlockSram(commit, 0x14);
}
