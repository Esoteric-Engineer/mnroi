extern char lbl_8057BEE0[];
extern char lbl_804CFF30[];
extern void fn_8016BC70(void);
extern void fn_8016B6B4(void);

asm void fn_8016B828(void)
{
    // clang-format off
    nofralloc
    stwu    r1, -0x20(r1)
    mflr    r0
    stmw    r26, 0x8(r1)
    stw     r0, 0x24(r1)
    mr      r30, r4
    mr      r26, r3
    mr      r31, r5
    mr      r27, r6
    mr      r28, r7
    mr      r29, r8
    andi.   r0, r30, 0x1f
    bne     L_fail
    andi.   r0, r31, 0x1f
    bne     L_fail
    bl      fn_8016BC70
    lis     r9, (lbl_8057BEE0+0x14)@ha
    lis     r11, (lbl_804CFF30+0x4)@ha
    stw     r29, (lbl_8057BEE0+0x14)@l(r9)
    mr      r3, r26
    stw     r27, (lbl_804CFF30+0x4)@l(r11)
    mr      r6, r28
    mr      r4, r30
    mr      r5, r31
    bl      fn_8016B6B4
    lis     r9, (lbl_8057BEE0+0x10)@ha
    lis     r11, lbl_8057BEE0@ha
    stw     r31, (lbl_8057BEE0+0x10)@l(r9)
    lis     r10, (lbl_8057BEE0+0x4)@ha
    lis     r9, lbl_804CFF30@ha
    li      r0, 1
    stw     r26, lbl_8057BEE0@l(r11)
    li      r3, 0
    stw     r30, (lbl_8057BEE0+0x4)@l(r10)
    stw     r0, lbl_804CFF30@l(r9)
    b       L_end
L_fail:
    li      r3, -1
L_end:
    lwz     r0, 0x24(r1)
    mtlr    r0
    lmw     r26, 0x8(r1)
    addi    r1, r1, 0x20
    blr
    // clang-format on
}
