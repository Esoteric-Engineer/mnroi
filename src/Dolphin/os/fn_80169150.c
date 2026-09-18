extern unsigned int lbl_804CFC8C;

asm void fn_80169150(void)
{
    // clang-format off
    nofralloc
    lis     r4, lbl_804CFC8C@h
    ori     r4, r4, lbl_804CFC8C@l
    li      r5, 0
    stw     r5, 0(r4)
    blr
    // clang-format on
}
