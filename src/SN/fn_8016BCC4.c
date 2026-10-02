extern char lbl_804CFF30[];
void fn_8016B79C(void);
void fn_8016BAF0(void);

asm void fn_8016BCC4(int arg)
{
    // clang-format off
    nofralloc
    stwu    r1, -8(r1)
    mflr    r0
    stw     r0, 0xc(r1)
    cmpwi   r3, 3
    beq     L_end
    cmplwi  r3, 3
    bgt     L_gt3
    cmpwi   r3, 1
    beq     L_case1
    cmpwi   r3, 2
    beq     L_inc
    b       L_end
L_gt3:
    cmpwi   r3, 4
    beq     L_inc
    cmpwi   r3, 5
    beq     L_case5
    b       L_end
L_case1:
    bl      fn_8016B79C
    b       L_end
L_inc:
    lis     r11, (lbl_804CFF30+0xC)@ha
    lwz     r9, (lbl_804CFF30+0xC)@l(r11)
    addi    r9, r9, 1
    stw     r9, (lbl_804CFF30+0xC)@l(r11)
    b       L_end
L_case5:
    bl      fn_8016BAF0
L_end:
    lwz     r0, 0xc(r1)
    mtlr    r0
    addi    r1, r1, 8
    blr
    // clang-format on
}
