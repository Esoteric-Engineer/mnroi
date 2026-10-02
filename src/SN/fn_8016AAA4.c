extern char lbl_804CFE6C[];
extern void OSReport(const char* msg, ...);

asm void fn_8016AAA4(void)
{
    // clang-format off
    nofralloc
    mflr    r0
    stw     r0, 4(r1)
    stwu    r1, -8(r1)
    lis     r3, lbl_804CFE6C+0x65@h
    ori     r3, r3, lbl_804CFE6C+0x65@l
    bl      OSReport
    li      r3, -1
    addi    r1, r1, 8
    lwz     r0, 4(r1)
    mtlr    r0
    blr
    // clang-format on
}
