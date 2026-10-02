extern char lbl_804CFF30[];
extern char lbl_8057BEE0[];
void fn_8016B29C(void);

asm void fn_8016BD38(void)
{
    // clang-format off
    nofralloc
    stwu    r1, -0x10(r1)
    mflr    r0
    stmw    r30, 8(r1)
    stw     r0, 0x14(r1)
    lis     r10, (lbl_804CFF30+0x8)@ha
    lis     r7, (lbl_8057BEE0+0x4)@ha
    lwz     r9, (lbl_804CFF30+0x8)@l(r10)
    lis     r8, 0xcc00
    lwz     r3, (lbl_8057BEE0+0x4)@l(r7)
    ori     r8, r8, 0x6828
    addi    r9, r9, 1
    li      r11, 0x88
    stw     r9, (lbl_804CFF30+0x8)@l(r10)
    stw     r11, 0(r8)
    lis     r10, lbl_804CFF30@ha
    lwz     r0, lbl_804CFF30@l(r10)
    cmpwi   r0, 0
    beq     L_end
    lis     r9, (lbl_8057BEE0+0x8)@ha
    lwz     r11, (lbl_8057BEE0+0x8)@l(r9)
    cmpwi   r11, 0
    beq     L_no_pending
    lwz     r0, lbl_804CFF30@l(r10)
    cmpwi   r0, 4
    bne     L_not4
    addi    r0, r3, 0x200
    li      r4, 0x200
    b       L_store
L_not4:
    addi    r0, r3, 0x400
    li      r4, 0x400
L_store:
    stw     r0, (lbl_8057BEE0+0x4)@l(r7)
    lis     r11, (lbl_8057BEE0+0x8)@ha
    lwz     r9, (lbl_8057BEE0+0x8)@l(r11)
    subi    r9, r9, 1
    stw     r9, (lbl_8057BEE0+0x8)@l(r11)
    b       L_call
L_no_pending:
    lis     r9, (lbl_8057BEE0+0xC)@ha
    lwz     r0, (lbl_8057BEE0+0xC)@l(r9)
    cmpwi   r0, 0
    beq     L_no_886C
    lwz     r4, (lbl_8057BEE0+0xC)@l(r9)
    stw     r11, (lbl_8057BEE0+0xC)@l(r9)
    b       L_call
L_no_886C:
    stw     r0, 0(r8)
    lis     r9, (lbl_8057BEE0+0x10)@ha
    lwz     r0, (lbl_8057BEE0+0x10)@l(r9)
    cmpwi   r0, 0
    beq     L_no_8870
    lwz     r0, lbl_804CFF30@l(r10)
    cmpwi   r0, 4
    beq     L_end
    li      r0, 1
    stw     r0, lbl_804CFF30@l(r10)
    b       L_end
L_no_8870:
    lis     r9, (lbl_8057BEE0+0x14)@ha
    lwz     r31, (lbl_8057BEE0+0x14)@l(r9)
    cmpwi   r31, 0
    beq     L_no_8874
    li      r0, 5
    stw     r0, lbl_804CFF30@l(r10)
    b       L_end
L_no_8874:
    lis     r30, (lbl_804CFF30+0x4)@ha
    lis     r9, (lbl_8057BEE0+0x18)@ha
    lwz     r0, (lbl_804CFF30+0x4)@l(r30)
    stw     r31, lbl_804CFF30@l(r10)
    stw     r31, (lbl_8057BEE0+0x18)@l(r9)
    cmpwi   r0, 0
    beq     L_end
    li      r3, 0
    mtlr    r0
    blrl
    stw     r31, (lbl_804CFF30+0x4)@l(r30)
    b       L_end
L_call:
    bl      fn_8016B29C
L_end:
    lwz     r0, 0x14(r1)
    mtlr    r0
    lmw     r30, 8(r1)
    addi    r1, r1, 0x10
    blr
    // clang-format on
}
