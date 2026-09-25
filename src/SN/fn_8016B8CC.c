extern char lbl_8057BD88[];
extern void fn_8016ACCC(void);
extern void fn_8016B740(void);
extern void fn_8016B24C(void);
extern void fn_8016B30C(void);

asm void fn_8016B8CC(void)
{
    // clang-format off
    nofralloc
    stwu    r1, -0x18(r1)
    mflr    r0
    stmw    r29, 0xc(r1)
    stw     r0, 0x1c(r1)
    lis     r9, (lbl_8057BD88+0x15C)@ha
    lis     r29, (lbl_8057BD88+0x160)@ha
    lwz     r30, (lbl_8057BD88+0x15C)@l(r9)
L_wait:
    bl      fn_8016ACCC
    cmpwi   r3, 0
    beq     L_wait
    lis     r9, 0xcc00
    li      r0, 0x1000
    ori     r9, r9, 0x3000
    stw     r0, 0(r9)
    bl      fn_8016B740
    lis     r9, (lbl_8057BD88+0x160)@ha
    lwz     r0, (lbl_8057BD88+0x160)@l(r9)
    cmpwi   r0, 0
    beq     L_else
    lis     r9, (lbl_8057BD88+0x15C)@ha
    lwz     r11, (lbl_8057BD88+0x160)@l(r29)
    lwz     r10, (lbl_8057BD88+0x15C)@l(r9)
    li      r31, 0x400
    subi    r11, r11, 1
    addi    r10, r10, 0x400
    stw     r11, (lbl_8057BD88+0x160)@l(r29)
    stw     r10, (lbl_8057BD88+0x15C)@l(r9)
    b       L_join
L_else:
    lis     r9, (lbl_8057BD88+0x164)@ha
    lwz     r31, (lbl_8057BD88+0x164)@l(r9)
    stw     r0, (lbl_8057BD88+0x164)@l(r9)
L_join:
    bl      fn_8016B24C
    mr      r3, r30
    mr      r4, r31
    bl      fn_8016B30C
    lwz     r0, 0x1c(r1)
    mtlr    r0
    lmw     r29, 0xc(r1)
    addi    r1, r1, 0x18
    blr
    // clang-format on
}
