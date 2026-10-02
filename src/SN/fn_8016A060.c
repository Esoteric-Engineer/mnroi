extern char lbl_80573680[];
extern void lbl_8016A0EC(void);

asm void fn_8016A060(void)
{
    // clang-format off
    nofralloc
    mtsprg  1, r31
    li      r31, 4
    mtsprg  2, r31
    lis     r31, lbl_80573680@h
    ori     r31, r31, lbl_80573680@l
    b       lbl_8016A0EC
    // clang-format on
}
