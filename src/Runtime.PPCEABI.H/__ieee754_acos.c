struct { double v; } AcosZeroConst = {0.0};
double AcosPiConst = 3.14159265358979311600e+00;
double AcosPio2HiConst = 1.57079632679489655800e+00;
double AcosPS5Const = 3.47933107596021167570e-05;
double AcosPS4Const = 7.91534994289814532176e-04;
double AcosPS3Const = -4.00555345006794114027e-02;
double AcosPS2Const = 2.01212532134862925881e-01;
double AcosPS1Const = -3.25565818622400915405e-01;
double AcosPS0Const = 1.66666666666666657415e-01;
double AcosQS4Const = 7.70381505559019352791e-02;
double AcosQS3Const = -6.88283971605453293030e-01;
double AcosQS2Const = 2.02094576023350569471e+00;
double AcosQS1Const = -2.40339491173441421878e+00;
double AcosOneConst = 1.00000000000000000000e+00;
double AcosPio2LoConst = 6.12323399573676603587e-17;
double AcosHalfConst = 0.5;

extern double __ieee754_sqrt(double x);

asm double __ieee754_acos(double x)
{
    // clang-format off
    nofralloc
    stwu r1, -0x28(r1)
    mflr r0
    stfd f29, 0x10(r1)
    stfd f30, 0x18(r1)
    stfd f31, 0x20(r1)
    stw r0, 0x2c(r1)
    fmr f6, f1
    fmr f0, f6
    stfd f0, 0x8(r1)
    lwz r9, 0x8(r1)
    lwz r10, 0xc(r1)
    mr r8, r9
    clrlwi r11, r8, 1
    lis r0, 0x3fef
    ori r0, r0, 0xffff
    cmpw r11, r0
    ble L_8016C594
    fmr f13, f6
    stfd f13, 0x8(r1)
    lwz r9, 0x8(r1)
    lwz r10, 0xc(r1)
    addis r0, r11, -0x3ff0
    or. r11, r10, r0
    bne L_8016C588
    cmpwi r8, 0x0
    lfd f1, AcosZeroConst
    bgt L_8016C774
    lfd f1, AcosPiConst
    b L_8016C774
L_8016C588:
    fsub f1, f6, f6
    fdiv f1, f1, f1
    b L_8016C774
L_8016C594:
    lis r0, 0x3fdf
    ori r0, r0, 0xffff
    cmpw r11, r0
    bgt L_8016C630
    lis r0, 0x3c60
    cmpw r11, r0
    bgt L_8016C5B8
    lfd f1, AcosPio2HiConst
    b L_8016C774
L_8016C5B8:
    fmul f30, f6, f6
    lfd f13, AcosPS4Const
    lfd f0, AcosPS5Const
    lfd f12, AcosPS3Const
    fmadd f0, f30, f0, f13
    lfd f11, AcosPS2Const
    lfd f10, AcosQS3Const
    fmadd f0, f30, f0, f12
    lfd f13, AcosQS4Const
    lfd f12, AcosPS1Const
    fmadd f0, f30, f0, f11
    lfd f9, AcosQS2Const
    lfd f11, AcosQS1Const
    fmadd f13, f30, f13, f10
    lfd f8, AcosPS0Const
    lfd f10, AcosOneConst
    fmadd f0, f30, f0, f12
    lfd f1, AcosPio2LoConst
    lfd f12, AcosPio2HiConst
    fmadd f13, f30, f13, f9
    fmadd f0, f30, f0, f8
    fmadd f13, f30, f13, f11
    fmul f31, f30, f0
    fmadd f29, f30, f13, f10
    fdiv f11, f31, f29
    fmul f0, f6, f11
    fsub f1, f1, f0
    fsub f1, f6, f1
    fsub f1, f12, f1
    b L_8016C774
L_8016C630:
    cmpwi r8, 0x0
    blt L_8016C6EC
    lfd f31, AcosOneConst
    lfd f13, AcosHalfConst
    fsub f0, f31, f6
    fmul f30, f0, f13
    fmr f1, f30
    bl __ieee754_sqrt
    fmr f7, f1
    lfd f0, AcosPS4Const
    fmr f13, f7
    lfd f12, AcosPS5Const
    stfd f13, 0x8(r1)
    lfd f11, AcosPS3Const
    fmadd f12, f30, f12, f0
    lwz r9, 0x8(r1)
    lwz r10, 0xc(r1)
    li r10, 0x0
    lfd f0, AcosQS4Const
    stw r9, 0x8(r1)
    stw r10, 0xc(r1)
    fmadd f12, f30, f12, f11
    lfd f9, AcosPS2Const
    lfd f13, 0x8(r1)
    lfd f10, AcosQS2Const
    fmadd f12, f30, f12, f9
    lfd f8, AcosPS1Const
    fmr f1, f13
    lfd f11, AcosQS1Const
    lfd f13, AcosQS3Const
    fmadd f12, f30, f12, f8
    lfd f9, AcosPS0Const
    fmadd f0, f30, f0, f13
    fmadd f0, f30, f0, f10
    fmadd f0, f30, f0, f11
    fmadd f12, f30, f12, f9
    fmadd f29, f30, f0, f31
    fmul f13, f1, f1
    fmul f31, f30, f12
    fadd f0, f7, f1
    fsub f13, f30, f13
    fdiv f13, f13, f0
    fdiv f11, f31, f29
    fmadd f0, f11, f7, f13
    fadd f1, f1, f0
    fadd f1, f1, f1
    b L_8016C774
L_8016C6EC:
    lfd f7, AcosOneConst
    lfd f11, AcosHalfConst
    fadd f0, f6, f7
    lfd f12, AcosPS4Const
    fmul f30, f0, f11
    lfd f13, AcosPS5Const
    lfd f11, AcosPS3Const
    fmadd f13, f30, f13, f12
    lfd f10, AcosPS2Const
    lfd f0, AcosQS4Const
    fmadd f13, f30, f13, f11
    lfd f9, AcosQS3Const
    lfd f11, AcosQS2Const
    fmadd f13, f30, f13, f10
    lfd f8, AcosPS1Const
    lfd f10, AcosPS0Const
    fmadd f0, f30, f0, f9
    lfd f12, AcosQS1Const
    fmadd f0, f30, f0, f11
    fmadd f13, f30, f13, f8
    fmadd f0, f30, f0, f12
    fmadd f13, f30, f13, f10
    fmadd f29, f30, f0, f7
    fmul f31, f30, f13
    fmr f1, f30
    bl __ieee754_sqrt
    fdiv f11, f31, f29
    lfd f0, AcosPio2LoConst
    lfd f13, AcosPiConst
    fmr f7, f1
    fmsub f0, f11, f7, f0
    fadd f1, f7, f0
    fadd f1, f1, f1
    fsub f1, f13, f1
L_8016C774:
    lwz r0, 0x2c(r1)
    mtlr r0
    lfd f29, 0x10(r1)
    lfd f30, 0x18(r1)
    lfd f31, 0x20(r1)
    addi r1, r1, 0x28
    blr
    // clang-format on
}
