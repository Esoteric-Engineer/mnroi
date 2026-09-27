asm void SNWiggleSelect(void)
{
    // clang-format off
    nofralloc
    lis     r4, 0xcc00
    lwz     r5, 0x6828(r4)
    andi.   r5, r5, 0x5
    stw     r5, 0x6828(r4)
    li      r3, 0x6
    mtctr   r3
L_wiggle:
    bdnz    L_wiggle
    ori     r5, r5, 0xd0
    stw     r5, 0x6828(r4)
    blr
    // clang-format on
}
