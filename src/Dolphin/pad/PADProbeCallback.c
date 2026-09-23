typedef unsigned int u32;
typedef int BOOL;

extern u32 SIGetResponse(int chan, void* data);
extern void SISetCommand(int chan, u32 command);
extern void SIEnablePolling(u32 poll);
extern void SIGetTypeAsync(int chan, void* callback);
extern void* memset(void* dst, int val, unsigned long n);

extern void PADTypeAndStatusCallback(void);

extern int lbl_8066C49C;
extern u32 lbl_8066C4A4;
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
        memset(Origin + lbl_8066C49C * 12, 0, 12);
        SIGetTypeAsync(lbl_8066C49C, PADTypeAndStatusCallback);
    }
}

void PADProbeCallback(int chan, u32 error, void* context)
{
    if (!(error & 0xF)) {
        PADEnable(lbl_8066C49C);
        lbl_8066F3E8 |= 0x80000000 >> lbl_8066C49C;
    }
    DoReset();
}
