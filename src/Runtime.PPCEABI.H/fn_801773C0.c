extern unsigned int lbl_8066C3B0;
extern void fn_801773B4(unsigned int);

asm void fn_801773C0(void)
{
    // clang-format off
    nofralloc
    stwu    r1, -8(r1)
    mflr    r0
    stw     r0, 12(r1)
    lwz     r3, lbl_8066C3B0
    bl      fn_801773B4
    lwz     r0, 12(r1)
    mtlr    r0
    addi    r1, r1, 8
    blr
    // clang-format on
}
