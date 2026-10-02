void SNSync(void);

asm int SNRead32(void)
{
    // clang-format off
    nofralloc
    mflr    r4
    stw     r4, 4(r1)
    stwu    r1, -8(r1)
    lis     r4, 0xcc00
    li      r3, 0
    stw     r3, 0x6838(r4)
    li      r3, 0x31
    stw     r3, 0x6834(r4)
    bl      SNSync
    lis     r4, 0xcc00
    lwz     r3, 0x6838(r4)
    lwz     r4, 0xc(r1)
    addi    r1, r1, 8
    mtlr    r4
    blr
    // clang-format on
}
