extern float lbl_8066C2C8;
extern float lbl_8066C2CC;
extern float lbl_8066C2D0;
extern float lbl_8066C2D4;
extern float lbl_8066C2D8;
extern float lbl_8066C2DC;
extern float lbl_8066C2E0;
extern double lbl_8066C2E8;
extern float lbl_8066C2F0;
extern float lbl_8066C2F4;
extern float lbl_8066C2F8;
extern const char lbl_8067015C[4];
extern const char lbl_8066FE44[4];
extern float fabsf(float x);
extern int __kernel_rem_pio2f(float* x, float* y, int e0, int nx, int prec, const char* ipio2);

asm int __ieee754_rem_pio2f(float x, float* y)
{
    // clang-format off
    nofralloc
    stwu    r1, -0x40(r1)
    mflr    r0
    stmw    r29, 0x34(r1)
    stw     r0, 0x44(r1)
    mr      r31, r3
    fmr     f0, f1
    stfs    f0, 0x18(r1)
    lwz     r29, 0x18(r1)
    clrlwi  r30, r29, 1
    lis     r0, 0x3f49
    ori     r0, r0, 0xfd8
    cmpw    r30, r0
    bgt     L_reduce
    lfs     f0, lbl_8066C2C8
    li      r3, 0
    stfs    f1, 0(r31)
    b       L_ret_y1
L_reduce:
    lis     r0, 0x4016
    ori     r0, r0, 0xcbe3
    cmpw    r30, r0
    bgt     L_medium
    cmpwi   r29, 0
    ble     L_neg
    lfs     f0, lbl_8066C2CC
    lis     r0, 0x3fc9
    rlwinm  r9, r29, 0, 1, 27
    ori     r0, r0, 0xfd0
    fsubs   f1, f1, f0
    cmpw    r9, r0
    beq     L_pos_near
    lfs     f12, lbl_8066C2D0
    b       L_pos_fin
L_pos_near:
    lfs     f0, lbl_8066C2D4
    lfs     f12, lbl_8066C2D8
    fsubs   f1, f1, f0
L_pos_fin:
    fsubs   f13, f1, f12
    fsubs   f0, f1, f13
    stfs    f13, 0(r31)
    fsubs   f0, f0, f12
    stfs    f0, 4(r31)
    li      r3, 1
    b       L_end
L_neg:
    lfs     f0, lbl_8066C2CC
    lis     r0, 0x3fc9
    rlwinm  r9, r29, 0, 1, 27
    ori     r0, r0, 0xfd0
    fadds   f1, f1, f0
    cmpw    r9, r0
    beq     L_neg_near
    lfs     f12, lbl_8066C2D0
    b       L_neg_fin
L_neg_near:
    lfs     f0, lbl_8066C2D4
    lfs     f12, lbl_8066C2D8
    fadds   f1, f1, f0
L_neg_fin:
    fadds   f13, f1, f12
    fsubs   f0, f1, f13
    stfs    f13, 0(r31)
    fadds   f0, f0, f12
    stfs    f0, 4(r31)
    li      r3, -1
    b       L_end
L_medium:
    lis     r0, 0x4349
    ori     r0, r0, 0xf80
    cmpw    r30, r0
    bgt     L_large
    bl      fabsf
    lfs     f13, lbl_8066C2E0
    fmr     f9, f1
    lfs     f0, lbl_8066C2DC
    mr      r9, r11
    lis     r10, 0x4330
    fmadds  f0, f9, f0, f13
    lfd     f11, lbl_8066C2E8
    lfs     f13, lbl_8066C2CC
    fctiwz  f12, f0
    lfs     f10, lbl_8066C2D0
    stfd    f12, 0x28(r1)
    lwz     r3, 0x2c(r1)
    xoris   r0, r3, 0x8000
    cmpwi   r3, 0x1f
    stw     r0, 0x2c(r1)
    stw     r10, 0x28(r1)
    lfd     f0, 0x28(r1)
    fsub    f0, f0, f11
    frsp    f8, f0
    fmuls   f13, f8, f13
    fsubs   f11, f9, f13
    fmuls   f1, f8, f10
    bgt     L_iter1
    subi    r0, r3, 1
    la      r10, lbl_8067015C
    slwi    r0, r0, 2
    rlwinm  r11, r29, 0, 1, 23
    lwzx    r9, r10, r0
    cmpw    r11, r9
    beq     L_iter1
    fsubs   f0, f11, f1
    stfs    f0, 0(r31)
    b       L_med_fin
L_iter1:
    fsubs   f0, f11, f1
    srawi   r9, r30, 23
    stfs    f0, 0(r31)
    stfs    f0, 0x18(r1)
    lwz     r0, 0x18(r1)
    extrwi  r0, r0, 8, 1
    subf    r0, r0, r9
    cmpwi   r0, 8
    ble     L_med_fin
    lfs     f0, lbl_8066C2D4
    fmr     f9, f11
    lfs     f12, lbl_8066C2D8
    fmuls   f1, f8, f0
    fsubs   f11, f11, f1
    fsubs   f0, f9, f11
    fsubs   f0, f0, f1
    fmsubs  f1, f8, f12, f0
    fsubs   f13, f11, f1
    stfs    f13, 0(r31)
    stfs    f13, 0x18(r1)
    lwz     r0, 0x18(r1)
    extrwi  r0, r0, 8, 1
    subf    r0, r0, r9
    cmpwi   r0, 0x19
    ble     L_med_fin
    lfs     f0, lbl_8066C2F0
    fmr     f9, f11
    lfs     f12, lbl_8066C2F4
    fmuls   f1, f8, f0
    fsubs   f11, f11, f1
    fsubs   f0, f9, f11
    fsubs   f0, f0, f1
    fmsubs  f1, f8, f12, f0
    fsubs   f13, f11, f1
    stfs    f13, 0(r31)
L_med_fin:
    lfs     f13, 0(r31)
    cmpwi   r29, 0
    fsubs   f0, f11, f13
    fsubs   f0, f0, f1
    stfs    f0, 4(r31)
    bge     L_end
    fneg    f13, f13
    neg     r3, r3
    b       L_negate
L_large:
    lis     r0, 0x7f7f
    ori     r0, r0, 0xffff
    cmpw    r30, r0
    ble     L_finite
    fsubs   f0, f1, f1
    li      r3, 0
    stfs    f0, 0(r31)
    b       L_ret_y1
L_finite:
    srawi   r9, r30, 23
    subi    r5, r9, 0x86
    slwi    r0, r5, 23
    subf    r30, r0, r30
    stw     r30, 0x18(r1)
    lfs     f1, 0x18(r1)
    cmpwi   r29, 0
    addi    r8, r1, 8
    lfd     f12, lbl_8066C2E8
    lfs     f11, lbl_8066C2F8
    mfcr    r30
    lis     r7, 0x4330
    mr      r10, r8
    addi    r0, r1, 0xc
L_loop:
    fmr     f0, f1
    fctiwz  f13, f0
    mr      r11, r9
    stfd    f13, 0x28(r1)
    lwz     r9, 0x2c(r1)
    xoris   r9, r9, 0x8000
    stw     r9, 0x2c(r1)
    stw     r7, 0x28(r1)
    lfd     f0, 0x28(r1)
    fsub    f0, f0, f12
    frsp    f0, f0
    stfs    f0, 0(r10)
    fsubs   f0, f1, f0
    addi    r10, r10, 4
    fmuls   f1, f0, f11
    cmpw    r10, r0
    ble     L_loop
    stfs    f1, 0x10(r1)
    li      r6, 3
    lfs     f13, lbl_8066C2C8
    lfs     f0, 8(r8)
    fcmpu   cr0, f0, f13
    bne     L_call
    addi    r9, r8, 8
L_skip:
    lfsu    f0, -4(r9)
    subi    r6, r6, 1
    fcmpu   cr0, f0, f13
    beq     L_skip
L_call:
    addi    r3, r1, 8
    mr      r4, r31
    li      r7, 2
    la      r8, lbl_8066FE44
    bl      __kernel_rem_pio2f
    mtcrf   128, r30
    bge     L_end
    lfs     f13, 0(r31)
    neg     r3, r3
    lfs     f0, 4(r31)
    fneg    f13, f13
L_negate:
    fneg    f0, f0
    stfs    f13, 0(r31)
L_ret_y1:
    stfs    f0, 4(r31)
L_end:
    lwz     r0, 0x44(r1)
    mtlr    r0
    lmw     r29, 0x34(r1)
    addi    r1, r1, 0x40
    blr
    // clang-format on
}
