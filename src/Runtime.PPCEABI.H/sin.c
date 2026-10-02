struct { double v; } SinZeroConst = {0.0};

extern double __kernel_cos(double x, double y);
extern double __kernel_sin(double x, double y, int iy);
extern int __ieee754_rem_pio2(double x, double* y);

asm double sin(double x)
{
    // clang-format off
    nofralloc
    stwu    r1, -0x20(r1)
    mflr    r0
    stw     r0, 0x24(r1)
    lfd     f2, SinZeroConst.v
    fmr     f0, f1
    stfd    f0, 0x18(r1)
    lwz     r9, 0x18(r1)
    lwz     r10, 0x1c(r1)
    clrlwi  r9, r9, 1
    lis     r0, 0x3fe9
    ori     r0, r0, 0x21fb
    cmpw    r9, r0
    bgt     L_8016CD78
    li      r3, 0x0
    bl      __kernel_sin
    b       L_8016CE08
L_8016CD78:
    lis     r0, 0x7fef
    ori     r0, r0, 0xffff
    cmpw    r9, r0
    ble     L_8016CD90
    fsub    f1, f1, f1
    b       L_8016CE08
L_8016CD90:
    addi    r3, r1, 0x8
    bl      __ieee754_rem_pio2
    clrlwi  r3, r3, 30
    cmpwi   r3, 0x1
    beq     L_8016CDD4
    bgt     L_8016CDB4
    cmpwi   r3, 0x0
    beq     L_8016CDC0
    b       L_8016CDF8
L_8016CDB4:
    cmpwi   r3, 0x2
    beq     L_8016CDE4
    b       L_8016CDF8
L_8016CDC0:
    lfd     f1, 0x8(r1)
    li      r3, 0x1
    lfd     f2, 0x10(r1)
    bl      __kernel_sin
    b       L_8016CE08
L_8016CDD4:
    lfd     f1, 0x8(r1)
    lfd     f2, 0x10(r1)
    bl      __kernel_cos
    b       L_8016CE08
L_8016CDE4:
    lfd     f1, 0x8(r1)
    li      r3, 0x1
    lfd     f2, 0x10(r1)
    bl      __kernel_sin
    b       L_8016CE04
L_8016CDF8:
    lfd     f1, 0x8(r1)
    lfd     f2, 0x10(r1)
    bl      __kernel_cos
L_8016CE04:
    fneg    f1, f1
L_8016CE08:
    lwz     r0, 0x24(r1)
    mtlr    r0
    addi    r1, r1, 0x20
    blr
    // clang-format on
}
