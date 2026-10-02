/* k_sin.c's seven constants, in the original's .sdata order
 * (S6..S1 then half, not fdlibm's source order). */
double KernelSinS6Const = 1.58969099521155010221e-10;
double KernelSinS5Const = -2.50507602534068634195e-08;
double KernelSinS4Const = 2.75573137070700676789e-06;
double KernelSinS3Const = -1.98412698298579493134e-04;
double KernelSinS2Const = 8.33333333332248946124e-03;
double KernelSinS1Const = -1.66666666666666324348e-01;
double KernelSinHalfConst = 5.00000000000000000000e-01;

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
    lfd     f0, KernelSinS6Const
    lfd     f10, KernelSinS5Const
    cmpwi   r3, 0
    lfd     f12, KernelSinS4Const
    fmul    f7, f9, f8
    lfd     f11, KernelSinS3Const
    fmadd   f0, f9, f0, f10
    lfd     f13, KernelSinS2Const
    fmadd   f0, f9, f0, f12
    fmadd   f0, f9, f0, f11
    fmadd   f0, f9, f0, f13
    beq     L_iy0
    fmul    f0, f7, f0
    lfd     f1, KernelSinHalfConst
    lfd     f13, KernelSinS1Const
    fmsub   f1, f2, f1, f0
    fmul    f13, f7, f13
    fmsub   f1, f9, f1, f2
    fsub    f1, f1, f13
    fsub    f1, f8, f1
    b       L_end
L_iy0:
    lfd     f1, KernelSinS1Const
    fmadd   f1, f9, f0, f1
    fmadd   f1, f7, f1, f8
L_end:
    addi    r1, r1, 0x18
    blr
    // clang-format on
}
