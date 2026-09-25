asm void fn_8016BF04(void)
{
    // clang-format off
    nofralloc
    stwu    r1, -0x10(r1)
    lis     r0, 0xCC00
    ori     r0, r0, 0x601E
    stw     r0, 8(r1)
    lwz     r3, 8(r1)
    mtspr   1013, r3
    isync
    addi    r1, r1, 0x10
    blr
    // clang-format on
}
