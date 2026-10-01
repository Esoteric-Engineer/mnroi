extern char lbl_8057BEE0[];
extern char lbl_804CFF30[];
extern int SNQueryData(void);
extern void SNRead(void);
extern void SNWrite(void);

asm void fn_8016BAF0(void)
{
    // clang-format off
    nofralloc
    stwu    r1, -0x10(r1)
    mflr    r0
    stmw    r30, 8(r1)
    stw     r0, 0x14(r1)
    lis     r9, (lbl_8057BEE0+0x20)@ha
    addi    r31, r9, (lbl_8057BEE0+0x20)@l
L_8016BB08:
    bl      SNQueryData
    mr.     r3, r3
    beq     L_8016BB08
    mr      r4, r3
    li      r30, 0
    mr      r3, r31
    bl      SNRead
    lwz     r11, 8(r31)
    li      r0, 0
    lis     r9, (lbl_8057BEE0+0x18)@ha
    sth     r0, 2(r31)
    stw     r11, (lbl_8057BEE0+0x18)@l(r9)
    mr      r3, r31
    li      r4, 8
    bl      SNWrite
    lis     r9, (lbl_804CFF30+0x4)@ha
    lis     r11, lbl_804CFF30@ha
    lwz     r0, (lbl_804CFF30+0x4)@l(r9)
    stw     r30, lbl_804CFF30@l(r11)
    cmpwi   r0, 0
    beq     L_8016BB74
    lis     r9, (lbl_8057BEE0+0x18)@ha
    mtlr    r0
    lwz     r3, (lbl_8057BEE0+0x18)@l(r9)
    blrl
    lis     r9, (lbl_804CFF30+0x4)@ha
    stw     r30, (lbl_804CFF30+0x4)@l(r9)
L_8016BB74:
    lis     r9, 0xcc00
    li      r0, 0x1000
    ori     r9, r9, 0x3000
    stw     r0, 0(r9)
    lwz     r0, 0x14(r1)
    mtlr    r0
    lmw     r30, 8(r1)
    addi    r1, r1, 0x10
    blr
    // clang-format on
}
