extern char lbl_80573680[];

asm void fn_80168B9C(void)
{
    // clang-format off
    nofralloc
    lis     r3, lbl_80573680@h
    ori     r3, r3, lbl_80573680@l
    li      r4, 1
    stw     r4, 0x6D4(r3)
    blr
    // clang-format on
}
