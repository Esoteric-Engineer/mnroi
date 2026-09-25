void SNSync(void);

asm void SNWrite32(void)
{
    // clang-format off
    nofralloc
    mflr    r4
    stw     r4, 4(r1)
    stwu    r1, -8(r1)
    lis     r4, 0xcc00
    stw     r3, 0x6838(r4)
    li      r3, 0x35
    stw     r3, 0x6834(r4)
    bl      SNSync
    addi    r1, r1, 8
    lwz     r4, 4(r1)
    mtlr    r4
    blr
    // clang-format on
}
