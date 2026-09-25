extern void fn_80168C9C(void);
void fn_8016C458(void);

asm void fn_8016927C(void)
{
    // clang-format off
    nofralloc
    mflr    r30
    lbz     r3, 0x701(r31)
    bl      fn_8016C458
    sth     r3, 0x708(r31)
    clrrwi. r3, r3, 31
    beq     L_801692A4
    mfspr   r4, 1013
    stw     r4, 0x450(r31)
    li      r3, 0
    mtspr   1013, r3
L_801692A4:
    li      r4, 2
    li      r5, 0x702
    sthbrx  r4, r5, r31
    addi    r3, r31, 0x700
    addi    r4, r4, 8
    lwz     r0, 0x6a4(r31)
    mtlr    r0
    blrl
    cmpwi   r3, 0
    bne     fn_80168C9C
    mtlr    r30
    blr
    // clang-format on
}
