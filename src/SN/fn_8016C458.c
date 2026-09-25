extern char lbl_804CFF30[];
extern char lbl_80573680[];
extern void fn_8016BEE4(void);
extern void fn_8016BF04(void);

asm void fn_8016C458(void)
{
    // clang-format off
    nofralloc
    stwu    r1, -8(r1)
    mflr    r0
    stw     r0, 0xc(r1)
    lis     r9, (lbl_804CFF30+0x10)@ha
    li      r10, 0
    lwz     r0, (lbl_804CFF30+0x10)@l(r9)
    cmpwi   r0, -0x8000
    beq     L_8016C480
    li      r3, 0
    b       L_8016C504
L_8016C480:
    cmpwi   r3, 1
    beq     L_8016C4B8
    bgt     L_8016C498
    cmpwi   r3, 0
    beq     L_8016C4AC
    b       L_8016C4E8
L_8016C498:
    cmpwi   r3, 2
    beq     L_8016C4C4
    cmpwi   r3, 3
    beq     L_8016C4D4
    b       L_8016C4E8
L_8016C4AC:
    lis     r9, (lbl_80573680+0x88F1)@ha
    stb     r10, (lbl_80573680+0x88F1)@l(r9)
    b       L_8016C4E8
L_8016C4B8:
    lis     r9, (lbl_80573680+0x88F1)@ha
    stb     r3, (lbl_80573680+0x88F1)@l(r9)
    b       L_8016C4E8
L_8016C4C4:
    lis     r9, (lbl_80573680+0x88F0)@ha
    stb     r10, (lbl_80573680+0x88F0)@l(r9)
    bl      fn_8016BEE4
    b       L_8016C4E4
L_8016C4D4:
    lis     r9, (lbl_80573680+0x88F0)@ha
    li      r0, 1
    stb     r0, (lbl_80573680+0x88F0)@l(r9)
    bl      fn_8016BF04
L_8016C4E4:
    lis     r10, 0x8000
L_8016C4E8:
    lis     r9, (lbl_80573680+0x88F0)@ha
    lis     r11, (lbl_80573680+0x88F1)@ha
    lbz     r3, (lbl_80573680+0x88F0)@l(r9)
    lbz     r0, (lbl_80573680+0x88F1)@l(r11)
    slwi    r3, r3, 8
    or      r3, r10, r3
    or      r3, r3, r0
L_8016C504:
    lwz     r0, 0xc(r1)
    mtlr    r0
    addi    r1, r1, 8
    blr
    // clang-format on
}
