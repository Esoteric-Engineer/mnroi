extern void fn_8017A67C(void);

asm void fn_8017A6CC(register int severity, register char* msg, register int line)
{
    // clang-format off
    nofralloc
    stwu    r1, -8(r1)
    mflr    r0
    stw     r0, 12(r1)
    bl      fn_8017A67C
    lwz     r0, 12(r1)
    mtlr    r0
    addi    r1, r1, 8
    blr
    // clang-format on
}
