typedef int BOOL;

extern void DCInvalidateRange(void* addr, unsigned long nBytes);
extern BOOL EXILock(long chan, unsigned long dev, void* callback);
extern BOOL EXISelect(long chan, unsigned long dev, unsigned long freq);
extern BOOL EXIUnlock(long chan);
extern BOOL EXIImm(long chan, void* buf, long len, unsigned long type, void* callback);
extern BOOL EXISync(long chan);
extern BOOL EXIDma(long chan, void* buf, long len, unsigned long type, void* callback);
extern BOOL EXIDeselect(long chan);

BOOL __OSReadROM(void* buffer, long length, long offset)
{
    unsigned long cmd;
    BOOL err;

    DCInvalidateRange(buffer, length);

    if (EXILock(0, 1, 0) == 0) {
        return 0;
    }
    if (EXISelect(0, 1, 3) == 0) {
        EXIUnlock(0);
        return 0;
    }

    cmd = offset << 6;
    err = 0;
    err |= !EXIImm(0, &cmd, 4, 1, 0);
    err |= !EXISync(0);
    err |= !EXIDma(0, buffer, length, 0, 0);
    err |= !EXISync(0);
    err |= !EXIDeselect(0);
    EXIUnlock(0);

    return !err;
}
