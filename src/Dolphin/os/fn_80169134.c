asm void fn_80169134(void)
{
    // clang-format off
    nofralloc
    lis     r5, -13312
    li      r3, 19656
    li      r4, 3
    stw     r4, 12324(r5)
    stw     r3, 12324(r5)
    nop
    b       fn_80169134
    // clang-format on
}
