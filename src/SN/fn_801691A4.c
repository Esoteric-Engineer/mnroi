asm void fn_801691A4(void)
{
    // clang-format off
    nofralloc
loop:
    lwz     r4, 0(r3)
    andi.   r4, r4, 0x14
    beq     loop
    stw     r4, 0(r3)
    blr
    // clang-format on
}
