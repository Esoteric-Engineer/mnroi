extern void fn_80172028(void);
extern int lbl_8066C3B0;

asm void fn_801721C0(void)
{
    // clang-format off
    nofralloc
    stwu    r1, -8(r1)
    mflr    r0
    stw     r0, 12(r1)
    mr      r0, r3
    mr      r9, r4
    mr      r6, r5
    lwz     r3, lbl_8066C3B0
    mr      r4, r0
    mr      r5, r9
    bl      fn_80172028
    lwz     r0, 12(r1)
    mtlr    r0
    addi    r1, r1, 8
    blr
    // clang-format on
}
