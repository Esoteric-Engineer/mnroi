asm void __OSClearAlarm(void)
{
    // clang-format off
    nofralloc
    lwz     r0, 28(r1)
    lwz     r31, 20(r1)
    addi    r1, r1, 24
    mtlr    r0
    blr
    // clang-format on
}
