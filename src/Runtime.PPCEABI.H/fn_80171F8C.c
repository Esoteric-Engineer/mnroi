extern int lbl_8066C3B0;

asm unsigned int fn_80171F8C(void)
{
    // clang-format off
    nofralloc
    lwz     r9, lbl_8066C3B0
    lis     r0, 0x41C6
    ori     r0, r0, 0x4E6D
    lwz     r3, 88(r9)
    mullw   r3, r3, r0
    addi    r3, r3, 12345
    stw     r3, 88(r9)
    clrlwi  r3, r3, 1
    blr
    // clang-format on
}
