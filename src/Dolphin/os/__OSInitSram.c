typedef int BOOL;

typedef struct SramControlBlock {
    unsigned char sram[64];
    unsigned long offset;
    BOOL enabled;
    BOOL locked;
    BOOL sync;
} SramControlBlock;

extern SramControlBlock Scb;

extern void DCInvalidateRange(void* addr, unsigned long nBytes);
extern BOOL EXILock(long chan, unsigned long dev, void* callback);
extern BOOL EXISelect(long chan, unsigned long dev, unsigned long freq);
extern BOOL EXIUnlock(long chan);
extern BOOL EXIImm(long chan, void* buf, long len, unsigned long type, void* callback);
extern BOOL EXISync(long chan);
extern BOOL EXIDma(long chan, void* buf, long len, unsigned long type, void* callback);
extern BOOL EXIDeselect(long chan);
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

void __OSInitSram(void)
{
    SramControlBlock* scb = &Scb;
    scb->enabled = 0;
    scb->locked = 0;
    scb->sync = ReadSram(Scb.sram);
    scb->offset = 64;
    OSSetGbsMode(OSGetGbsMode());
}
