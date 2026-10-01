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

extern long ResettingChan;
extern u32 AnalogMode;
extern u32 Spec;
extern u32 lbl_8066F3DC;
extern u32 lbl_8066F3E0;
extern u32 lbl_8066F3E4;
extern u32 lbl_8066F3F0;
extern u8 CmdReadOrigin[2];
extern u8 CmdCalibrate[2];

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
    cmd = AnalogMode | 0x400000;
    SISetCommand(chan, cmd);
    SIEnablePolling(lbl_8066F3DC);
}

static inline void DoReset(void)
{
    u32 chanBit;

    ResettingChan = __cntlzw(lbl_8066F3E0);
    if (ResettingChan != 32) {
        chanBit = 0x80000000 >> ResettingChan;
        lbl_8066F3E0 &= ~chanBit;
        memset(Origin[ResettingChan], 0, 12);
        SIGetTypeAsync(ResettingChan, PADTypeAndStatusCallback);
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
    chanBit = 0x80000000 >> (c = ResettingChan);
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

    if (Spec < 2) {
        PADEnable(c);
        DoReset();
        return;
    }

    if (!(type & 0x80000000) || (type & 0x04000000)) {
        if (recalibrate) {
            rc = SITransfer(c, CmdCalibrate, 3, Origin[c], 10, PADOriginCallback, 0);
        } else {
            rc = SITransfer(c, CmdReadOrigin, 1, Origin[c], 10, PADOriginCallback, 0);
        }
    } else if ((type & 0x00100000) && !(type & 0x00080000) && !(type & 0x00040000)) {
        if (type & 0x40000000) {
            rc = SITransfer(c, CmdReadOrigin, 1, Origin[c], 10, PADOriginCallback, 0);
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
