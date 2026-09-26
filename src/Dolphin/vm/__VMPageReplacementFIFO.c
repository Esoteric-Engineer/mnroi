extern unsigned long lbl_8066F968;
extern unsigned long lbl_8066CEA0;

extern unsigned long __VMGetNumPagesInMRAM(void);
extern unsigned long VMBASEIsPageLocked(unsigned long page);

// Returns the next unlocked page from a wrapping FIFO cursor. GCC output, so asm.
asm unsigned long __VMPageReplacementFIFO(void)
{
    // clang-format off
    nofralloc
    stwu    r1, -0x10(r1)
    mflr    r0
    stw     r0, 0x14(r1)
    stw     r31, 0xc(r1)
    li      r31, 0
    stw     r30, 8(r1)
L_loop:
    lwz     r3, lbl_8066F968
    addi    r0, r3, 1
    mr      r30, r3
    stw     r0, lbl_8066F968
    bl      __VMGetNumPagesInMRAM
    lwz     r0, lbl_8066F968
    cmplw   r0, r3
    blt     L_nowrap
    stw     r31, lbl_8066CEA0
    stw     r31, lbl_8066F968
L_nowrap:
    mr      r3, r30
    bl      VMBASEIsPageLocked
    cmpwi   r3, 0
    bne     L_loop
    lwz     r0, 0x14(r1)
    mr      r3, r30
    lwz     r31, 0xc(r1)
    lwz     r30, 8(r1)
    mtlr    r0
    addi    r1, r1, 0x10
    blr
    // clang-format on
}
