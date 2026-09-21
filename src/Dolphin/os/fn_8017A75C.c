extern void lbl_8016AAD8(void);
extern void lbl_8016AAE0(void);
extern void lbl_8016AAE8(void);

asm void fn_8017A75C(void)
{
    // clang-format off
    nofralloc
    stwu    r1, -0x78(r1)
    mflr    r0
    stmw    r30, 0x70(r1)
    stw     r0, 0x7c(r1)
    mr      r30, r3
    stw     r5, 0x10(r1)
    stw     r6, 0x14(r1)
    stw     r7, 0x18(r1)
    stw     r8, 0x1c(r1)
    stw     r9, 0x20(r1)
    stw     r10, 0x24(r1)
    bne     cr1, L_a
    stfd    f1, 0x28(r1)
    stfd    f2, 0x30(r1)
    stfd    f3, 0x38(r1)
    stfd    f4, 0x40(r1)
    stfd    f5, 0x48(r1)
    stfd    f6, 0x50(r1)
    stfd    f7, 0x58(r1)
    stfd    f8, 0x60(r1)
L_a:
    mr      r31, r4
    andi.   r0, r31, 0x200
    beq     L_b
    mr      r3, r30
    li      r4, 0
    bl      lbl_8016AAD8
    cmpwi   r3, -1
    beq     L_b
    bl      lbl_8016AAE8
    cmpwi   r3, 0
    li      r3, -1
    bne     L_c
L_b:
    mr      r3, r30
    mr      r4, r31
    li      r5, 0
    bl      lbl_8016AAE0
L_c:
    lwz     r0, 0x7c(r1)
    mtlr    r0
    lmw     r30, 0x70(r1)
    addi    r1, r1, 0x78
    blr
    // clang-format on
}
