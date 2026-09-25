extern void fn_801694DC(void);
extern void fn_80169304(void);

asm void fn_8016948C(void)
{
    // clang-format off
    nofralloc
    lbz     r5, 0x6D8(r31)
    cmpwi   r5, 0
    beq     L_skip
    addi    r4, r31, 0x6D9
    bl      fn_801694DC
    li      r5, 0
    stb     r5, 0x6D8(r31)
L_skip:
    lwz     r3, 0x370(r31)
    addi    r3, r3, 4
    stw     r3, 0x370(r31)
    b       fn_80169304
    // clang-format on
}
