asm int fn_8016C074(int x)
{
    // clang-format off
    nofralloc
    lis     r0, 0x5705
    ori     r0, r0, 0xFFFF
    cmpw    r3, r0
    lis     r3, 5
    ori     r3, r3, 0x2100
    bgtlr
    li      r3, 0
    blr
    // clang-format on
}
