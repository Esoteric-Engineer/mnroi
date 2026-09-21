typedef int BOOL;

typedef struct SramControlBlock {
    unsigned char sram[64];
    unsigned long offset;
    BOOL enabled;
    BOOL locked;
    BOOL sync;
} SramControlBlock;

extern SramControlBlock Scb;

extern BOOL OSDisableInterrupts(void);
extern void OSRestoreInterrupts(BOOL level);

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

void* __OSLockSram(void)
{
    unsigned char* sram = Scb.sram;
    BOOL enabled = OSDisableInterrupts();

    if (Scb.locked != 0) {
        OSRestoreInterrupts(enabled);
        sram = 0;
    } else {
        Scb.enabled = enabled;
        Scb.locked = 1;
    }
    return sram;
}

void* __OSLockSramEx(void)
{
    return LockSram(0x14);
}
