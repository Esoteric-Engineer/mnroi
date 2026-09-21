extern void terminate(void);
extern void fn_8017A608(void);
extern void lbl_801796B4(int);
extern void* lbl_804D0670;

asm void fn_8017A5CC(void)
{
    // clang-format off
    nofralloc
    stwu    r1, -8(r1)
    mflr    r0
    stw     r0, 12(r1)
    bl      fn_8017A608
    entry terminate
    stwu    r1, -8(r1)
    mflr    r0
    stw     r0, 12(r1)
    lis     r9, lbl_804D0670@ha
    lwz     r0, lbl_804D0670@l(r9)
    mtlr    r0
    blrl
    lwz     r0, 12(r1)
    mtlr    r0
    addi    r1, r1, 8
    blr
    // clang-format on
}

asm void fn_8017A608(void)
{
    // clang-format off
    nofralloc
    stwu    r1, -8(r1)
    mflr    r0
    stw     r0, 12(r1)
    li      r3, 1
    crclr   6
    bl      lbl_801796B4
    // clang-format on
}
