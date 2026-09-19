asm unsigned int __OSGetDIConfig(void)
{
    // clang-format off
    nofralloc
    lis     r3, 0xCC00
    addi    r3, r3, 0x6000
    lwz     r0, 0x24(r3)
    clrlwi  r3, r0, 24
    blr
    // clang-format on
}
