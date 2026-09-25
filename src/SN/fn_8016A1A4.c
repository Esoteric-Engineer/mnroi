extern char lbl_80573680[];

asm void fn_8016A1A4(void)
{
    // clang-format off
    nofralloc
    lis     r3, lbl_80573680@h
    ori     r3, r3, lbl_80573680@l
    lwz     r3, 1744(r3)
    blr
    // clang-format on
}
