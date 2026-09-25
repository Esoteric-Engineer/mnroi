asm void fn_8016BEE4(void)
{
    // clang-format off
    nofralloc
    stwu    r1, -0x10(r1)
    li      r0, 0
    stw     r0, 8(r1)
    lwz     r3, 8(r1)
    mtspr   1013, r3
    isync
    addi    r1, r1, 0x10
    blr
    // clang-format on
}
