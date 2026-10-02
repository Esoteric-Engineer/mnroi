extern char lbl_8057BEE0[];
extern void fn_8016B740(void);
extern void fn_8016B24C(void);
extern void fn_8016B29C(void);

asm void fn_8016B79C(void)
{
    // clang-format off
    nofralloc
    stwu    r1, -0x18(r1)
    mflr    r0
    stmw    r29, 0xc(r1)
    stw     r0, 0x1c(r1)
    lis     r31, (lbl_8057BEE0+0x4)@ha
    lis     r9, 0xcc00
    li      r0, 0x1000
    lwz     r29, (lbl_8057BEE0+0x4)@l(r31)
    ori     r9, r9, 0x3000
    stw     r0, 0(r9)
    bl      fn_8016B740
    lis     r10, (lbl_8057BEE0+0x8)@ha
    lwz     r0, (lbl_8057BEE0+0x8)@l(r10)
    cmpwi   r0, 0
    beq     L_else
    lwz     r11, (lbl_8057BEE0+0x4)@l(r31)
    li      r30, 0x400
    lwz     r9, (lbl_8057BEE0+0x8)@l(r10)
    addi    r11, r11, 0x400
    subi    r9, r9, 1
    stw     r11, (lbl_8057BEE0+0x4)@l(r31)
    stw     r9, (lbl_8057BEE0+0x8)@l(r10)
    b       L_join
L_else:
    lis     r9, (lbl_8057BEE0+0xC)@ha
    lwz     r30, (lbl_8057BEE0+0xC)@l(r9)
    stw     r0, (lbl_8057BEE0+0xC)@l(r9)
L_join:
    bl      fn_8016B24C
    mr      r3, r29
    mr      r4, r30
    bl      fn_8016B29C
    lwz     r0, 0x1c(r1)
    mtlr    r0
    lmw     r29, 0xc(r1)
    addi    r1, r1, 0x18
    blr
    // clang-format on
}
