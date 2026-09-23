extern void _fwalk(void);
extern void fn_80178224(void);

asm void fn_80178684(void)
{
    // clang-format off
    nofralloc
    stwu    r1, -8(r1)
    mflr    r0
    stw     r0, 12(r1)
    lis     r4, fn_80178224@ha
    addi    r4, r4, fn_80178224@l
    bl      _fwalk
    lwz     r0, 12(r1)
    mtlr    r0
    addi    r1, r1, 8
    blr
    // clang-format on
}
