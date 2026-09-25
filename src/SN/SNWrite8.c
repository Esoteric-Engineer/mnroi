void SNSync(void);

asm void SNWrite8(int arg)
{
    // clang-format off
    nofralloc
    mflr    r4
    stw     r4, 4(r1)
    stwu    r1, -8(r1)
    slwi    r3, r3, 24
    lis     r4, 0xcc00
    stw     r3, 0x6838(r4)
    li      r3, 5
    stw     r3, 0x6834(r4)
    bl      SNSync
    lwz     r4, 0xc(r1)
    addi    r1, r1, 8
    mtlr    r4
    blr
    // clang-format on
}
