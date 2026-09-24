typedef int BOOL;

typedef struct SramControlBlock {
    unsigned char sram[64];
    unsigned long offset;
    BOOL enabled;
    BOOL locked;
    BOOL sync;
} SramControlBlock;

typedef struct OSSramEx {
    unsigned char pad[0x1C];
    unsigned short wirelessPadID[4];
} OSSramEx;

extern SramControlBlock Scb;

extern BOOL OSDisableInterrupts(void);
extern void OSRestoreInterrupts(BOOL level);
extern void fn_8017F2E4(BOOL commit, unsigned long offset);

static inline void* LockSram(unsigned long offset)
{
    unsigned char* base = Scb.sram;
    BOOL enabled = OSDisableInterrupts();

    if (Scb.locked != 0) {
        OSRestoreInterrupts(enabled);
        return 0;
    }

    Scb.enabled = enabled;
    Scb.locked = 1;
    return base + offset;
}

static inline OSSramEx* __OSLockSramExI(void)
{
    return (OSSramEx*)LockSram(0x14);
}

void OSSetWirelessID(long chan, unsigned short id)
{
    OSSramEx* sram = __OSLockSramExI();

    if (sram->wirelessPadID[chan] != id) {
        sram->wirelessPadID[chan] = id;
        fn_8017F2E4(1, 0x14);
    } else {
        fn_8017F2E4(0, 0x14);
    }
}
