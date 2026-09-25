extern char lbl_804CFD50[];

asm void fn_80168CC8(void)
{
    // clang-format off
    nofralloc
    mflr    r30
    addi    r3, r31, 0x700
    li      r4, 8
    lwz     r0, 0x6A4(r31)
    mtlr    r0
    blrl
    lis     r3, lbl_804CFD50@h
    ori     r3, r3, lbl_804CFD50@l
    li      r4, 8
    lwz     r0, 0x6A4(r31)
    mtlr    r0
    blrl
    li      r5, 0
    stw     r5, 0x6BC(r31)
    mtlr    r30
    blr
    // clang-format on
}
