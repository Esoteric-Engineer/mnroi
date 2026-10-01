typedef unsigned int u32;
typedef int BOOL;

extern u32 SIGetResponse(int chan, void* data);
extern void SISetCommand(int chan, u32 command);
extern void SIEnablePolling(u32 poll);
extern void SIGetTypeAsync(int chan, void* callback);
extern void* memset(void* dst, int val, unsigned long n);

extern void PADTypeAndStatusCallback(void);

extern long ResettingChan;
extern u32 AnalogMode;
extern u32 lbl_8066F3DC;
extern u32 lbl_8066F3E0;
extern u32 lbl_8066F3E8;
extern unsigned char Origin[];

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
        memset(Origin + ResettingChan * 12, 0, 12);
        SIGetTypeAsync(ResettingChan, PADTypeAndStatusCallback);
    }
}

void PADProbeCallback(int chan, u32 error, void* context)
{
    if (!(error & 0xF)) {
        PADEnable(ResettingChan);
        lbl_8066F3E8 |= 0x80000000 >> ResettingChan;
    }
    DoReset();
}
