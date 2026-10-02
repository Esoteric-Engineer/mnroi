typedef unsigned long u32;
typedef long s32;

extern int OSDisableInterrupts(void);
extern int OSRestoreInterrupts(int enabled);
extern int EXILock(s32 chan, u32 dev, void* unlockedCallback);
extern int EXIUnlock(s32 chan);
extern int EXISelect(s32 chan, u32 dev, u32 freq);
extern int EXIDeselect(s32 chan);
extern int EXIImm(s32 chan, void* buf, s32 len, u32 type, void* callback);
extern int EXISync(s32 chan);

extern s32 lbl_8066F4B0;
extern u32 lbl_8066F4B4;
extern u32 lbl_8066F4B8;

static int QueueLength(void)
{
    u32 cmd;

    if (EXISelect(lbl_8066F4B0, lbl_8066F4B4, 3) == 0) {
        return -1;
    }
    cmd = 0x20010000;
    EXIImm(lbl_8066F4B0, &cmd, 4, 1, 0);
    EXISync(lbl_8066F4B0);
    EXIImm(lbl_8066F4B0, &cmd, 1, 0, 0);
    EXISync(lbl_8066F4B0);
    EXIDeselect(lbl_8066F4B0);
    return 0x10 - (cmd >> 24);
}

int WriteUARTN(void* buf, u32 len)
{
    u32 cmd;
    s32 xLen;
    char* ptr;
    int enabled;
    int qLen;
    int error;

    if ((lbl_8066F4B8 - 0xA5FF0000) != 0x5A) {
        return 2;
    }

    enabled = OSDisableInterrupts();
    if (EXILock(lbl_8066F4B0, lbl_8066F4B4, 0) == 0) {
        OSRestoreInterrupts(enabled);
        return 0;
    }

    ptr = (char*)buf;
    while ((u32)ptr - (u32)buf < len) {
        if (*ptr == 0xA) {
            *ptr = 0xD;
        }
        ptr++;
    }

    error = 0;
    cmd = 0xA0010000;

    while (len != 0) {
        qLen = QueueLength();
        if (qLen < 0) {
            error = 3;
            break;
        }

        if ((qLen >= 0xC) || (qLen >= len)) {
            if (EXISelect(lbl_8066F4B0, lbl_8066F4B4, 3) == 0) {
                error = 3;
                break;
            }

            EXIImm(lbl_8066F4B0, &cmd, 4, 1, 0);
            EXISync(lbl_8066F4B0);

            while ((qLen != 0) && (len != 0)) {
                if ((qLen < 4) && (qLen < len)) {
                    break;
                }

                xLen = len < 4 ? (s32)len : 4;

                EXIImm(lbl_8066F4B0, buf, xLen, 1, 0);
                (char*)buf += xLen;
                len -= xLen;
                qLen -= xLen;
                EXISync(lbl_8066F4B0);
            }
            EXIDeselect(lbl_8066F4B0);
        }
    }
    EXIUnlock(lbl_8066F4B0);
    OSRestoreInterrupts(enabled);
    return error;
}
