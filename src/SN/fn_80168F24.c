extern void fn_80168C9C(void);

asm void fn_80168F24(void)
{
    // clang-format off
    nofralloc
    mflr    r30
    lwz     r3, 0x6BC(r31)
    stw     r3, 0x708(r31)
    lwz     r5, 0x6D4(r31)
    li      r6, 0x704
    stwbrx  r5, r6, r31
    li      r4, 4
    li      r6, 0x702
    sthbrx  r4, r6, r31
    addi    r3, r31, 0x700
    addi    r4, r4, 8
    lwz     r0, 0x6A4(r31)
    mtlr    r0
    blrl
    cmpwi   r3, 0
    bne     fn_80168C9C
    mtlr    r30
    blr
    // clang-format on
}
