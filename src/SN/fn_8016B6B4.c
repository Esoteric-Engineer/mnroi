extern char lbl_80573680[];
extern void fn_8016B374(void);
extern void fn_8016B4B0(void);

asm void fn_8016B6B4(void)
{
    // clang-format off
    nofralloc
    stwu    r1, -0x20(r1)
    mflr    r0
    stw     r0, 0x24(r1)
    li      r11, 0x18
    addi    r9, r1, 8
    mtctr   r11
    li      r0, 0
L_loop:
    stb     r0, 0(r9)
    addi    r9, r9, 1
    bdnz    L_loop
    lis     r9, (lbl_80573680+0x8874)@ha
    li      r0, 0x10
    lwz     r11, (lbl_80573680+0x8874)@l(r9)
    slwi    r0, r0, 8
    li      r9, 9
    sth     r0, 0xa(r1)
    cmpwi   r11, 0
    stb     r9, 8(r1)
    beq     L_b
    stb     r9, 0x10(r1)
    b       L_join
L_b:
    li      r0, 0xb
    stb     r0, 0x10(r1)
L_join:
    stw     r3, 0x14(r1)
    li      r3, 0x18
    stw     r6, 0x18(r1)
    stw     r5, 0x1c(r1)
    bl      fn_8016B374
    addi    r3, r1, 8
    li      r4, 0x18
    bl      fn_8016B4B0
    lwz     r0, 0x24(r1)
    mtlr    r0
    addi    r1, r1, 0x20
    blr
    // clang-format on
}
