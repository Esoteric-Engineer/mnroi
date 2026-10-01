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
extern u32 EnabledBits;
extern u32 ResettingBits;
extern u32 WaitingBits;
extern unsigned char Origin[];

static inline void PADEnable(int chan)
{
    u32 cmd;
    u32 chanBit;
    u32 data[2];

    chanBit = 0x80000000 >> chan;
    EnabledBits |= chanBit;
    SIGetResponse(chan, data);
    cmd = AnalogMode | 0x400000;
    SISetCommand(chan, cmd);
    SIEnablePolling(EnabledBits);
}

static inline void DoReset(void)
{
    u32 chanBit;

    ResettingChan = __cntlzw(ResettingBits);
    if (ResettingChan != 32) {
        chanBit = 0x80000000 >> ResettingChan;
        ResettingBits &= ~chanBit;
        memset(Origin + ResettingChan * 12, 0, 12);
        SIGetTypeAsync(ResettingChan, PADTypeAndStatusCallback);
    }
}

void PADProbeCallback(int chan, u32 error, void* context)
{
    if (!(error & 0xF)) {
        PADEnable(ResettingChan);
        WaitingBits |= 0x80000000 >> ResettingChan;
    }
    DoReset();
}
