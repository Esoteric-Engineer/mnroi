void fn_80168770(void);

asm void fn_80168D08(void)
{
    // clang-format off
    nofralloc
    mflr    r30
    li      r6, 0x704
    lwbrx   r3, r6, r31
    addi    r4, r31, 0
    add     r3, r3, r4
    addi    r4, r31, 0x708
    li      r6, 0x702
    lhbrx   r5, r6, r31
    bl      fn_80168770
    addi    r3, r31, 0x700
    li      r4, 8
    lwz     r0, 0x6A4(r31)
    mtlr    r0
    blrl
    mtlr    r30
    blr
    // clang-format on
}
