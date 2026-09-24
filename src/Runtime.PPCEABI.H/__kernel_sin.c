extern double lbl_8066C1D8;
extern double lbl_8066C1E0;
extern double lbl_8066C1E8;
extern double lbl_8066C1F0;
extern double lbl_8066C1F8;
extern double lbl_8066C200;
extern double lbl_8066C208;

asm double __kernel_sin(double x, double y, int iy)
{
    // clang-format off
    nofralloc
    stwu    r1, -0x18(r1)
    fmr     f8, f1
    fmr     f0, f8
    stfd    f0, 8(r1)
    lwz     r9, 8(r1)
    lwz     r10, 0xc(r1)
    clrlwi  r9, r9, 1
    lis     r0, 0x3e3f
    ori     r0, r0, 0xffff
    cmpw    r9, r0
    bgt     L_big
    fctiwz  f0, f8
    stfd    f0, 0x10(r1)
    lwz     r9, 0x14(r1)
    cmpwi   r9, 0
    beq     L_end
L_big:
    fmul    f9, f8, f8
    lfd     f0, lbl_8066C1D8
    lfd     f10, lbl_8066C1E0
    cmpwi   r3, 0
    lfd     f12, lbl_8066C1E8
    fmul    f7, f9, f8
    lfd     f11, lbl_8066C1F0
    fmadd   f0, f9, f0, f10
    lfd     f13, lbl_8066C1F8
    fmadd   f0, f9, f0, f12
    fmadd   f0, f9, f0, f11
    fmadd   f0, f9, f0, f13
    beq     L_iy0
    fmul    f0, f7, f0
    lfd     f1, lbl_8066C208
    lfd     f13, lbl_8066C200
    fmsub   f1, f2, f1, f0
    fmul    f13, f7, f13
    fmsub   f1, f9, f1, f2
    fsub    f1, f1, f13
    fsub    f1, f8, f1
    b       L_end
L_iy0:
    lfd     f1, lbl_8066C200
    fmadd   f1, f9, f0, f1
    fmadd   f1, f7, f1, f8
L_end:
    addi    r1, r1, 0x18
    blr
    // clang-format on
}
