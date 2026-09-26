typedef long s32;
typedef int BOOL;

extern BOOL EXISelect(s32 chan, unsigned long dev, unsigned long freq);
extern BOOL EXIDeselect(s32 chan);
extern BOOL EXIImm(s32 chan, void* buf, s32 len, unsigned long type, void* callback);
extern BOOL EXISync(s32 chan);

s32 __CARDEnableInterrupt(s32 chan, BOOL enable)
{
    BOOL err;
    unsigned long cmd;

    if (!EXISelect(chan, 0, 4)) {
        return -3;
    }

    cmd = enable ? 0x81010000 : 0x81000000;
    err = 0;
    err |= !EXIImm(chan, &cmd, 2, 1, 0);
    err |= !EXISync(chan);
    err |= !EXIDeselect(chan);

    return err ? -3 : 0;
}
