typedef unsigned int u32;
typedef int BOOL;

extern BOOL OSDisableInterrupts(void);
extern void OSRestoreInterrupts(BOOL enabled);
extern void SIDisablePolling(u32 poll);
extern void SIGetTypeAsync(int chan, void* callback);
extern void* memset(void* dst, int val, unsigned long n);

extern void PADTypeAndStatusCallback(void);

extern long ResettingChan;
extern u32 Spec;
extern u32 EnabledBits;
extern u32 ResettingBits;
extern u32 RecalibrateBits;
extern u32 WaitingBits;
extern u32 CheckingBits;
extern u32 PendingBits;
extern u32 lbl_8066F3F4;
extern unsigned char Origin[];

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

BOOL PADReset(u32 mask)
{
    BOOL enabled;
    u32 disableBits;

    enabled = OSDisableInterrupts();
    mask |= PendingBits;
    PendingBits = 0;
    mask = mask & ~(WaitingBits | CheckingBits);
    ResettingBits |= mask;
    disableBits = ResettingBits & EnabledBits;
    EnabledBits &= ~mask;
    lbl_8066F3F4 &= ~mask;
    if (Spec == 4) {
        RecalibrateBits |= mask;
    }
    SIDisablePolling(disableBits);
    if (ResettingChan == 0x20) {
        DoReset();
    }
    OSRestoreInterrupts(enabled);
    return 1;
}
