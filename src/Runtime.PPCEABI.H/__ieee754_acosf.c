struct { float v; } AcosfZeroConst = {0.0000000000e+00f};
float AcosfAcosNegOneConst = 3.1415927410e+00f;
float AcosfPio2Const = 1.5707963705e+00f;
float AcosfPS5Const = 3.4793309169e-05f;
float AcosfPS4Const = 7.9153501429e-04f;
float AcosfPS3Const = -4.0055535734e-02f;
float AcosfPS2Const = 2.0121252537e-01f;
float AcosfPS1Const = -3.2556581497e-01f;
float AcosfPS0Const = 1.6666667163e-01f;
float AcosfQS4Const = 7.7038154006e-02f;
float AcosfQS3Const = -6.8828397989e-01f;
float AcosfQS2Const = 2.0209457874e+00f;
float AcosfQS1Const = -2.4033949375e+00f;
float AcosfOneConst = 1.0000000000e+00f;
float AcosfPio2LoConst = 7.5497894159e-08f;
float AcosfPio2HiConst = 1.5707962513e+00f;
float AcosfHalfConst = 5.0000000000e-01f;
float AcosfPiConst = 3.1415925026e+00f;

extern float __ieee754_sqrtf(float x);

asm float __ieee754_acosf(float x)
{
    // clang-format off
    nofralloc
    stwu    r1, -0x28(r1)
    mflr    r0
    stfd    f29, 0x10(r1)
    stfd    f30, 0x18(r1)
    stfd    f31, 0x20(r1)
    stw     r0, 0x2c(r1)
    fmr     f6, f1
    fmr     f0, f6
    stfs    f0, 0x8(r1)
    lwz     r9, 0x8(r1)
    clrlwi  r11, r9, 1
    lis     r0, 0x3f80
    cmpw    r11, r0
    bne     L_8016CE64
    cmpwi   r9, 0x0
    lfs     f1, AcosfZeroConst.v
    bgt     L_8016D048
    lfs     f1, AcosfAcosNegOneConst
    b       L_8016D048
L_8016CE64:
    ble     L_8016CE74
    fsubs   f1, f6, f6
    fdivs   f1, f1, f1
    b       L_8016D048
L_8016CE74:
    lis     r0, 0x3eff
    ori     r0, r0, 0xffff
    cmpw    r11, r0
    bgt     L_8016CF10
    lis     r0, 0x2300
    cmpw    r11, r0
    bgt     L_8016CE98
    lfs     f1, AcosfPio2Const
    b       L_8016D048
L_8016CE98:
    lfs     f0, AcosfPS4Const
    fmuls   f30, f6, f6
    lfs     f13, AcosfPS5Const
    lfs     f12, AcosfPS3Const
    fmadds  f13, f30, f13, f0
    lfs     f11, AcosfPS2Const
    fmadds  f13, f30, f13, f12
    lfs     f10, AcosfQS3Const
    lfs     f12, AcosfPS1Const
    fmadds  f13, f30, f13, f11
    lfs     f0, AcosfQS4Const
    lfs     f9, AcosfQS2Const
    fmadds  f13, f30, f13, f12
    fmadds  f0, f30, f0, f10
    lfs     f11, AcosfQS1Const
    lfs     f8, AcosfPS0Const
    fmadds  f0, f30, f0, f9
    lfs     f12, AcosfOneConst
    fmadds  f0, f30, f0, f11
    fmadds  f13, f30, f13, f8
    lfs     f1, AcosfPio2LoConst
    fmadds  f29, f30, f0, f12
    lfs     f11, AcosfPio2HiConst
    fmuls   f31, f30, f13
    fdivs   f10, f31, f29
    fmuls   f0, f6, f10
    fsubs   f1, f1, f0
    fsubs   f1, f6, f1
    fsubs   f1, f11, f1
    b       L_8016D048
L_8016CF10:
    cmpwi   r9, 0x0
    blt     L_8016CFC0
    lfs     f31, AcosfOneConst
    lfs     f13, AcosfHalfConst
    fsubs   f0, f31, f6
    fmuls   f30, f0, f13
    fmr     f1, f30
    bl      __ieee754_sqrtf
    fmr     f6, f1
    lfs     f0, AcosfPS4Const
    fmr     f12, f6
    lfs     f13, AcosfPS5Const
    stfs    f12, 0x8(r1)
    lfs     f11, AcosfPS3Const
    fmadds  f13, f30, f13, f0
    lwz     r0, 0x8(r1)
    lfs     f0, AcosfQS4Const
    fmadds  f13, f30, f13, f11
    clrrwi  r9, r0, 12
    lfs     f9, AcosfQS3Const
    lfs     f12, AcosfPS2Const
    stw     r9, 0x8(r1)
    fmadds  f0, f30, f0, f9
    lfs     f7, AcosfQS2Const
    fmadds  f13, f30, f13, f12
    lfs     f8, AcosfPS1Const
    lfs     f11, AcosfQS1Const
    fmadds  f0, f30, f0, f7
    lfs     f1, 0x8(r1)
    fmadds  f13, f30, f13, f8
    lfs     f10, AcosfPS0Const
    fmadds  f0, f30, f0, f11
    fmadds  f29, f30, f0, f31
    fmuls   f12, f1, f1
    fmadds  f13, f30, f13, f10
    fadds   f0, f6, f1
    fsubs   f12, f30, f12
    fmuls   f31, f30, f13
    fdivs   f12, f12, f0
    fdivs   f10, f31, f29
    fmadds  f0, f10, f6, f12
    fadds   f1, f1, f0
    fadds   f1, f1, f1
    b       L_8016D048
L_8016CFC0:
    lfs     f7, AcosfOneConst
    lfs     f12, AcosfHalfConst
    fadds   f0, f6, f7
    lfs     f11, AcosfPS4Const
    lfs     f13, AcosfPS5Const
    fmuls   f30, f0, f12
    lfs     f10, AcosfPS3Const
    fmr     f1, f30
    fmadds  f13, f30, f13, f11
    lfs     f12, AcosfPS2Const
    fmadds  f13, f30, f13, f10
    lfs     f0, AcosfQS4Const
    lfs     f11, AcosfQS3Const
    fmadds  f13, f30, f13, f12
    lfs     f10, AcosfPS1Const
    lfs     f8, AcosfQS2Const
    fmadds  f0, f30, f0, f11
    lfs     f9, AcosfPS0Const
    fmadds  f13, f30, f13, f10
    lfs     f12, AcosfQS1Const
    fmadds  f0, f30, f0, f8
    fmadds  f13, f30, f13, f9
    fmadds  f0, f30, f0, f12
    fmadds  f29, f30, f0, f7
    fmuls   f31, f30, f13
    bl      __ieee754_sqrtf
    fdivs   f10, f31, f29
    lfs     f0, AcosfPio2LoConst
    lfs     f13, AcosfPiConst
    fmr     f6, f1
    fmsubs  f0, f10, f6, f0
    fadds   f1, f6, f0
    fadds   f1, f1, f1
    fsubs   f1, f13, f1
L_8016D048:
    lwz     r0, 0x2c(r1)
    mtlr    r0
    lfd     f29, 0x10(r1)
    lfd     f30, 0x18(r1)
    lfd     f31, 0x20(r1)
    addi    r1, r1, 0x28
    blr
    // clang-format on
}
