extern void fn_80172BFC(void);
extern int lbl_8066C3B0;

asm void fn_80172BD4(void)
{
    // clang-format off
    nofralloc
    stwu    r1, -8(r1)
    mflr    r0
    stw     r0, 12(r1)
    lwz     r5, lbl_8066C3B0
    addi    r5, r5, 0x5c
    bl      fn_80172BFC
    lwz     r0, 12(r1)
    mtlr    r0
    addi    r1, r1, 8
    blr
    // clang-format on
}
