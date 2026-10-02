asm void SNSync(void)
{
    // clang-format off
    nofralloc
    lis     r4, 0xcc00
L_wait:
    lwz     r3, 0x6834(r4)
    clrlwi. r3, r3, 31
    bne     L_wait
    blr
    // clang-format on
}
