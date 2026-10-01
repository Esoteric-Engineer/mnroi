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
extern u32 lbl_8066F3DC;
extern u32 lbl_8066F3E0;
extern u32 lbl_8066F3E4;
extern u32 lbl_8066F3E8;
extern u32 lbl_8066F3EC;
extern u32 lbl_8066F3F0;
extern u32 lbl_8066F3F4;
extern unsigned char Origin[];

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

BOOL PADReset(u32 mask)
{
    BOOL enabled;
    u32 disableBits;

    enabled = OSDisableInterrupts();
    mask |= lbl_8066F3F0;
    lbl_8066F3F0 = 0;
    mask = mask & ~(lbl_8066F3E8 | lbl_8066F3EC);
    lbl_8066F3E0 |= mask;
    disableBits = lbl_8066F3E0 & lbl_8066F3DC;
    lbl_8066F3DC &= ~mask;
    lbl_8066F3F4 &= ~mask;
    if (Spec == 4) {
        lbl_8066F3E4 |= mask;
    }
    SIDisablePolling(disableBits);
    if (ResettingChan == 0x20) {
        DoReset();
    }
    OSRestoreInterrupts(enabled);
    return 1;
}
