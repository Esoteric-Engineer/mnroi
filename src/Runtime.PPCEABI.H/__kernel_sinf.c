/* kf_cos.c's constants share this object: its .sdata starts 8-aligned here,
 * so __kernel_cosf.c externs them instead of defining them itself. */
float KernelCosfOneConst = 1.0000000000e+00f;
float KernelCosfC6Const = -1.1359647598e-11f;
float KernelCosfC5Const = 2.0875723372e-09f;
float KernelCosfC4Const = -2.7557314297e-07f;
float KernelCosfC3Const = 2.4801587642e-05f;
float KernelCosfC2Const = -1.3888889225e-03f;
float KernelCosfC1Const = 4.1666667908e-02f;
float KernelCosfHalfConst = 5.0000000000e-01f;
float KernelCosfQxConst = 2.8125000000e-01f;
float KernelSinfS6Const = 1.5896910177e-10f;
float KernelSinfS5Const = -2.5050759689e-08f;
float KernelSinfS4Const = 2.7557314297e-06f;
float KernelSinfS3Const = -1.9841270114e-04f;
float KernelSinfS2Const = 8.3333337680e-03f;
float KernelSinfS1Const = -1.6666667163e-01f;
float KernelSinfHalfConst = 5.0000000000e-01f;

asm float __kernel_sinf(float x, float y, int iy)
{
    // clang-format off
    nofralloc
    stwu    r1, -0x18(r1)
    fmr     f9, f1
    fmr     f0, f9
    stfs    f0, 8(r1)
    lwz     r9, 8(r1)
    clrlwi  r9, r9, 1
    lis     r0, 0x31ff
    ori     r0, r0, 0xffff
    cmpw    r9, r0
    bgt     L_big
    fmr     f0, f9
    fctiwz  f13, f0
    stfd    f13, 0x10(r1)
    lwz     r9, 0x14(r1)
    cmpwi   r9, 0
    beq     L_end
L_big:
    lfs     f13, KernelSinfS5Const
    fmuls   f10, f9, f9
    lfs     f0, KernelSinfS6Const
    fmuls   f8, f10, f9
    lfs     f11, KernelSinfS4Const
    cmpwi   r3, 0
    fmadds  f0, f10, f0, f13
    lfs     f12, KernelSinfS3Const
    fmadds  f0, f10, f0, f11
    lfs     f13, KernelSinfS2Const
    fmadds  f0, f10, f0, f12
    fmadds  f0, f10, f0, f13
    beq     L_iy0
    fmuls   f13, f8, f0
    lfs     f1, KernelSinfHalfConst
    lfs     f0, KernelSinfS1Const
    fmsubs  f1, f2, f1, f13
    fmsubs  f1, f10, f1, f2
    fmuls   f0, f8, f0
    fsubs   f1, f1, f0
    fsubs   f1, f9, f1
    b       L_end
L_iy0:
    lfs     f1, KernelSinfS1Const
    fmadds  f1, f10, f0, f1
    fmadds  f1, f8, f1, f9
L_end:
    addi    r1, r1, 0x18
    blr
    // clang-format on
}
