typedef int BOOL;

extern BOOL fn_80195270(long chan, unsigned long dev, void* callback);
extern BOOL EXISelect(long chan, unsigned long dev, unsigned long freq);
extern void EXIUnlock(long chan);
extern BOOL fn_80193F48(long chan, void* buf, long len, unsigned long type, void* callback);
extern BOOL fn_80194330(long chan);
extern BOOL EXIImmEx(long chan, void* buf, long len, unsigned long type);
extern BOOL EXIDeselect(long chan);
extern void WriteSramCallback(long chan, void* ctx);

BOOL WriteSram(void* buffer, unsigned long offset, unsigned long size)
{
    unsigned long cmd;
    BOOL err;

    if (fn_80195270(0, 1, WriteSramCallback) == 0) {
        return 0;
    }

    if (EXISelect(0, 1, 3) == 0) {
        EXIUnlock(0);
        return 0;
    }

    offset *= 64;
    cmd = offset + 0x100 | 0xA0000000;
    err = !fn_80193F48(0, &cmd, 4, 1, 0);
    err |= !fn_80194330(0);
    err |= !EXIImmEx(0, buffer, size, 1);
    err |= !EXIDeselect(0);
    EXIUnlock(0);
    return !err;
}
