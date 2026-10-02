asm void SNDeselect(void)
{
    // clang-format off
    nofralloc
    lis     r4, 0xcc00
    lwz     r3, 0x6828(r4)
    andi.   r3, r3, 0x5
    stw     r3, 0x6828(r4)
    blr
    // clang-format on
}
