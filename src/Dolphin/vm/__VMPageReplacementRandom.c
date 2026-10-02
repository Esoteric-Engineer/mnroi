extern unsigned long VMLRUCursor;
extern unsigned long VMLRUFirstPass;

extern unsigned long __VMGetNumPagesInMRAM(void);
extern unsigned long VMBASEIsPageLocked(unsigned long page);
extern unsigned long OSGetTick(void);

// Picks a random unlocked page (OSGetTick % page count), or advances the FIFO cursor while
// VMLRUFirstPass is set. GCC output, so asm.
asm unsigned long __VMPageReplacementRandom(void)
{
    // clang-format off
    nofralloc
    stwu    r1, -0x10(r1)
    mflr    r0
    stw     r0, 0x14(r1)
    stw     r31, 0xc(r1)
    stw     r30, 8(r1)
    li      r30, 0
L_loop:
    lwz     r0, VMLRUFirstPass
    cmpwi   r0, 0
    beq     L_random
    lwz     r3, VMLRUCursor
    addi    r0, r3, 1
    mr      r31, r3
    stw     r0, VMLRUCursor
    bl      __VMGetNumPagesInMRAM
    lwz     r0, VMLRUCursor
    cmplw   r0, r3
    blt     L_check
    stw     r30, VMLRUFirstPass
    stw     r30, VMLRUCursor
    b       L_check
L_random:
    bl      __VMGetNumPagesInMRAM
    mr      r31, r3
    bl      OSGetTick
    divwu   r0, r3, r31
    mullw   r0, r0, r31
    subf    r31, r0, r3
L_check:
    mr      r3, r31
    bl      VMBASEIsPageLocked
    cmpwi   r3, 0
    bne     L_loop
    lwz     r0, 0x14(r1)
    mr      r3, r31
    lwz     r31, 0xc(r1)
    lwz     r30, 8(r1)
    mtlr    r0
    addi    r1, r1, 0x10
    blr
    // clang-format on
}
