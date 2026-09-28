float AsinfPio2HiConst = 1.5707962513e+00f;
float AsinfPio2LoConst = 7.5497894159e-08f;
float AsinfHugeConst = 1.000e+30f;
float AsinfOneConst = 1.0000000000e+00f;
float AsinfPS5Const = 3.4793309169e-05f;
float AsinfPS4Const = 7.9153501429e-04f;
float AsinfPS3Const = -4.0055535734e-02f;
float AsinfPS2Const = 2.0121252537e-01f;
float AsinfPS1Const = -3.2556581497e-01f;
float AsinfPS0Const = 1.6666667163e-01f;
float AsinfQS4Const = 7.7038154006e-02f;
float AsinfQS3Const = -6.8828397989e-01f;
float AsinfQS2Const = 2.0209457874e+00f;
float AsinfQS1Const = -2.4033949375e+00f;
float AsinfHalfConst = 5.0000000000e-01f;
float AsinfPio4HiConst = 7.8539818525e-01f;

extern float fabsf(float x);
extern float __ieee754_sqrtf(float x);

asm float __ieee754_asinf(float x)
{
    // clang-format off
    nofralloc
    stwu r1, -0x30(r1)
    mflr r0
    stfd f29, 0x18(r1)
    stfd f30, 0x20(r1)
    stfd f31, 0x28(r1)
    stmw r30, 0x10(r1)
    stw r0, 0x34(r1)
    fmr f6, f1
    fmr f0, f6
    stfs f0, 0x8(r1)
    lwz r30, 0x8(r1)
    clrlwi r31, r30, 1
    lis r0, 0x3f80
    cmpw r31, r0
    bne L_803FFC30
    lfs f1, AsinfPio2LoConst
    lfs f0, AsinfPio2HiConst
    fmuls f1, f6, f1
    fmadds f1, f6, f0, f1
    b L_803FFDEC
L_803FFC30:
    ble L_803FFC40
    fsubs f1, f6, f6
    fdivs f1, f1, f1
    b L_803FFDEC
L_803FFC40:
    lis r0, 0x3eff
    ori r0, r0, 0xffff
    cmpw r31, r0
    bgt L_803FFCE4
    lis r0, 0x31ff
    ori r0, r0, 0xffff
    cmpw r31, r0
    bgt L_803FFC80
    lfs f0, AsinfHugeConst
    lfs f13, AsinfOneConst
    fadds f0, f6, f0
    fcmpu cr0, f0, f13
    fmr f7, f13
    ble L_803FFC88
    fmr f1, f6
    b L_803FFDEC
L_803FFC80:
    lfs f7, AsinfOneConst
    fmuls f31, f6, f6
L_803FFC88:
    lfs f13, AsinfPS4Const
    lfs f0, AsinfPS5Const
    lfs f12, AsinfPS3Const
    fmadds f0, f31, f0, f13
    lfs f11, AsinfPS2Const
    fmadds f0, f31, f0, f12
    lfs f13, AsinfQS4Const
    lfs f10, AsinfQS3Const
    fmadds f0, f31, f0, f11
    lfs f9, AsinfPS1Const
    lfs f8, AsinfQS2Const
    fmadds f13, f31, f13, f10
    lfs f11, AsinfPS0Const
    fmadds f0, f31, f0, f9
    lfs f12, AsinfQS1Const
    fmadds f13, f31, f13, f8
    fmadds f0, f31, f0, f11
    fmadds f13, f31, f13, f12
    fmadds f29, f31, f13, f7
    fmuls f30, f31, f0
    fdivs f7, f30, f29
    fmadds f1, f6, f7, f6
    b L_803FFDEC
L_803FFCE4:
    fmr f1, f6
    bl fabsf
    lfs f8, AsinfOneConst
    lfs f0, AsinfHalfConst
    fsubs f7, f8, f1
    lfs f12, AsinfPS4Const
    lfs f13, AsinfPS5Const
    fmuls f31, f7, f0
    lfs f10, AsinfPS3Const
    fmr f1, f31
    fmadds f13, f31, f13, f12
    lfs f11, AsinfPS2Const
    lfs f12, AsinfQS3Const
    fmadds f13, f31, f13, f10
    lfs f0, AsinfQS4Const
    fmadds f13, f31, f13, f11
    lfs f10, AsinfPS1Const
    fmadds f0, f31, f0, f12
    lfs f9, AsinfQS2Const
    lfs f11, AsinfPS0Const
    fmadds f13, f31, f13, f10
    lfs f12, AsinfQS1Const
    fmadds f0, f31, f0, f9
    fmadds f13, f31, f13, f11
    fmadds f0, f31, f0, f12
    fmadds f29, f31, f0, f8
    fmuls f30, f31, f13
    bl __ieee754_sqrtf
    lis r0, 0x3f79
    ori r0, r0, 0x9999
    cmpw r31, r0
    ble L_803FFD84
    fdivs f7, f30, f29
    lfs f0, AsinfPio2LoConst
    lfs f12, AsinfPio2HiConst
    fmadds f13, f1, f7, f1
    fadds f13, f13, f13
    fsubs f13, f13, f0
    fsubs f31, f12, f13
    b L_803FFDD8
L_803FFD84:
    stfs f1, 0x8(r1)
    lwz r9, 0x8(r1)
    mr r0, r9
    clrrwi r9, r0, 12
    stw r9, 0x8(r1)
    lfs f7, 0x8(r1)
    fmuls f0, f7, f7
    fsubs f0, f31, f0
    lfs f11, AsinfPio2LoConst
    fadds f13, f1, f7
    lfs f9, AsinfPio4HiConst
    fdivs f0, f0, f13
    fdivs f10, f30, f29
    fadds f0, f0, f0
    fsubs f11, f11, f0
    fadds f13, f1, f1
    fadds f12, f7, f7
    fmsubs f30, f13, f10, f11
    fsubs f29, f9, f12
    fsubs f0, f30, f29
    fsubs f31, f9, f0
L_803FFDD8:
    cmpwi r30, 0x0
    bgt L_803FFDE8
    fneg f1, f31
    b L_803FFDEC
L_803FFDE8:
    fmr f1, f31
L_803FFDEC:
    lwz r0, 0x34(r1)
    mtlr r0
    lmw r30, 0x10(r1)
    lfd f29, 0x18(r1)
    lfd f30, 0x20(r1)
    lfd f31, 0x28(r1)
    addi r1, r1, 0x30
    blr
    // clang-format on
}
