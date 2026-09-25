extern char lbl_8057BD88[];
extern char lbl_804CFF30[];
extern void fn_8016B8CC(void);
extern void fn_8016B30C(void);
extern void fn_8016BB98(void);

asm void fn_8016B96C(void)
{
    // clang-format off
    nofralloc
    stwu    r1, -0x28(r1)
    mflr    r0
    stmw    r24, 8(r1)
    stw     r0, 0x2c(r1)
    lis     r9, lbl_804CFF30@ha
    lwz     r0, lbl_804CFF30@l(r9)
    cmpwi   r0, 1
    bne     L_no_reset
    bl      fn_8016B8CC
L_no_reset:
    lis     r9, 0xcc00
    lis     r27, (lbl_8057BD88+0x164)@ha
    ori     r9, r9, 0x6834
L_wait:
    lwz     r0, 0(r9)
    andi.   r11, r0, 1
    bne     L_wait
    lis     r30, (lbl_8057BD88+0x160)@ha
    lwz     r9, (lbl_8057BD88+0x160)@l(r30)
    subi    r9, r9, 1
    stw     r9, (lbl_8057BD88+0x160)@l(r30)
    lwz     r0, (lbl_8057BD88+0x160)@l(r30)
    cmpwi   r0, -1
    beq     L_first_done
    lis     r31, (lbl_8057BD88+0x15C)@ha
L_first_loop:
    lwz     r3, (lbl_8057BD88+0x15C)@l(r31)
    li      r4, 0x400
    bl      fn_8016B30C
    lwz     r9, (lbl_8057BD88+0x160)@l(r30)
    lwz     r11, (lbl_8057BD88+0x15C)@l(r31)
    subi    r9, r9, 1
    stw     r9, (lbl_8057BD88+0x160)@l(r30)
    addi    r11, r11, 0x400
    stw     r11, (lbl_8057BD88+0x15C)@l(r31)
    lwz     r0, (lbl_8057BD88+0x160)@l(r30)
    cmpwi   r0, -1
    bne     L_first_loop
L_first_done:
    lis     r9, (lbl_8057BD88+0x164)@ha
    lwz     r0, (lbl_8057BD88+0x164)@l(r9)
    cmpwi   r0, 0
    beq     L_no_tail
    lis     r9, (lbl_8057BD88+0x15C)@ha
    lwz     r4, (lbl_8057BD88+0x164)@l(r27)
    lwz     r3, (lbl_8057BD88+0x15C)@l(r9)
    bl      fn_8016B30C
    li      r0, 0
    stw     r0, (lbl_8057BD88+0x164)@l(r27)
L_no_tail:
    lis     r9, 0xcc00
    li      r10, 0
    ori     r9, r9, 0x6828
    lis     r11, (lbl_8057BD88+0x168)@ha
    stw     r10, 0(r9)
    lwz     r0, (lbl_8057BD88+0x168)@l(r11)
    cmpwi   r0, 0
    beq     L_done
    lis     r29, 0xcc00
    lis     r24, (lbl_8057BD88+0x164)@ha
    lis     r25, (lbl_8057BD88+0x15C)@ha
    li      r28, 0
    ori     r29, r29, 0x6828
    lis     r26, (lbl_8057BD88+0x168)@ha
L_outer:
    bl      fn_8016B8CC
    lis     r30, (lbl_8057BD88+0x160)@ha
    lwz     r9, (lbl_8057BD88+0x160)@l(r30)
    subi    r9, r9, 1
    stw     r9, (lbl_8057BD88+0x160)@l(r30)
    lwz     r0, (lbl_8057BD88+0x160)@l(r30)
    cmpwi   r0, -1
    beq     L_inner_done
    lis     r31, (lbl_8057BD88+0x15C)@ha
L_inner_loop:
    lwz     r3, (lbl_8057BD88+0x15C)@l(r31)
    li      r4, 0x400
    bl      fn_8016B30C
    lwz     r9, (lbl_8057BD88+0x160)@l(r30)
    lwz     r11, (lbl_8057BD88+0x15C)@l(r31)
    subi    r9, r9, 1
    stw     r9, (lbl_8057BD88+0x160)@l(r30)
    addi    r11, r11, 0x400
    stw     r11, (lbl_8057BD88+0x15C)@l(r31)
    lwz     r0, (lbl_8057BD88+0x160)@l(r30)
    cmpwi   r0, -1
    bne     L_inner_loop
L_inner_done:
    lwz     r0, (lbl_8057BD88+0x164)@l(r24)
    cmpwi   r0, 0
    beq     L_no_tail2
    lwz     r4, (lbl_8057BD88+0x164)@l(r27)
    lwz     r3, (lbl_8057BD88+0x15C)@l(r25)
    bl      fn_8016B30C
    stw     r28, (lbl_8057BD88+0x164)@l(r27)
L_no_tail2:
    stw     r28, 0(r29)
    lwz     r0, (lbl_8057BD88+0x168)@l(r26)
    cmpwi   r0, 0
    bne     L_outer
L_done:
    bl      fn_8016BB98
    lwz     r0, 0x2c(r1)
    mtlr    r0
    lmw     r24, 8(r1)
    addi    r1, r1, 0x28
    blr
    // clang-format on
}
