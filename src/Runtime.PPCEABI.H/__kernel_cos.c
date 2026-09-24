extern double lbl_8066C190;
extern double lbl_8066C198;
extern double lbl_8066C1A0;
extern double lbl_8066C1A8;
extern double lbl_8066C1B0;
extern double lbl_8066C1B8;
extern double lbl_8066C1C0;
extern double lbl_8066C1C8;
extern double lbl_8066C1D0;

asm double __kernel_cos(double x, double y)
{
    // clang-format off
    nofralloc
    stwu    r1, -0x18(r1)
    fmr     f0, f1
    stfd    f0, 8(r1)
    lwz     r9, 8(r1)
    lwz     r10, 0xc(r1)
    clrlwi  r10, r9, 1
    lis     r0, 0x3e3f
    ori     r0, r0, 0xffff
    cmpw    r10, r0
    bgt     L_big
    fctiwz  f0, f1
    stfd    f0, 0x10(r1)
    lwz     r9, 0x14(r1)
    cmpwi   r9, 0
    bne     L_big
    lfd     f1, lbl_8066C190
    b       L_end
L_big:
    fmul    f9, f1, f1
    lfd     f13, lbl_8066C1A0
    lfd     f0, lbl_8066C198
    lis     r0, 0x3fd3
    lfd     f10, lbl_8066C1A8
    ori     r0, r0, 0x3332
    fmadd   f0, f9, f0, f13
    lfd     f12, lbl_8066C1B0
    lfd     f11, lbl_8066C1B8
    cmpw    r10, r0
    fmadd   f0, f9, f0, f10
    lfd     f13, lbl_8066C1C0
    fmadd   f0, f9, f0, f12
    fmadd   f0, f9, f0, f11
    fmadd   f0, f9, f0, f13
    fmul    f11, f9, f0
    bgt     L_ge
    fmul    f0, f1, f2
    lfd     f13, lbl_8066C190
    lfd     f1, lbl_8066C1C8
    fmsub   f0, f9, f11, f0
    fmsub   f1, f9, f1, f0
    b       L_fin
L_ge:
    lis     r0, 0x3fe9
    cmpw    r10, r0
    ble     L_sub
    lfd     f12, lbl_8066C1D0
    b       L_st
L_sub:
    subis   r11, r10, 0x20
    li      r12, 0
    stw     r11, 8(r1)
    stw     r12, 0xc(r1)
    lfd     f0, 8(r1)
    fmr     f12, f0
L_st:
    fmul    f0, f1, f2
    lfd     f13, lbl_8066C190
    lfd     f1, lbl_8066C1C8
    fmsub   f0, f9, f11, f0
    fmsub   f1, f9, f1, f12
    fsub    f13, f13, f12
    fsub    f1, f1, f0
L_fin:
    fsub    f1, f13, f1
L_end:
    addi    r1, r1, 0x18
    blr
    // clang-format on
}
