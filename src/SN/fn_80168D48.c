void fn_80168770(void);
extern void fn_80168C9C(void);

asm void fn_80168D48(void)
{
    // clang-format off
    nofralloc
    mflr    r30
    li      r6, 0x704
    lwbrx   r4, r6, r31
    addi    r5, r31, 0
    add     r4, r4, r5
    addi    r3, r31, 0x708
    li      r6, 0x702
    lhbrx   r5, r6, r31
    mr      r29, r5
    bl      fn_80168770
    addi    r3, r31, 0x700
    mr      r4, r29
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
