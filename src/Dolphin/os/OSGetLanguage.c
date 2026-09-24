typedef int BOOL;

typedef struct SramControlBlock {
    unsigned char sram[64];
    unsigned long offset;
    BOOL enabled;
    BOOL locked;
    BOOL sync;
} SramControlBlock;

typedef struct OSSram {
    unsigned short checkSum;
    unsigned short checkSumInv;
    unsigned long ead0;
    unsigned long ead1;
    unsigned long counterBias;
    signed char displayOffsetH;
    unsigned char ntd;
    unsigned char language;
    unsigned char flags;
} OSSram;

extern SramControlBlock Scb;

extern BOOL OSDisableInterrupts(void);
extern void OSRestoreInterrupts(BOOL level);
extern void UnlockSram(BOOL commit, unsigned long offset);

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

static inline OSSram* __OSLockSramI(void)
{
    return (OSSram*)LockSram(0);
}

unsigned char OSGetLanguage(void)
{
    OSSram* sram = __OSLockSramI();
    unsigned char language = sram->language;
    UnlockSram(0, 0);
    return language;
}
