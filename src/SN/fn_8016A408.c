asm void fn_8016A408(void)
{
    // clang-format off
    nofralloc
    li      r12, 0xff
    li      r0, 0xf0
    cmpwi   r10, 0
    beq     L_end
    li      r12, 0xf0
    li      r0, 0xc0
    andi.   r10, r10, 1
    bne     L_end
    li      r12, 0xc0
    li      r0, 0x80
L_end:
    extrwi. r10, r4, 1, 16
    beq     L_ret
    mr      r12, r0
L_ret:
    blr
    // clang-format on
}
