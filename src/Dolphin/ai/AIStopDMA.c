asm void AIStopDMA(void)
{
    // clang-format off
    nofralloc
    lis     r3, -13312
    addi    r3, r3, 20480
    lhz     r0, 54(r3)
    rlwinm  r0, r0, 0, 17, 15
    sth     r0, 54(r3)
    blr
    // clang-format on
}
