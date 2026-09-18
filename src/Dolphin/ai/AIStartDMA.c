asm void AIStartDMA(void)
{
    // clang-format off
    nofralloc
    lis   r3, -13312
    addi  r3, r3, 20480
    lhz   r0, 54(r3)
    ori   r0, r0, 0x8000
    sth   r0, 54(r3)
    blr
    // clang-format on
}
