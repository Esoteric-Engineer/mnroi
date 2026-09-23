typedef int BOOL;
typedef unsigned int u32;

volatile u32 __SIRegs[0x100] : 0xCC006400;

#define SI_COMCSR_IDX 13
#define SI_COMCSR_TCINT_MASK (1u << 31)
#define SI_COMCSR_TSTART_MASK (1u << 0)
#define SI_COMCSR_RDSTINTMSK_MASK (1u << 27)

extern int OSDisableInterrupts(void);
extern int OSRestoreInterrupts(int level);

extern unsigned char lbl_8057D010[]; // .bss base; InputBufferVcount[4] is at +0x1E0

BOOL SIEnablePollingInterrupt(BOOL enable) {
    unsigned char* base = lbl_8057D010;
    BOOL enabled;
    BOOL rc;
    u32 reg;
    int i;

    enabled = OSDisableInterrupts();
    reg = __SIRegs[SI_COMCSR_IDX];
    rc = ((reg & SI_COMCSR_RDSTINTMSK_MASK) != 0) ? 1 : 0;

    if (enable) {
        reg |= SI_COMCSR_RDSTINTMSK_MASK;

        for (i = 0; i < 4; i++) {
            ((volatile u32*)(base + 0x1E0))[i] = 0;
        }
    } else {
        reg &= ~SI_COMCSR_RDSTINTMSK_MASK;
    }

    reg &= ~(SI_COMCSR_TCINT_MASK | SI_COMCSR_TSTART_MASK);
    __SIRegs[SI_COMCSR_IDX] = reg;

    OSRestoreInterrupts(enabled);
    return rc;
}
