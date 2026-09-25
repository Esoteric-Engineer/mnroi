extern char lbl_804CFC80[];
extern void fn_80169304(void);
extern void fn_801694DC(void);

asm void fn_801693DC(void)
{
    // clang-format off
    nofralloc
    lwz     r5, 0x20(r31)
    cmpwi   r5, 0
    beq     L_80169474
    lis     r3, (lbl_804CFC80 + 0x4)@h
    ori     r3, r3, (lbl_804CFC80 + 0x4)@l
    lwz     r3, 0x0(r3)
    cmpwi   r3, 0
    beq     L_8016944C
    cmpwi   r5, 1
    bne     L_8016944C
    lwz     r3, 0x18(r31)
    lbz     r3, 0x0(r3)
    cmpwi   r3, 0xa
    beq     L_8016944C
    cmpwi   r3, 0xd
    beq     L_8016944C
    lbz     r5, 0x6d8(r31)
    add     r4, r5, r31
    stb     r3, 0x6d9(r4)
    addi    r5, r5, 1
    stb     r5, 0x6d8(r31)
    cmpwi   r5, 0x10
    bne     L_80169474
    addi    r4, r31, 0x6d9
    bl      fn_801694DC
    li      r5, 0
    stb     r5, 0x6d8(r31)
    b       L_80169474
L_8016944C:
    lbz     r5, 0x6d8(r31)
    cmpwi   r5, 0
    beq     L_80169468
    addi    r4, r31, 0x6d9
    bl      fn_801694DC
    li      r5, 0
    stb     r5, 0x6d8(r31)
L_80169468:
    lwz     r4, 0x18(r31)
    lwz     r5, 0x20(r31)
    bl      fn_801694DC
L_80169474:
    lwz     r3, 0x370(r31)
    addi    r3, r3, 4
    stw     r3, 0x370(r31)
    li      r3, 0
    stw     r3, 0x18(r31)
    b       fn_80169304
    // clang-format on
}
