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
extern void UnlockSram(BOOL commit, unsigned long offset);

// - sanitises `mode` (bits 0x7C00 == 0x5000 or 0xC0 both set -> 0)
// - locks SRAM
// - updates OSSramEx.gbsMode (+0x14 + 0x28 = SRAM byte 0x3C)
// - commits only if it changed
// Written as asm: plain C stalls at 75.8%.
// The original has an 8-byte larger frame and hoists the (u16)mode copy above the prologue.
asm void OSSetGbsMode(unsigned short mode)
{
    // clang-format off
    nofralloc
    mflr    r0
    clrlwi  r4, r3, 16
    stw     r0, 4(r1)
    rlwinm  r0, r3, 0, 17, 21
    cmplwi  r0, 0x5000
    stwu    r1, -0x20(r1)
    stw     r31, 0x1c(r1)
    stw     r30, 0x18(r1)
    addi    r30, r3, 0
    lis     r3, Scb@ha
    addi    r31, r3, Scb@l
    beq     L_zero
    rlwinm  r0, r4, 0, 24, 25
    cmplwi  r0, 0xc0
    bne     L_lock
L_zero:
    li      r30, 0
L_lock:
    bl      OSDisableInterrupts
    lwz     r0, 0x48(r31)
    addi    r5, r31, 0x48
    cmpwi   r0, 0
    beq     L_acquire
    bl      OSRestoreInterrupts
    li      r4, 0
    b       L_locked
L_acquire:
    stw     r3, 0x44(r31)
    li      r0, 1
    addi    r4, r31, 0x14
    stw     r0, 0(r5)
L_locked:
    lhz     r0, 0x28(r4)
    clrlwi  r3, r30, 16
    cmplw   r3, r0
    bne     L_write
    li      r3, 0
    li      r4, 0x14
    bl      UnlockSram
    b       L_end
L_write:
    sth     r30, 0x28(r4)
    li      r3, 1
    li      r4, 0x14
    bl      UnlockSram
L_end:
    lwz     r0, 0x24(r1)
    lwz     r31, 0x1c(r1)
    lwz     r30, 0x18(r1)
    addi    r1, r1, 0x20
    mtlr    r0
    blr
    // clang-format on
}
