asm void fn_801694B8(void)
{
    // clang-format off
    nofralloc
    mr      r5, r3
    lbz     r0, 0(r5)
    cmpwi   r0, 0
    beq     L_end
L_loop:
    lbzu    r0, 1(r5)
    cmpwi   r0, 0
    bne     L_loop
L_end:
    subf    r5, r3, r5
    mr      r4, r3
    // clang-format on
}
