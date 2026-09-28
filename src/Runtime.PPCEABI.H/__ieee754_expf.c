extern float lbl_8066CE00;
extern float lbl_8066CE04;
extern float lbl_8066CE08;
extern float lbl_8066CE0C;
extern float lbl_8066CE10;
extern float lbl_8066CE20;
extern float lbl_8066CE24;
extern float lbl_8066CE28;
extern float lbl_8066CE2C;
extern float lbl_8066CE30;
extern float lbl_8066CE34;
extern float lbl_8066CE38;
extern float lbl_8066CE3C;
extern float lbl_8066CE40;
extern double lbl_8066CE18;
extern const char lbl_80670868[4];
extern const char lbl_80670870[4];
extern const char lbl_80670878[4];

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
    lfs f1, lbl_8066CE00
    bne L_80400030
    fmr f1, f8
    b L_80400030
L_803FFE6C:
    lfs f0, lbl_8066CE04
    fcmpu cr0, f8, f0
    ble L_803FFE80
    lfs f1, lbl_8066CE08
    b L_80400030
L_803FFE80:
    lfs f0, lbl_8066CE0C
    fcmpu cr0, f8, f0
    bge L_803FFE94
    lfs f1, lbl_8066CE00
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
    la r9, lbl_80670870
    la r11, lbl_80670878
    lfsx f0, r9, r10
    subfic r0, r8, 0x1
    lfsx f10, r11, r10
    fsubs f7, f8, f0
    subf r11, r8, r0
    b L_803FFF30
L_803FFED8:
    slwi r0, r8, 2
    la r9, lbl_80670868
    lfsx f13, r9, r0
    lfs f0, lbl_8066CE10
    mr r9, r11
    lis r10, 0x4330
    lfd f11, lbl_8066CE18
    fmadds f0, f8, f0, f13
    lfs f10, -0x2c68(r13)
    lfs f13, -0x2c70(r13)
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
    lfs f6, lbl_8066CE24
    b L_803FFF74
L_803FFF3C:
    lis r0, 0x317f
    ori r0, r0, 0xffff
    cmplw r9, r0
    bgt L_803FFF6C
    lfs f0, lbl_8066CE20
    lfs f13, lbl_8066CE24
    fadds f0, f8, f0
    fcmpu cr0, f0, f13
    fmr f6, f13
    ble L_803FFF74
    fadds f1, f8, f6
    b L_80400030
L_803FFF6C:
    lfs f6, lbl_8066CE24
    li r11, 0x0
L_803FFF74:
    lfs f13, lbl_8066CE2C
    fmuls f9, f8, f8
    lfs f0, lbl_8066CE28
    cmpwi r11, 0x0
    lfs f12, lbl_8066CE30
    fmadds f0, f9, f0, f13
    lfs f11, lbl_8066CE34
    fmadds f0, f9, f0, f12
    lfs f13, lbl_8066CE38
    fmadds f0, f9, f0, f11
    fmadds f0, f9, f0, f13
    fmuls f0, f9, f0
    fsubs f12, f8, f0
    bne L_803FFFC8
    lfs f0, lbl_8066CE3C
    fmuls f1, f8, f12
    fsubs f0, f12, f0
    fdivs f1, f1, f0
    fsubs f1, f1, f8
    fsubs f1, f6, f1
    b L_80400030
L_803FFFC8:
    lfs f13, lbl_8066CE3C
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
    lfs f1, lbl_8066CE40
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
