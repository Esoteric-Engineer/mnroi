extern void fn_80172CEC(void);
extern int lbl_8066C3B0;

asm void fn_80172CC4(void)
{
    // clang-format off
    nofralloc
    stwu    r1, -8(r1)
    mflr    r0
    stw     r0, 12(r1)
    lwz     r4, lbl_8066C3B0
    addi    r4, r4, 0x60
    bl      fn_80172CEC
    lwz     r0, 12(r1)
    mtlr    r0
    addi    r1, r1, 8
    blr
    // clang-format on
}
