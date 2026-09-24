typedef unsigned int u32;
typedef unsigned char u8;
typedef int BOOL;

extern u32 SIGetResponse(int chan, void* data);
extern void SISetCommand(int chan, u32 command);
extern void SIEnablePolling(u32 poll);
extern void SIGetTypeAsync(int chan, void* callback);
extern BOOL SITransfer(int chan, void* output, u32 outputBytes, void* input, u32 inputBytes, void* callback,
                       long long delay);
extern void* memset(void* dst, int val, unsigned long n);

extern void PADOriginCallback(void);
extern void PADTypeAndStatusCallback(int chan, u32 type);
extern void PADProbeCallback(void);

extern long lbl_8066C49C;
extern u32 lbl_8066C4A4;
extern u32 lbl_8066C4A8;
extern u32 lbl_8066F3DC;
extern u32 lbl_8066F3E0;
extern u32 lbl_8066F3E4;
extern u32 lbl_8066F3F0;
extern u8 lbl_8066C4B0[2];
extern u8 lbl_8066C4B4[2];

u32 Type_8057D560[4];
u8 Origin[4][12];
u32 CmdProbeDevice[4];

static inline void PADEnable(int chan)
{
    u32 cmd;
    u32 chanBit;
    u32 data[2];

    chanBit = 0x80000000 >> chan;
    lbl_8066F3DC |= chanBit;
    SIGetResponse(chan, data);
    cmd = lbl_8066C4A4 | 0x400000;
    SISetCommand(chan, cmd);
    SIEnablePolling(lbl_8066F3DC);
}

static inline void DoReset(void)
{
    u32 chanBit;

    lbl_8066C49C = __cntlzw(lbl_8066F3E0);
    if (lbl_8066C49C != 32) {
        chanBit = 0x80000000 >> lbl_8066C49C;
        lbl_8066F3E0 &= ~chanBit;
        memset(Origin[lbl_8066C49C], 0, 12);
        SIGetTypeAsync(lbl_8066C49C, PADTypeAndStatusCallback);
    }
}

void PADTypeAndStatusCallback(int chan, u32 type)
{
    int c;
    u32 error;
    BOOL rc;
    u32 recalibrate;
    u32 chanBit;

    (void)Type_8057D560;
    (void)Origin;
    (void)CmdProbeDevice;
    rc = 1;
    chanBit = 0x80000000 >> (c = lbl_8066C49C);
    error = type & 0xFF;

    recalibrate = lbl_8066F3E4 & chanBit;
    lbl_8066F3E4 &= ~chanBit;

    if (error & 0xF) {
        DoReset();
        return;
    }

    type &= ~0xFF;
    Type_8057D560[c] = type;
    if ((type & 0x18000000) != 0x08000000 || (type & 0x01000000) == 0) {
        DoReset();
        return;
    }

    if (lbl_8066C4A8 < 2) {
        PADEnable(c);
        DoReset();
        return;
    }

    if (!(type & 0x80000000) || (type & 0x04000000)) {
        if (recalibrate) {
            rc = SITransfer(c, lbl_8066C4B4, 3, Origin[c], 10, PADOriginCallback, 0);
        } else {
            rc = SITransfer(c, lbl_8066C4B0, 1, Origin[c], 10, PADOriginCallback, 0);
        }
    } else if ((type & 0x00100000) && !(type & 0x00080000) && !(type & 0x00040000)) {
        if (type & 0x40000000) {
            rc = SITransfer(c, lbl_8066C4B0, 1, Origin[c], 10, PADOriginCallback, 0);
        } else {
            rc = SITransfer(c, &CmdProbeDevice[c], 3, Origin[c], 8,
                            PADProbeCallback, 0);
        }
    }

    if (!rc) {
        lbl_8066F3F0 |= chanBit;
        DoReset();
    }
}
