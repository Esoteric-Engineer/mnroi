extern void fn_80172DA0(void);
extern int lbl_8066C3B0;

asm void fn_80172D78(void)
{
    // clang-format off
    nofralloc
    stwu    r1, -8(r1)
    mflr    r0
    stw     r0, 12(r1)
    lwz     r4, lbl_8066C3B0
    addi    r4, r4, 0x7c
    bl      fn_80172DA0
    lwz     r0, 12(r1)
    mtlr    r0
    addi    r1, r1, 8
    blr
    // clang-format on
}
