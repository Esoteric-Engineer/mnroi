asm void fn_80168770(void)
{
    // clang-format off
    nofralloc
    li      r6, 1
    stw     r6, 0x6EC(r31)
    andi.   r6, r3, 3
    bne     L_bytes
    andi.   r6, r4, 3
    bne     L_bytes
    andi.   r6, r5, 3
    bne     L_bytes
    subi    r3, r3, 4
    subi    r4, r4, 4
    add     r5, r5, r4
L_words:
    lwzu    r6, 4(r4)
    stwu    r6, 4(r3)
    cmplw   r4, r5
    blt     L_words
    li      r6, 0
    stw     r6, 0x6EC(r31)
    li      r3, 1
    blr
L_bytes:
    subi    r3, r3, 1
    subi    r4, r4, 1
    add     r5, r5, r4
L_loop:
    lbzu    r6, 1(r4)
    stbu    r6, 1(r3)
    cmplw   r4, r5
    blt     L_loop
    li      r6, 0
    stw     r6, 0x6EC(r31)
    li      r3, 1
    blr
    // clang-format on
}
