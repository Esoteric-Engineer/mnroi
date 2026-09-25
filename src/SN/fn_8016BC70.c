extern char lbl_804CFF30[];
extern char lbl_8057BD88[];
void fn_8016B96C(void);
void fn_8016BB98(void);

asm int fn_8016BC70(void)
{
    // clang-format off
    nofralloc
    stwu    r1, -8(r1)
    mflr    r0
    stw     r0, 0xc(r1)
    lis     r9, lbl_804CFF30@ha
    lwz     r0, lbl_804CFF30@l(r9)
    cmpwi   r0, 0
    bne     L_8016BC94
    li      r3, 0
    b       L_8016BCB4
L_8016BC94:
    lwz     r0, lbl_804CFF30@l(r9)
    cmpwi   r0, 5
    bne     L_8016BCA8
    bl      fn_8016BB98
    b       L_8016BCAC
L_8016BCA8:
    bl      fn_8016B96C
L_8016BCAC:
    lis     r9, (lbl_8057BD88+0x170)@ha
    lwz     r3, (lbl_8057BD88+0x170)@l(r9)
L_8016BCB4:
    lwz     r0, 0xc(r1)
    mtlr    r0
    addi    r1, r1, 8
    blr
    // clang-format on
}
