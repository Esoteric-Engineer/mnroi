#pragma force_active on

const float ExpfHalfConst[2] = {0.5f, -0.5f};                              /* 0x3f000000/bf000000 halF */
const float ExpfLn2HiConst[2] = {0.69313812255859375f, -0.69313812255859375f}; /* 0x3f317180/bf317180 ln2HI */
const float ExpfLn2LoConst[2] = {9.05800061445916e-06f, -9.05800061445916e-06f}; /* 0x3717f7d1/b717f7d1 ln2LO */

struct { float v; } ExpfZeroConst = {0.0f};                    /* 0x00000000 zero */
float ExpfOThresholdConst = 88.7216796875f;                    /* 0x42b17180 overflow threshold */
union { unsigned long w; float f; } ExpfInfConst = {0x7F800000}; /* +inf */
float ExpfUThresholdConst = -103.97208404541016f;              /* 0xc2cff1b5 underflow threshold */
float ExpfInvLn2Const = 1.4426950216293335f;                   /* 0x3fb8aa3b invln2 */
double ExpfCvtConst = 4503601774854144.0;                      /* MWCC's (float)k magic */
float ExpfHugeConst = 1.0000000150474662e+30f;                 /* 0x7149f2ca huge */
float ExpfOneConst = 1.0f;                                     /* 0x3f800000 one */
float ExpfP5Const = 4.138136944220605e-08f;                    /* 0x3331bb4c P5 */
float ExpfP4Const = -1.6533901998627698e-06f;                  /* 0xb5ddea0e P4 */
float ExpfP3Const = 6.61375597701408e-05f;                     /* 0x388ab355 P3 */
float ExpfP2Const = -0.0027777778450399637f;                   /* 0xbb360b61 P2 */
float ExpfP1Const = 0.1666666716337204f;                       /* 0x3e2aaaab P1 */
float ExpfTwoConst = 2.0f;                                     /* 0x40000000 two */
float ExpfTwom100Const = 7.888609052210118e-31f;               /* 0x0d800000 twom100 */

asm float __ieee754_expf(float x)
{
    // clang-format off
    nofralloc
    stwu r1, -0x18(r1)
    fmr f8, f1
    fmr f0, f8
    stfs f0, 0x8(r1)
    lwz r0, 0x8(r1)
    mr r9, r0
    srwi r8, r9, 31
    lis r0, 0x42b1
    clrlwi r9, r9, 1
    ori r0, r0, 0x7217
    cmplw r9, r0
    ble L_803FFE94
    lis r0, 0x7f80
    cmplw r9, r0
    ble L_803FFE50
    fadds f1, f8, f8
    b L_80400030
L_803FFE50:
    cmpw r9, r0
    bne L_803FFE6C
    cmpwi r8, 0x0
    lfs f1, ExpfZeroConst.v
    bne L_80400030
    fmr f1, f8
    b L_80400030
L_803FFE6C:
    lfs f0, ExpfOThresholdConst
    fcmpu cr0, f8, f0
    ble L_803FFE80
    lfs f1, ExpfInfConst.f
    b L_80400030
L_803FFE80:
    lfs f0, ExpfUThresholdConst
    fcmpu cr0, f8, f0
    bge L_803FFE94
    lfs f1, ExpfZeroConst.v
    b L_80400030
L_803FFE94:
    lis r0, 0x3eb1
    ori r0, r0, 0x7218
    cmplw r9, r0
    ble L_803FFF3C
    lis r0, 0x3f85
    ori r0, r0, 0x1591
    cmplw r9, r0
    bgt L_803FFED8
    slwi r10, r8, 2
    la r9, ExpfLn2HiConst
    la r11, ExpfLn2LoConst
    lfsx f0, r9, r10
    subfic r0, r8, 0x1
    lfsx f10, r11, r10
    fsubs f7, f8, f0
    subf r11, r8, r0
    b L_803FFF30
L_803FFED8:
    slwi r0, r8, 2
    la r9, ExpfHalfConst
    lfsx f13, r9, r0
    lfs f0, ExpfInvLn2Const
    mr r9, r11
    lis r10, 0x4330
    lfd f11, ExpfCvtConst
    fmadds f0, f8, f0, f13
    lfs f10, ExpfLn2LoConst
    lfs f13, ExpfLn2HiConst
    fctiwz f12, f0
    stfd f12, 0x10(r1)
    lwz r11, 0x14(r1)
    xoris r0, r11, 0x8000
    stw r0, 0x14(r1)
    stw r10, 0x10(r1)
    lfd f0, 0x10(r1)
    fsub f0, f0, f11
    frsp f9, f0
    fmuls f13, f9, f13
    fsubs f7, f8, f13
    fmuls f10, f9, f10
L_803FFF30:
    fsubs f8, f7, f10
    lfs f6, ExpfOneConst
    b L_803FFF74
L_803FFF3C:
    lis r0, 0x317f
    ori r0, r0, 0xffff
    cmplw r9, r0
    bgt L_803FFF6C
    lfs f0, ExpfHugeConst
    lfs f13, ExpfOneConst
    fadds f0, f8, f0
    fcmpu cr0, f0, f13
    fmr f6, f13
    ble L_803FFF74
    fadds f1, f8, f6
    b L_80400030
L_803FFF6C:
    lfs f6, ExpfOneConst
    li r11, 0x0
L_803FFF74:
    lfs f13, ExpfP4Const
    fmuls f9, f8, f8
    lfs f0, ExpfP5Const
    cmpwi r11, 0x0
    lfs f12, ExpfP3Const
    fmadds f0, f9, f0, f13
    lfs f11, ExpfP2Const
    fmadds f0, f9, f0, f12
    lfs f13, ExpfP1Const
    fmadds f0, f9, f0, f11
    fmadds f0, f9, f0, f13
    fmuls f0, f9, f0
    fsubs f12, f8, f0
    bne L_803FFFC8
    lfs f0, ExpfTwoConst
    fmuls f1, f8, f12
    fsubs f0, f12, f0
    fdivs f1, f1, f0
    fsubs f1, f1, f8
    fsubs f1, f6, f1
    b L_80400030
L_803FFFC8:
    lfs f13, ExpfTwoConst
    fmuls f0, f8, f12
    cmpwi r11, -0x7d
    fsubs f13, f13, f12
    fdivs f0, f0, f13
    fsubs f0, f10, f0
    fsubs f0, f0, f7
    fsubs f0, f6, f0
    bge L_80400014
    stfs f0, 0x8(r1)
    addi r0, r11, 0x64
    slwi r0, r0, 23
    lfs f1, ExpfTwom100Const
    lwz r9, 0x8(r1)
    add r9, r9, r0
    stw r9, 0x8(r1)
    lfs f0, 0x8(r1)
    fmuls f1, f0, f1
    b L_80400030
L_80400014:
    stfs f0, 0x8(r1)
    slwi r0, r11, 23
    lwz r9, 0x8(r1)
    add r9, r9, r0
    stw r9, 0x8(r1)
    lfs f0, 0x8(r1)
    fmr f1, f0
L_80400030:
    addi r1, r1, 0x18
    blr
    // clang-format on
}
