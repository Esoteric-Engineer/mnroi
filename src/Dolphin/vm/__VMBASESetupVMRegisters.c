extern unsigned char* lbl_8066F980;

extern void __VMBASESetupSDR1(void);

// Combines SDR1's hash mask with the page table base and clears SR7, then installs it via __VMBASESetupSDR1. GCC output, so asm.
asm void __VMBASESetupVMRegisters(void)
{
    // clang-format off
    nofralloc
    stwu    r1, -0x10(r1)
    mflr    r0
    stw     r0, 0x14(r1)
    li      r0, 0
    mtsr    7, r0
    mfmsr   r3
    mfsdr1  r4
    lwz     r0, lbl_8066F980
    clrlwi  r4, r4, 16
    rlwinm  r3, r3, 0, 28, 25
    rlwinm  r0, r0, 0, 1, 15
    li      r5, 0
    add     r4, r4, r0
    bl      __VMBASESetupSDR1
    lwz     r0, 0x14(r1)
    mtlr    r0
    addi    r1, r1, 0x10
    blr
    // clang-format on
}
