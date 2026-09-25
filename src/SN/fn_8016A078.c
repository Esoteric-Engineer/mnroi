extern void fn_8016A094(void);

asm void fn_8016A078(void)
{
    // clang-format off
    nofralloc
    mtsprg  1, r31
    mfsrr0  r31
    mtsprg  0, r31
    lis     r31, fn_8016A094@h
    ori     r31, r31, fn_8016A094@l
    mtsrr0  r31
    rfi
    // clang-format on
}
