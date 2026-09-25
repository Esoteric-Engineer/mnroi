asm void fn_801692D4(void)
{
    // clang-format off
    nofralloc
    li      r6, 0x704
    lwbrx   r3, r6, r31
    stw     r3, 0x370(r31)
    mfmsr   r3
    rlwinm  r3, r3, 0, 17, 15
    mtmsr   r3
    lis     r5, 0xcc00
    li      r4, 0
    stw     r4, 0x3004(r5)
    li      r4, 0
    lis     r3, 0xcc00
    sth     r4, 0x2002(r3)
    // clang-format on
}
