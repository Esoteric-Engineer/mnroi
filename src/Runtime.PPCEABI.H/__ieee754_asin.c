extern double lbl_8066CCC8;
extern double lbl_8066CCD0;
extern double lbl_8066CCD8;
extern double lbl_8066CCE0;
extern double lbl_8066CCE8;
extern double lbl_8066CCF0;
extern double lbl_8066CCF8;
extern double lbl_8066CD00;
extern double lbl_8066CD08;
extern double lbl_8066CD10;
extern double lbl_8066CD18;
extern double lbl_8066CD20;
extern double lbl_8066CD28;
extern double lbl_8066CD30;
extern double lbl_8066CD38;
extern double lbl_8066CD40;
extern double fabs(double x);
extern double __ieee754_sqrt(double x);

asm double __ieee754_asin(double x)
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
    fmr f7, f1
    fmr f0, f7
    stfd f0, 0x8(r1)
    lwz r9, 0x8(r1)
    lwz r10, 0xc(r1)
    mr r30, r9
    clrlwi r31, r30, 1
    lis r0, 0x3fef
    ori r0, r0, 0xffff
    cmpw r31, r0
    ble L_803FF430
    stfd f0, 0x8(r1)
    lwz r9, 0x8(r1)
    lwz r10, 0xc(r1)
    addis r0, r31, -0x3ff0
    or. r11, r10, r0
    bne L_803FF424
    lfd f1, lbl_8066CCD0
    lfd f0, lbl_8066CCC8
    fmul f1, f7, f1
    fmadd f1, f7, f0, f1
    b L_803FF5EC
L_803FF424:
    fsub f1, f7, f7
    fdiv f1, f1, f1
    b L_803FF5EC
L_803FF430:
    lis r0, 0x3fdf
    ori r0, r0, 0xffff
    cmpw r31, r0
    bgt L_803FF4D4
    lis r0, 0x3e3f
    ori r0, r0, 0xffff
    cmpw r31, r0
    bgt L_803FF470
    lfd f0, lbl_8066CCD8
    lfd f13, lbl_8066CCE0
    fadd f0, f7, f0
    fcmpu cr0, f0, f13
    fmr f6, f13
    ble L_803FF478
    fmr f1, f7
    b L_803FF5EC
L_803FF470:
    fmul f31, f7, f7
    lfd f6, lbl_8066CCE0
L_803FF478:
    lfd f13, lbl_8066CCF0
    lfd f0, lbl_8066CCE8
    lfd f12, lbl_8066CCF8
    fmadd f0, f31, f0, f13
    lfd f11, lbl_8066CD00
    lfd f13, lbl_8066CD18
    fmadd f0, f31, f0, f12
    lfd f10, lbl_8066CD20
    lfd f9, lbl_8066CD28
    fmadd f0, f31, f0, f11
    lfd f8, lbl_8066CD08
    lfd f11, lbl_8066CD10
    fmadd f13, f31, f13, f10
    lfd f12, lbl_8066CD30
    fmadd f13, f31, f13, f9
    fmadd f0, f31, f0, f8
    fmadd f13, f31, f13, f12
    fmadd f0, f31, f0, f11
    fmadd f29, f31, f13, f6
    fmul f30, f31, f0
    fdiv f9, f30, f29
    fmadd f1, f7, f9, f7
    b L_803FF5EC
L_803FF4D4:
    fmr f1, f7
    bl fabs
    lfd f7, lbl_8066CCE0
    lfd f12, lbl_8066CD38
    fsub f9, f7, f1
    lfd f0, lbl_8066CCF0
    fmul f31, f9, f12
    lfd f13, lbl_8066CCE8
    lfd f12, lbl_8066CCF8
    fmadd f13, f31, f13, f0
    lfd f11, lbl_8066CD00
    lfd f0, lbl_8066CD18
    fmadd f13, f31, f13, f12
    lfd f10, lbl_8066CD20
    lfd f8, lbl_8066CD08
    fmadd f13, f31, f13, f11
    lfd f9, lbl_8066CD28
    lfd f11, lbl_8066CD10
    fmadd f0, f31, f0, f10
    lfd f12, lbl_8066CD30
    fmadd f13, f31, f13, f8
    fmadd f0, f31, f0, f9
    fmadd f13, f31, f13, f11
    fmadd f0, f31, f0, f12
    fmul f30, f31, f13
    fmadd f29, f31, f0, f7
    fmr f1, f31
    bl __ieee754_sqrt
    lis r0, 0x3fef
    ori r0, r0, 0x3332
    cmpw r31, r0
    ble L_803FF574
    fdiv f9, f30, f29
    lfd f0, lbl_8066CCD0
    lfd f12, lbl_8066CCC8
    fmadd f13, f1, f9, f1
    fadd f13, f13, f13
    fsub f13, f13, f0
    fsub f31, f12, f13
    b L_803FF5D8
L_803FF574:
    stfd f1, 0x8(r1)
    lwz r11, 0x8(r1)
    lwz r12, 0xc(r1)
    mr r9, r11
    mr r10, r12
    li r10, 0x0
    stw r9, 0x8(r1)
    stw r10, 0xc(r1)
    lfd f0, 0x8(r1)
    fmr f9, f0
    fmul f0, f9, f9
    lfd f12, lbl_8066CCD0
    fsub f0, f31, f0
    lfd f10, lbl_8066CD40
    fadd f13, f1, f9
    fdiv f0, f0, f13
    fdiv f11, f30, f29
    fadd f0, f0, f0
    fsub f12, f12, f0
    fadd f13, f1, f1
    fmsub f30, f13, f11, f12
    fadd f0, f9, f9
    fsub f29, f10, f0
    fsub f13, f30, f29
    fsub f31, f10, f13
L_803FF5D8:
    cmpwi r30, 0x0
    bgt L_803FF5E8
    fneg f1, f31
    b L_803FF5EC
L_803FF5E8:
    fmr f1, f31
L_803FF5EC:
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
