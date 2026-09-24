extern float lbl_8066C058;
extern float lbl_8066C05C;
extern float lbl_8066C060;
extern float lbl_8066C064;
extern float lbl_8066C068;
extern float lbl_8066C06C;
extern float lbl_8066C070;
extern float lbl_8066C074;
extern float lbl_8066C078;
extern float lbl_8066C07C;
extern float lbl_8066C080;
extern float lbl_8066C084;
extern float lbl_8066C088;
extern float lbl_8066C08C;
extern float lbl_8066C090;
extern float lbl_8066C094;
extern float lbl_8066C098;
extern float lbl_8066C09C;
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
    lfs     f1, lbl_8066C058
    bgt     L_8016D048
    lfs     f1, lbl_8066C05C
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
    lfs     f1, lbl_8066C060
    b       L_8016D048
L_8016CE98:
    lfs     f0, lbl_8066C068
    fmuls   f30, f6, f6
    lfs     f13, lbl_8066C064
    lfs     f12, lbl_8066C06C
    fmadds  f13, f30, f13, f0
    lfs     f11, lbl_8066C070
    fmadds  f13, f30, f13, f12
    lfs     f10, lbl_8066C080
    lfs     f12, lbl_8066C074
    fmadds  f13, f30, f13, f11
    lfs     f0, lbl_8066C07C
    lfs     f9, lbl_8066C084
    fmadds  f13, f30, f13, f12
    fmadds  f0, f30, f0, f10
    lfs     f11, lbl_8066C088
    lfs     f8, lbl_8066C078
    fmadds  f0, f30, f0, f9
    lfs     f12, lbl_8066C08C
    fmadds  f0, f30, f0, f11
    fmadds  f13, f30, f13, f8
    lfs     f1, lbl_8066C090
    fmadds  f29, f30, f0, f12
    lfs     f11, lbl_8066C094
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
    lfs     f31, lbl_8066C08C
    lfs     f13, lbl_8066C098
    fsubs   f0, f31, f6
    fmuls   f30, f0, f13
    fmr     f1, f30
    bl      __ieee754_sqrtf
    fmr     f6, f1
    lfs     f0, lbl_8066C068
    fmr     f12, f6
    lfs     f13, lbl_8066C064
    stfs    f12, 0x8(r1)
    lfs     f11, lbl_8066C06C
    fmadds  f13, f30, f13, f0
    lwz     r0, 0x8(r1)
    lfs     f0, lbl_8066C07C
    fmadds  f13, f30, f13, f11
    clrrwi  r9, r0, 12
    lfs     f9, lbl_8066C080
    lfs     f12, lbl_8066C070
    stw     r9, 0x8(r1)
    fmadds  f0, f30, f0, f9
    lfs     f7, lbl_8066C084
    fmadds  f13, f30, f13, f12
    lfs     f8, lbl_8066C074
    lfs     f11, lbl_8066C088
    fmadds  f0, f30, f0, f7
    lfs     f1, 0x8(r1)
    fmadds  f13, f30, f13, f8
    lfs     f10, lbl_8066C078
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
    lfs     f7, lbl_8066C08C
    lfs     f12, lbl_8066C098
    fadds   f0, f6, f7
    lfs     f11, lbl_8066C068
    lfs     f13, lbl_8066C064
    fmuls   f30, f0, f12
    lfs     f10, lbl_8066C06C
    fmr     f1, f30
    fmadds  f13, f30, f13, f11
    lfs     f12, lbl_8066C070
    fmadds  f13, f30, f13, f10
    lfs     f0, lbl_8066C07C
    lfs     f11, lbl_8066C080
    fmadds  f13, f30, f13, f12
    lfs     f10, lbl_8066C074
    lfs     f8, lbl_8066C084
    fmadds  f0, f30, f0, f11
    lfs     f9, lbl_8066C078
    fmadds  f13, f30, f13, f10
    lfs     f12, lbl_8066C088
    fmadds  f0, f30, f0, f8
    fmadds  f13, f30, f13, f9
    fmadds  f0, f30, f0, f12
    fmadds  f29, f30, f0, f7
    fmuls   f31, f30, f13
    bl      __ieee754_sqrtf
    fdivs   f10, f31, f29
    lfs     f0, lbl_8066C090
    lfs     f13, lbl_8066C09C
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
