typedef unsigned long u32;
typedef long s32;

extern int EXIAttach(s32 chan, void* extCallback);
extern int EXILock(s32 chan, u32 dev, void* unlockedCallback);
extern int EXISelect(s32 chan, u32 dev, u32 freq);
extern int EXIImm(s32 chan, void* buf, s32 len, u32 type, void* callback);
extern int EXISync(s32 chan);
extern int EXIDeselect(s32 chan);
extern int EXIUnlock(s32 chan);
extern int EXIDetach(s32 chan);

int ProbeBarnacle(s32 chan, u32 dev, u32* revision)
{
    int err;
    u32 cmd;

    if (chan != 2 && dev == 0 && !EXIAttach(chan, 0)) {
        return 0;
    }

    err = !EXILock(chan, dev, 0);
    if (!err) {
        err = !EXISelect(chan, dev, 0);
        if (!err) {
            cmd = 0x20011300;
            err = 0;
            err |= !EXIImm(chan, &cmd, sizeof(cmd), 1, 0);
            err |= !EXISync(chan);
            err |= !EXIImm(chan, revision, sizeof(revision), 0, 0);
            err |= !EXISync(chan);
            err |= !EXIDeselect(chan);
        }

        EXIUnlock(chan);
    }

    if (chan != 2 && dev == 0) {
        EXIDetach(chan);
    }

    if (err) {
        return 0;
    }

    if (*revision != 0xFFFFFFFF) {
        return 1;
    }

    return 0;
}
