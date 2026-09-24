extern double lbl_8066C210;
extern double lbl_8066C218;
extern double lbl_8066C220;
extern double lbl_8066C228;
extern double lbl_8066C230;
extern double lbl_8066C238;
extern double lbl_8066C240;
extern double lbl_8066C248;
extern double lbl_8066C250;
extern double lbl_8066C258;
extern double lbl_8066C260;
extern double fabs(double x);
extern int __kernel_rem_pio2(double* x, double* y, int e0, int nx, int prec, const int* ipio2);

asm int __ieee754_rem_pio2(double x, double* y)
{
    // clang-format off
    nofralloc
    stwu    r1, -0x48(r1)
    mflr    r0
    stmw    r29, 0x3c(r1)
    stw     r0, 0x4c(r1)
    mr      r30, r3
    fmr     f0, f1
    stfd    f0, 0x20(r1)
    lwz     r9, 0x20(r1)
    lwz     r10, 0x24(r1)
    mr      r29, r9
    clrlwi  r31, r29, 1
    lis     r0, 0x3fe9
    ori     r0, r0, 0x21fb
    cmpw    r31, r0
    bgt     L_8016E1E4
    lfd     f0, lbl_8066C210
    li      r3, 0x0
    stfd    f1, 0x0(r30)
    b       L_8016E4E4
L_8016E1E4:
    lis     r0, 0x4002
    ori     r0, r0, 0xd97b
    cmpw    r31, r0
    bgt     L_8016E28C
    cmpwi   r29, 0x0
    ble     L_8016E244
    lfd     f0, lbl_8066C218
    lis     r0, 0x3ff9
    ori     r0, r0, 0x21fb
    fsub    f11, f1, f0
    cmpw    r31, r0
    beq     L_8016E21C
    lfd     f12, lbl_8066C220
    b       L_8016E228
L_8016E21C:
    lfd     f0, lbl_8066C228
    lfd     f12, lbl_8066C230
    fsub    f11, f11, f0
L_8016E228:
    fsub    f13, f11, f12
    fsub    f0, f11, f13
    stfd    f13, 0x0(r30)
    fsub    f0, f0, f12
    stfd    f0, 0x8(r30)
    li      r3, 0x1
    b       L_8016E4E8
L_8016E244:
    lfd     f0, lbl_8066C218
    lis     r0, 0x3ff9
    ori     r0, r0, 0x21fb
    fadd    f11, f1, f0
    cmpw    r31, r0
    beq     L_8016E264
    lfd     f12, lbl_8066C220
    b       L_8016E270
L_8016E264:
    lfd     f0, lbl_8066C228
    lfd     f12, lbl_8066C230
    fadd    f11, f11, f0
L_8016E270:
    fadd    f13, f11, f12
    fsub    f0, f11, f13
    stfd    f13, 0x0(r30)
    fadd    f0, f0, f12
    stfd    f0, 0x8(r30)
    li      r3, -0x1
    b       L_8016E4E8
L_8016E28C:
    lis     r0, 0x4139
    ori     r0, r0, 0x21fb
    cmpw    r31, r0
    bgt     L_8016E3D4
    bl      fabs
    lfd     f13, lbl_8066C240
    fmr     f9, f1
    lfd     f0, lbl_8066C238
    mr      r9, r11
    lis     r10, 0x4330
    fmadd   f0, f9, f0, f13
    lfd     f11, lbl_8066C248
    lfd     f13, lbl_8066C218
    fctiwz  f12, f0
    stfd    f12, 0x30(r1)
    lfd     f0, lbl_8066C220
    lwz     r3, 0x34(r1)
    xoris   r0, r3, 0x8000
    cmpwi   r3, 0x1f
    stw     r0, 0x34(r1)
    stw     r10, 0x30(r1)
    lfd     f10, 0x30(r1)
    fsub    f10, f10, f11
    fmul    f13, f10, f13
    fmul    f1, f10, f0
    fsub    f11, f9, f13
    bgt     L_8016E31C
    subi    r0, r3, 0x1
    subi    r11, r13, 0x3750
    slwi    r0, r0, 2
    lwzx    r9, r11, r0
    cmpw    r31, r9
    beq     L_8016E31C
    fsub    f0, f11, f1
    stfd    f0, 0x0(r30)
    b       L_8016E3B0
L_8016E31C:
    fsub    f0, f11, f1
    srawi   r8, r31, 20
    stfd    f0, 0x0(r30)
    stfd    f0, 0x20(r1)
    lwz     r9, 0x20(r1)
    lwz     r10, 0x24(r1)
    extrwi  r9, r9, 11, 1
    subf    r0, r9, r8
    cmpwi   r0, 0x10
    ble     L_8016E3B0
    lfd     f0, lbl_8066C228
    fmr     f9, f11
    lfd     f12, lbl_8066C230
    fmul    f1, f10, f0
    fsub    f11, f11, f1
    fsub    f0, f9, f11
    fsub    f0, f0, f1
    fmsub   f1, f10, f12, f0
    fsub    f13, f11, f1
    stfd    f13, 0x0(r30)
    stfd    f13, 0x20(r1)
    lwz     r9, 0x20(r1)
    lwz     r10, 0x24(r1)
    extrwi  r9, r9, 11, 1
    subf    r0, r9, r8
    cmpwi   r0, 0x31
    ble     L_8016E3B0
    lfd     f0, lbl_8066C250
    fmr     f9, f11
    lfd     f12, lbl_8066C258
    fmul    f1, f10, f0
    fsub    f11, f11, f1
    fsub    f0, f9, f11
    fsub    f0, f0, f1
    fmsub   f1, f10, f12, f0
    fsub    f13, f11, f1
    stfd    f13, 0x0(r30)
L_8016E3B0:
    lfd     f13, 0x0(r30)
    cmpwi   r29, 0x0
    fsub    f0, f11, f13
    fsub    f0, f0, f1
    stfd    f0, 0x8(r30)
    bge     L_8016E4E8
    fneg    f13, f13
    neg     r3, r3
    b       L_8016E4DC
L_8016E3D4:
    lis     r0, 0x7fef
    ori     r0, r0, 0xffff
    cmpw    r31, r0
    ble     L_8016E3F4
    fsub    f0, f1, f1
    li      r3, 0x0
    stfd    f0, 0x0(r30)
    b       L_8016E4E4
L_8016E3F4:
    stfd    f1, 0x20(r1)
    lwz     r11, 0x20(r1)
    lwz     r12, 0x24(r1)
    stfd    f11, 0x20(r1)
    mr      r10, r12
    srawi   r8, r31, 20
    subi    r5, r8, 0x416
    slwi    r0, r5, 20
    subf    r9, r0, r31
    stw     r9, 0x20(r1)
    stw     r10, 0x24(r1)
    lfd     f0, 0x20(r1)
    fmr     f11, f0
    cmpwi   r29, 0x0
    addi    r7, r1, 0x8
    lfd     f12, lbl_8066C248
    lfd     f13, lbl_8066C260
    mfcr    r31
    addi    r0, r7, 0x8
    lis     r8, 0x4330
    mr      r10, r7
L_8016E448:
    fctiwz  f0, f11
    stfd    f0, 0x30(r1)
    mr      r11, r9
    lwz     r9, 0x34(r1)
    xoris   r9, r9, 0x8000
    stw     r9, 0x34(r1)
    stw     r8, 0x30(r1)
    lfd     f0, 0x30(r1)
    fsub    f0, f0, f12
    stfd    f0, 0x0(r10)
    fsub    f0, f11, f0
    addi    r10, r10, 0x8
    fmul    f11, f0, f13
    cmpw    r10, r0
    ble     L_8016E448
    stfd    f11, 0x18(r1)
    li      r6, 0x3
    lfd     f13, lbl_8066C210
    lfd     f0, 0x10(r7)
    fcmpu   cr0, f0, f13
    bne     L_8016E4B0
    addi    r9, r7, 0x10
L_8016E4A0:
    lfdu    f0, -0x8(r9)
    subi    r6, r6, 0x1
    fcmpu   cr0, f0, f13
    beq     L_8016E4A0
L_8016E4B0:
    addi    r3, r1, 0x8
    mr      r4, r30
    li      r7, 0x2
    subi    r8, r13, 0x3858
    bl      __kernel_rem_pio2
    mtcrf   128, r31
    bge     L_8016E4E8
    lfd     f13, 0x0(r30)
    neg     r3, r3
    lfd     f0, 0x8(r30)
    fneg    f13, f13
L_8016E4DC:
    fneg    f0, f0
    stfd    f13, 0x0(r30)
L_8016E4E4:
    stfd    f0, 0x8(r30)
L_8016E4E8:
    lwz     r0, 0x4c(r1)
    mtlr    r0
    lmw     r29, 0x3c(r1)
    addi    r1, r1, 0x48
    blr
    // clang-format on
}
