extern char lbl_8057BD88[];
extern char lbl_804CFF30[];
extern int SNQueryData(void);
extern void fn_8016AD54(void);
extern void fn_8016AF10(void);

asm void fn_8016BB98(void)
{
    // clang-format off
    nofralloc
    stwu    r1, -0x10(r1)
    mflr    r0
    stmw    r30, 8(r1)
    stw     r0, 0x14(r1)
    lis     r9, (lbl_8057BD88+0x16C)@ha
    lis     r11, (lbl_8057BD88+0x178)@ha
    lwz     r0, (lbl_8057BD88+0x16C)@l(r9)
    addi    r31, r11, (lbl_8057BD88+0x178)@l
    cmpwi   r0, 0
    beq     L_8016BC28
L_8016BBC0:
    bl      SNQueryData
    mr.     r3, r3
    beq     L_8016BBC0
    mr      r4, r3
    lis     r30, (lbl_8057BD88+0x170)@ha
    mr      r3, r31
    bl      fn_8016AD54
    lwz     r9, 8(r31)
    li      r0, 0
    sth     r0, 2(r31)
    mr      r3, r31
    stw     r9, (lbl_8057BD88+0x170)@l(r30)
    li      r4, 8
    bl      fn_8016AF10
    li      r31, 0
    lis     r9, (lbl_804CFF30+0x4)@ha
    lis     r11, lbl_804CFF30@ha
    lwz     r0, (lbl_804CFF30+0x4)@l(r9)
    stw     r31, lbl_804CFF30@l(r11)
    cmpwi   r0, 0
    beq     L_8016BC28
    lwz     r3, (lbl_8057BD88+0x170)@l(r30)
    mtlr    r0
    blrl
    lis     r9, (lbl_804CFF30+0x4)@ha
    stw     r31, (lbl_804CFF30+0x4)@l(r9)
L_8016BC28:
    li      r10, 0
    lis     r9, (lbl_804CFF30+0x4)@ha
    lis     r11, 0xcc00
    stw     r10, (lbl_804CFF30+0x4)@l(r9)
    ori     r11, r11, 0x6828
    li      r0, 8
    stw     r0, 0(r11)
    lis     r9, 0xcc00
    ori     r9, r9, 0x3000
    li      r0, 0x1000
    stw     r0, 0(r9)
    lis     r11, lbl_804CFF30@ha
    stw     r10, lbl_804CFF30@l(r11)
    lwz     r0, 0x14(r1)
    mtlr    r0
    lmw     r30, 8(r1)
    addi    r1, r1, 0x10
    blr
    // clang-format on
}
