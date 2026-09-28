extern double lbl_8066BFA4;
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
    lfd f1, lbl_8066BFA4+0x4
    bgt L_8016C774
    lfd f1, lbl_8066BFA4+0xC
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
    lfd f1, lbl_8066BFA4+0x14
    b L_8016C774
L_8016C5B8:
    fmul f30, f6, f6
    lfd f13, lbl_8066BFA4+0x24
    lfd f0, lbl_8066BFA4+0x1C
    lfd f12, lbl_8066BFA4+0x2C
    fmadd f0, f30, f0, f13
    lfd f11, lbl_8066BFA4+0x34
    lfd f10, lbl_8066BFA4+0x54
    fmadd f0, f30, f0, f12
    lfd f13, lbl_8066BFA4+0x4C
    lfd f12, lbl_8066BFA4+0x3C
    fmadd f0, f30, f0, f11
    lfd f9, lbl_8066BFA4+0x5C
    lfd f11, lbl_8066BFA4+0x64
    fmadd f13, f30, f13, f10
    lfd f8, lbl_8066BFA4+0x44
    lfd f10, lbl_8066BFA4+0x6C
    fmadd f0, f30, f0, f12
    lfd f1, lbl_8066BFA4+0x74
    lfd f12, lbl_8066BFA4+0x14
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
    lfd f31, lbl_8066BFA4+0x6C
    lfd f13, lbl_8066BFA4+0x7C
    fsub f0, f31, f6
    fmul f30, f0, f13
    fmr f1, f30
    bl __ieee754_sqrt
    fmr f7, f1
    lfd f0, lbl_8066BFA4+0x24
    fmr f13, f7
    lfd f12, lbl_8066BFA4+0x1C
    stfd f13, 0x8(r1)
    lfd f11, lbl_8066BFA4+0x2C
    fmadd f12, f30, f12, f0
    lwz r9, 0x8(r1)
    lwz r10, 0xc(r1)
    li r10, 0x0
    lfd f0, lbl_8066BFA4+0x4C
    stw r9, 0x8(r1)
    stw r10, 0xc(r1)
    fmadd f12, f30, f12, f11
    lfd f9, lbl_8066BFA4+0x34
    lfd f13, 0x8(r1)
    lfd f10, lbl_8066BFA4+0x5C
    fmadd f12, f30, f12, f9
    lfd f8, lbl_8066BFA4+0x3C
    fmr f1, f13
    lfd f11, lbl_8066BFA4+0x64
    lfd f13, lbl_8066BFA4+0x54
    fmadd f12, f30, f12, f8
    lfd f9, lbl_8066BFA4+0x44
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
    lfd f7, lbl_8066BFA4+0x6C
    lfd f11, lbl_8066BFA4+0x7C
    fadd f0, f6, f7
    lfd f12, lbl_8066BFA4+0x24
    fmul f30, f0, f11
    lfd f13, lbl_8066BFA4+0x1C
    lfd f11, lbl_8066BFA4+0x2C
    fmadd f13, f30, f13, f12
    lfd f10, lbl_8066BFA4+0x34
    lfd f0, lbl_8066BFA4+0x4C
    fmadd f13, f30, f13, f11
    lfd f9, lbl_8066BFA4+0x54
    lfd f11, lbl_8066BFA4+0x5C
    fmadd f13, f30, f13, f10
    lfd f8, lbl_8066BFA4+0x3C
    lfd f10, lbl_8066BFA4+0x44
    fmadd f0, f30, f0, f9
    lfd f12, lbl_8066BFA4+0x64
    fmadd f0, f30, f0, f11
    fmadd f13, f30, f13, f8
    fmadd f0, f30, f0, f12
    fmadd f13, f30, f13, f10
    fmadd f29, f30, f0, f7
    fmul f31, f30, f13
    fmr f1, f30
    bl __ieee754_sqrt
    fdiv f11, f31, f29
    lfd f0, lbl_8066BFA4+0x74
    lfd f13, lbl_8066BFA4+0xC
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
