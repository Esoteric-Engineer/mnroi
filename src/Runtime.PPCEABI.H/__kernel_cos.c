/* k_cos.c's constants, in the original's .sdata order
 * (one, then C6..C1, then the 0.5 and 0.28125 literals). */
double KernelCosOneConst = 1.00000000000000000000e+00;
double KernelCosC6Const = -1.13596475577881948265e-11;
double KernelCosC5Const = 2.08757232129817482790e-09;
double KernelCosC4Const = -2.75573143513906633035e-07;
double KernelCosC3Const = 2.48015872894767294178e-05;
double KernelCosC2Const = -1.38888888888741095749e-03;
double KernelCosC1Const = 4.16666666666666019037e-02;
double KernelCosHalfConst = 5.00000000000000000000e-01;
double KernelCosQxConst = 2.81250000000000000000e-01;

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
    lfd     f1, KernelCosOneConst
    b       L_end
L_big:
    fmul    f9, f1, f1
    lfd     f13, KernelCosC5Const
    lfd     f0, KernelCosC6Const
    lis     r0, 0x3fd3
    lfd     f10, KernelCosC4Const
    ori     r0, r0, 0x3332
    fmadd   f0, f9, f0, f13
    lfd     f12, KernelCosC3Const
    lfd     f11, KernelCosC2Const
    cmpw    r10, r0
    fmadd   f0, f9, f0, f10
    lfd     f13, KernelCosC1Const
    fmadd   f0, f9, f0, f12
    fmadd   f0, f9, f0, f11
    fmadd   f0, f9, f0, f13
    fmul    f11, f9, f0
    bgt     L_ge
    fmul    f0, f1, f2
    lfd     f13, KernelCosOneConst
    lfd     f1, KernelCosHalfConst
    fmsub   f0, f9, f11, f0
    fmsub   f1, f9, f1, f0
    b       L_fin
L_ge:
    lis     r0, 0x3fe9
    cmpw    r10, r0
    ble     L_sub
    lfd     f12, KernelCosQxConst
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
    lfd     f13, KernelCosOneConst
    lfd     f1, KernelCosHalfConst
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
