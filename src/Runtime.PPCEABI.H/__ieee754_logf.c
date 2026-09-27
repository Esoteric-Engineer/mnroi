extern float lbl_8066CE48;
extern float lbl_8066CE4C;
extern float lbl_8066CE50;
extern float lbl_8066CE54;
extern double lbl_8066CE58;
extern float lbl_8066CE60;
extern float lbl_8066CE64;
extern float lbl_8066CE68;
extern float lbl_8066CE6C;
extern float lbl_8066CE70;
extern float lbl_8066CE74;
extern float lbl_8066CE78;
extern float lbl_8066CE7C;
extern float lbl_8066CE80;
extern float lbl_8066CE84;
extern float lbl_8066CE88;
extern float lbl_8066CE8C;

asm float __ieee754_logf(float x)
{
    // clang-format off
    nofralloc
    stwu r1, -0x18(r1)
    fmr f0, f1
    stfs f0, 0x8(r1)
    lwz r0, 0x8(r1)
    mr r8, r0
    li r7, 0x0
    lis r0, 0x7f
    ori r0, r0, 0xffff
    cmpw r8, r0
    bgt L_8040026C
    clrlwi. r0, r8, 1
    bne L_80400238
    lfs f1, lbl_8066CE48
    b L_80400478
L_80400238:
    cmpwi r8, 0x0
    bge L_80400250
    lfs f0, lbl_8066CE4C
    fsubs f1, f1, f1
    fdivs f1, f1, f0
    b L_80400478
L_80400250:
    lfs f0, lbl_8066CE50
    li r7, -0x19
    fmuls f1, f1, f0
    fmr f0, f1
    stfs f0, 0x8(r1)
    lwz r0, 0x8(r1)
    mr r8, r0
L_8040026C:
    lis r0, 0x7f7f
    ori r0, r0, 0xffff
    cmpw r8, r0
    ble L_80400284
    fadds f1, f1, f1
    b L_80400478
L_80400284:
    srawi r11, r8, 23
    subi r0, r7, 0x7f
    clrlwi r8, r8, 9
    add r7, r0, r11
    addis r9, r8, 0x4b
    subi r9, r9, 0x4e0
    rlwinm r11, r9, 0, 8, 8
    xoris r0, r11, 0x3f80
    or r0, r8, r0
    stw r0, 0x8(r1)
    lfs f1, 0x8(r1)
    srawi r9, r11, 23
    lfs f0, lbl_8066CE54
    addi r0, r8, 0xf
    clrlwi r0, r0, 9
    add r7, r7, r9
    fsubs f3, f1, f0
    cmpwi r0, 0xf
    bgt L_8040037C
    lfs f1, lbl_8066CE4C
    fcmpu cr0, f3, f1
    bne L_80400318
    cmpwi r7, 0x0
    beq L_80400478
    xoris r0, r7, 0x8000
    stw r0, 0x14(r1)
    lis r11, 0x4330
    lfd f13, lbl_8066CE58
    stw r11, 0x10(r1)
    lfs f1, lbl_8066CE64
    lfd f0, 0x10(r1)
    lfs f12, lbl_8066CE60
    fsub f0, f0, f13
    frsp f11, f0
    fmuls f1, f11, f1
    fmadds f1, f11, f12, f1
    b L_80400478
L_80400318:
    lfs f0, lbl_8066CE68
    fmuls f12, f3, f3
    lfs f13, lbl_8066CE6C
    cmpwi r7, 0x0
    fmuls f0, f3, f0
    fsubs f13, f13, f0
    fmuls f9, f12, f13
    bne L_80400340
    fsubs f1, f3, f9
    b L_80400478
L_80400340:
    xoris r0, r7, 0x8000
    stw r0, 0x14(r1)
    lis r11, 0x4330
    lfd f13, lbl_8066CE58
    stw r11, 0x10(r1)
    lfs f1, lbl_8066CE64
    lfd f0, 0x10(r1)
    lfs f12, lbl_8066CE60
    fsub f0, f0, f13
    frsp f11, f0
    fmuls f1, f11, f1
    fsubs f1, f9, f1
    fsubs f1, f1, f3
    fmsubs f1, f11, f12, f1
    b L_80400478
L_8040037C:
    lfs f0, lbl_8066CE70
    xoris r0, r7, 0x8000
    lis r10, 0x4330
    fadds f0, f3, f0
    stw r0, 0x14(r1)
    fdivs f2, f3, f0
    lfs f11, lbl_8066CE80
    lfs f4, lbl_8066CE84
    lis r0, 0x35
    stw r10, 0x10(r1)
    subis r11, r8, 0x31
    lfs f5, lbl_8066CE88
    ori r0, r0, 0xc288
    lfs f10, lbl_8066CE74
    subf r0, r8, r0
    lfs f6, lbl_8066CE78
    addi r11, r11, 0x5c30
    lfs f7, lbl_8066CE8C
    or. r10, r11, r0
    lfd f9, lbl_8066CE58
    lfd f12, 0x10(r1)
    lfs f8, lbl_8066CE7C
    fmuls f13, f2, f2
    fmuls f0, f13, f13
    fmadds f11, f0, f11, f4
    fmadds f11, f0, f11, f5
    fmadds f11, f0, f11, f7
    fmadds f10, f0, f10, f6
    fmuls f13, f13, f11
    fsub f12, f12, f9
    fmadds f10, f0, f10, f8
    fmadds f9, f0, f10, f13
    frsp f11, f12
    ble L_80400444
    lfs f0, lbl_8066CE6C
    cmpwi r7, 0x0
    fmuls f0, f3, f0
    fmuls f10, f0, f3
    bne L_80400428
    fadds f1, f10, f9
    fmuls f1, f2, f1
    fsubs f1, f10, f1
    b L_80400474
L_80400428:
    lfs f0, lbl_8066CE64
    fadds f1, f10, f9
    lfs f13, lbl_8066CE60
    fmuls f0, f11, f0
    fmadds f1, f2, f1, f0
    fsubs f1, f10, f1
    b L_80400460
L_80400444:
    cmpwi r7, 0x0
    beq L_8040046C
    lfs f0, lbl_8066CE64
    fsubs f1, f3, f9
    lfs f13, lbl_8066CE60
    fmuls f0, f11, f0
    fmsubs f1, f2, f1, f0
L_80400460:
    fsubs f1, f1, f3
    fmsubs f1, f11, f13, f1
    b L_80400478
L_8040046C:
    fsubs f1, f3, f9
    fmuls f1, f2, f1
L_80400474:
    fsubs f1, f3, f1
L_80400478:
    addi r1, r1, 0x18
    blr
    // clang-format on
}
