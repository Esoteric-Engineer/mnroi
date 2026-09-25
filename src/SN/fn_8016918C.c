asm void fn_8016918C(void)
{
    // clang-format off
    nofralloc
    lis     r3, -13312
    ori     r3, r3, 0x6000
    lwz     r4, 0(r3)
    andi.   r4, r4, 0x14
    li      r4, 0
    blr
    // clang-format on
}
