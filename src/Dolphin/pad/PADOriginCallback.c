typedef unsigned int u32;
typedef int BOOL;

extern u32 SIGetResponse(int chan, void* data);
extern void SISetCommand(int chan, u32 command);
extern void SIEnablePolling(u32 poll);
extern void SIGetTypeAsync(int chan, void* callback);
extern void* memset(void* dst, int val, unsigned long n);

extern void UpdateOrigin(int chan);
extern void PADTypeAndStatusCallback(void);

extern long ResettingChan;
extern u32 AnalogMode;
extern unsigned char Origin[];

u32 __PADSpec;
BOOL Recalibrated;
void (*SamplingCallback)(void);
#pragma force_active on
u32 CmdTypeAndStatus;
#pragma force_active reset
u32 lbl_8066F3F4;
u32 PendingBits;
u32 CheckingBits;
u32 WaitingBits;
u32 RecalibrateBits;
u32 ResettingBits;
u32 EnabledBits;
BOOL Initialized;

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

void PADOriginCallback(int chan, u32 error, void* context)
{
    if (!(error & 0xF)) {
        UpdateOrigin(ResettingChan);
        PADEnable(ResettingChan);
    }
    DoReset();
}
