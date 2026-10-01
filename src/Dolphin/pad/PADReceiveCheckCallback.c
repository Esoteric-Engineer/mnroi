typedef unsigned int u32;
typedef unsigned char u8;
typedef int BOOL;

extern int OSDisableInterrupts(void);
extern void OSRestoreInterrupts(int enabled);
extern void SIDisablePolling(u32 poll);
extern void OSSetWirelessID(int chan, unsigned short id);
extern BOOL SITransfer(int chan, void* output, u32 outputBytes, void* input, u32 inputBytes, void* callback,
                       long long delay);
extern void PADOriginUpdateCallback(void);

extern u32 EnabledBits;
extern u32 WaitingBits;
extern u32 CheckingBits;
extern u32 PendingBits;
extern u32 lbl_8066F3F4;
extern u8 CmdReadOrigin[2];
extern u8 Origin[4][12];

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

void PADReceiveCheckCallback(int chan, u32 type)
{
    u32 error;
    u32 chanBit;

    chanBit = 0x80000000 >> chan;
    if ((EnabledBits & chanBit) != 0) {
        error = type & 0xFF;
        type &= ~0xFF;

        WaitingBits &= ~chanBit;
        CheckingBits &= ~chanBit;

        if (!(error & 0xF) && (type & 0x80000000) != 0 && (type & 0x00100000) != 0 && (type & 0x40000000) != 0 &&
            !(type & 0x04000000) && !(type & 0x00080000) && !(type & 0x00040000)) {
            SITransfer(chan, CmdReadOrigin, 1, Origin[chan], 10, PADOriginUpdateCallback, 0);
        } else {
            PADDisable(chan);
        }
    }
}
