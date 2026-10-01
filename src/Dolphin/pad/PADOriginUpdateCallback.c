typedef unsigned int u32;

extern int OSDisableInterrupts(void);
extern void OSRestoreInterrupts(int enabled);
extern void SIDisablePolling(u32 poll);
extern void OSSetWirelessID(int chan, unsigned short id);
extern void UpdateOrigin(int chan);

extern u32 EnabledBits;
extern u32 WaitingBits;
extern u32 CheckingBits;
extern u32 PendingBits;
extern u32 lbl_8066F3F4;

static inline void PADDisable(int chan)
{
    int enabled;
    u32 chanBit;

    enabled = OSDisableInterrupts();
    chanBit = 0x80000000 >> chan;
    SIDisablePolling(chanBit);
    EnabledBits &= ~chanBit;
    WaitingBits &= ~chanBit;
    CheckingBits &= ~chanBit;
    PendingBits &= ~chanBit;
    lbl_8066F3F4 &= ~chanBit;
    OSSetWirelessID(chan, 0);
    OSRestoreInterrupts(enabled);
}

void PADOriginUpdateCallback(int chan, u32 error, void* context)
{
    if (!(EnabledBits & (0x80000000 >> chan))) {
        return;
    }
    if (!(error & 0xF)) {
        UpdateOrigin(chan);
    }
    if ((error & 0x8) != 0) {
        PADDisable(chan);
    }
}
