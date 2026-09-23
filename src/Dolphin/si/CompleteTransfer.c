typedef unsigned char u8;
typedef unsigned int u32;
typedef long long s64;

volatile u32 __SIRegs[0x100] : 0xCC006400;

#define SI_COMCSR_IDX 13
#define SI_STATUS_IDX 14
#define SI_COMCSR_TCINT_MASK (1u << 31)
#define SI_COMCSR_TSTART_MASK (1u << 0)
#define SI_COMCSR_COMERR_MASK (1u << 29)

extern s64 __OSGetSystemTime(void);

typedef struct SIControl {
    long chan;
    u32 poll;
    u32 inputBytes;
    void* input;
    void* callback;
} SIControl;

// SIBios.c's .data pool: 0x44 bytes of assert strings, then Si (+0x44) and Type (+0x58), all addressed off the one base.
// Deriving both from a u8* base (rather than a struct pointer) is what reproduces the original's hoisted &Si.inputBytes.
extern u8 lbl_804D1B78[];
#define SI(b) ((SIControl*)((b) + 0x44))
#define TYPE(b) ((u32*)((b) + 0x58))

extern s64 lbl_8057D150[4]; // XferTime
extern s64 TypeTime[4];

static inline void SIClearTCInterrupt(void) {
    u32 reg;

    reg = __SIRegs[SI_COMCSR_IDX];
    reg |= SI_COMCSR_TCINT_MASK;
    reg &= ~SI_COMCSR_TSTART_MASK;
    __SIRegs[SI_COMCSR_IDX] = reg;
}

u32 CompleteTransfer(void) {
    u32 sr;
    u32 i;
    u32 rLen;
    u8* input;
    u32 temp;
    u8* b = lbl_804D1B78;

    sr = __SIRegs[SI_STATUS_IDX];
    SIClearTCInterrupt();

    if (SI(b)->chan != -1) {
        lbl_8057D150[SI(b)->chan] = __OSGetSystemTime();
        input = SI(b)->input;
        rLen = SI(b)->inputBytes / sizeof(u32);
        for (i = 0; i < rLen; i++) {
            *(u32*)input = __SIRegs[i + 0x20];
            input += 4;
        }

        rLen = SI(b)->inputBytes & 3;
        if (rLen != 0) {
            temp = __SIRegs[i + 32];
            for (i = 0; i < rLen; i++) {
                *(input++) = temp >> ((3 - i) * 8);
            }
        }

        if (__SIRegs[SI_COMCSR_IDX] & SI_COMCSR_COMERR_MASK) {
            sr >>= (3 - SI(b)->chan) * 8;
            sr &= 0xF;
            if ((sr & 8) != 0 && (TYPE(b)[SI(b)->chan] & 0x80) == 0) {
                TYPE(b)[SI(b)->chan] = 8;
            }

            if (sr == 0) {
                sr = 4;
            }
        } else {
            TypeTime[SI(b)->chan] = __OSGetSystemTime();
            sr = 0;
        }

        SI(b)->chan = -1;
    }

    return sr;
}
