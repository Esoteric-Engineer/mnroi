#pragma force_active on

const double ExpHalfConst0 = 0.5;
const double ExpHalfConst1 = -0.5;
const double ExpLn2HiConst0 = 6.93147180369123816490e-01;
const double ExpLn2HiConst1 = -6.93147180369123816490e-01;
const double ExpLn2LoConst0 = 1.90821492927058770002e-10;
const double ExpLn2LoConst1 = -1.90821492927058770002e-10;

struct { double v; } ExpZeroConst = { 0.0 };
double ExpOThresholdConst = 7.09782712893383973096e+02;
union { unsigned int w[2]; double f; } ExpInfConst = {{ 0x7FF00000, 0x00000000 }};
double ExpUThresholdConst = -7.45133219101941108420e+02;
double ExpInvLn2Const = 1.44269504088896338700e+00;
double ExpCvtConst = 4503601774854144.0; /* MWCC's (double)k magic, not in e_exp.c */
double ExpHugeConst = 1.0e+300;
double ExpOneConst = 1.0;
double ExpP5Const = 4.13813679705723846039e-08;
double ExpP4Const = -1.65339022054652515390e-06;
double ExpP3Const = 6.61375632143793436117e-05;
double ExpP2Const = -2.77777777770155933842e-03;
double ExpP1Const = 1.66666666666666019037e-01;
double ExpTwoConst = 2.0;
double ExpTwom1000Const = 9.33263618503218878990e-302;

asm double __ieee754_exp(double x)
{
    // clang-format off
    nofralloc
    stwu r1, -0x18(r1)
    fmr f8, f1
    fmr f0, f8
    stfd f0, 0x8(r1)
    lwz r9, 0x8(r1)
    lwz r10, 0xc(r1)
    mr r11, r9
    srwi r7, r11, 31
    lis r0, 0x4086
    clrlwi r11, r11, 1
    ori r0, r0, 0x2e41
    cmplw r11, r0
    ble L_803FF6B0
    lis r0, 0x7fef
    ori r0, r0, 0xffff
    cmplw r11, r0
    ble L_803FF688
    fmr f13, f8
    stfd f13, 0x8(r1)
    lwz r9, 0x8(r1)
    lwz r10, 0xc(r1)
    clrlwi r0, r11, 12
    or. r11, r10, r0
    beq L_803FF674
    fadd f1, f8, f8
    b L_803FF880
L_803FF674:
    cmpwi r7, 0x0
    lfd f1, ExpZeroConst.v
    bne L_803FF880
    fmr f1, f8
    b L_803FF880
L_803FF688:
    lfd f0, ExpOThresholdConst
    fcmpu cr0, f8, f0
    ble L_803FF69C
    lfd f1, ExpInfConst.f
    b L_803FF880
L_803FF69C:
    lfd f0, ExpUThresholdConst
    fcmpu cr0, f8, f0
    bge L_803FF6B0
    lfd f1, ExpZeroConst.v
    b L_803FF880
L_803FF6B0:
    lis r0, 0x3fd6
    ori r0, r0, 0x2e42
    cmplw r11, r0
    ble L_803FF754
    lis r0, 0x3ff0
    ori r0, r0, 0xa2b1
    cmplw r11, r0
    bgt L_803FF6F4
    slwi r10, r7, 3
    la r9, ExpLn2HiConst0
    lfdx f0, r9, r10
    la r11, ExpLn2LoConst0
    subfic r0, r7, 0x1
    lfdx f7, r11, r10
    fsub f10, f8, f0
    subf r8, r7, r0
    b L_803FF748
L_803FF6F4:
    slwi r0, r7, 3
    la r9, ExpHalfConst0
    lfdx f13, r9, r0
    lfd f0, ExpInvLn2Const
    mr r9, r11
    lis r10, 0x4330
    lfd f10, ExpCvtConst
    fmadd f0, f8, f0, f13
    lfd f11, ExpLn2LoConst0
    lfd f13, ExpLn2HiConst0
    fctiwz f12, f0
    stfd f12, 0x10(r1)
    lwz r8, 0x14(r1)
    xoris r0, r8, 0x8000
    stw r0, 0x14(r1)
    stw r10, 0x10(r1)
    lfd f9, 0x10(r1)
    fsub f9, f9, f10
    fmul f13, f9, f13
    fmul f7, f9, f11
    fsub f10, f8, f13
L_803FF748:
    fsub f8, f10, f7
    lfd f6, ExpOneConst
    b L_803FF78C
L_803FF754:
    lis r0, 0x3e2f
    ori r0, r0, 0xffff
    cmplw r11, r0
    bgt L_803FF784
    lfd f0, ExpHugeConst
    lfd f13, ExpOneConst
    fadd f0, f8, f0
    fcmpu cr0, f0, f13
    fmr f6, f13
    ble L_803FF78C
    fadd f1, f8, f6
    b L_803FF880
L_803FF784:
    lfd f6, ExpOneConst
    li r8, 0x0
L_803FF78C:
    fmul f9, f8, f8
    lfd f13, ExpP4Const
    lfd f0, ExpP5Const
    cmpwi r8, 0x0
    lfd f11, ExpP3Const
    fmadd f0, f9, f0, f13
    lfd f12, ExpP2Const
    lfd f13, ExpP1Const
    fmadd f0, f9, f0, f11
    fmadd f0, f9, f0, f12
    fmadd f0, f9, f0, f13
    fmul f0, f9, f0
    fsub f12, f8, f0
    bne L_803FF7E0
    lfd f0, ExpTwoConst
    fmul f1, f8, f12
    fsub f0, f12, f0
    fdiv f1, f1, f0
    fsub f1, f1, f8
    fsub f1, f6, f1
    b L_803FF880
L_803FF7E0:
    lfd f13, ExpTwoConst
    fmul f0, f8, f12
    cmpwi r8, -0x3fd
    fsub f13, f13, f12
    fdiv f0, f0, f13
    fsub f0, f7, f0
    fsub f0, f0, f10
    fsub f0, f6, f0
    bge L_803FF848
    fmr f13, f0
    addi r0, r8, 0x3e8
    stfd f13, 0x8(r1)
    slwi r0, r0, 20
    lfd f1, ExpTwom1000Const
    lwz r11, 0x8(r1)
    lwz r12, 0xc(r1)
    stfd f0, 0x8(r1)
    lwz r9, 0x8(r1)
    lwz r10, 0xc(r1)
    add r11, r9, r0
    stw r11, 0x8(r1)
    stw r12, 0xc(r1)
    lfd f13, 0x8(r1)
    fmr f0, f13
    fmul f1, f0, f1
    b L_803FF880
L_803FF848:
    fmr f13, f0
    slwi r0, r8, 20
    stfd f13, 0x8(r1)
    lwz r9, 0x8(r1)
    lwz r10, 0xc(r1)
    stfd f0, 0x8(r1)
    lwz r11, 0x8(r1)
    lwz r12, 0xc(r1)
    add r9, r11, r0
    stw r9, 0x8(r1)
    stw r10, 0xc(r1)
    lfd f13, 0x8(r1)
    fmr f0, f13
    fmr f1, f0
L_803FF880:
    addi r1, r1, 0x18
    blr
    // clang-format on
}
