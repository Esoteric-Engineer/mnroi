extern double lbl_8066CD48;
extern double lbl_8066CD50;
extern double lbl_8066CD58;
extern double lbl_8066CD60;
extern double lbl_8066CD68;
extern double lbl_8066CD70;
extern double lbl_8066CD78;
extern double lbl_8066CD80;
extern double lbl_8066CD88;
extern double lbl_8066CD90;
extern double lbl_8066CD98;
extern double lbl_8066CDA0;
extern double lbl_8066CDA8;
extern double lbl_8066CDB0;
extern double lbl_8066CDB8;
extern const char lbl_80670828[4];
extern const char lbl_80670838[4];
extern const char lbl_80670848[4];

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
    lfd f1, lbl_8066CD48
    bne L_803FF880
    fmr f1, f8
    b L_803FF880
L_803FF688:
    lfd f0, lbl_8066CD50
    fcmpu cr0, f8, f0
    ble L_803FF69C
    lfd f1, lbl_8066CD58
    b L_803FF880
L_803FF69C:
    lfd f0, lbl_8066CD60
    fcmpu cr0, f8, f0
    bge L_803FF6B0
    lfd f1, lbl_8066CD48
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
    la r9, lbl_80670838
    lfdx f0, r9, r10
    la r11, lbl_80670848
    subfic r0, r7, 0x1
    lfdx f7, r11, r10
    fsub f10, f8, f0
    subf r8, r7, r0
    b L_803FF748
L_803FF6F4:
    slwi r0, r7, 3
    la r9, lbl_80670828
    lfdx f13, r9, r0
    lfd f0, lbl_8066CD68
    mr r9, r11
    lis r10, 0x4330
    lfd f10, lbl_8066CD70
    fmadd f0, f8, f0, f13
    lfd f11, -0x2c98(r13)
    lfd f13, -0x2ca8(r13)
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
    lfd f6, lbl_8066CD80
    b L_803FF78C
L_803FF754:
    lis r0, 0x3e2f
    ori r0, r0, 0xffff
    cmplw r11, r0
    bgt L_803FF784
    lfd f0, lbl_8066CD78
    lfd f13, lbl_8066CD80
    fadd f0, f8, f0
    fcmpu cr0, f0, f13
    fmr f6, f13
    ble L_803FF78C
    fadd f1, f8, f6
    b L_803FF880
L_803FF784:
    lfd f6, lbl_8066CD80
    li r8, 0x0
L_803FF78C:
    fmul f9, f8, f8
    lfd f13, lbl_8066CD90
    lfd f0, lbl_8066CD88
    cmpwi r8, 0x0
    lfd f11, lbl_8066CD98
    fmadd f0, f9, f0, f13
    lfd f12, lbl_8066CDA0
    lfd f13, lbl_8066CDA8
    fmadd f0, f9, f0, f11
    fmadd f0, f9, f0, f12
    fmadd f0, f9, f0, f13
    fmul f0, f9, f0
    fsub f12, f8, f0
    bne L_803FF7E0
    lfd f0, lbl_8066CDB0
    fmul f1, f8, f12
    fsub f0, f12, f0
    fdiv f1, f1, f0
    fsub f1, f1, f8
    fsub f1, f6, f1
    b L_803FF880
L_803FF7E0:
    lfd f13, lbl_8066CDB0
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
    lfd f1, lbl_8066CDB8
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
