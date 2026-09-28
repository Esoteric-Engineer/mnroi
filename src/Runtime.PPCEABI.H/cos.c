extern double lbl_8066BFA4;

extern double __kernel_cos(double x, double y);
extern double __kernel_sin(double x, double y, int iy);
extern int __ieee754_rem_pio2(double x, double* y);

asm double cos(double x)
{
    // clang-format off
    nofralloc
    stwu    r1, -0x20(r1)
    mflr    r0
    stw     r0, 0x24(r1)
    lfd     f2, lbl_8066BFA4+0x94
    fmr     f0, f1
    stfd    f0, 0x18(r1)
    lwz     r9, 0x18(r1)
    lwz     r10, 0x1c(r1)
    clrlwi  r9, r9, 1
    lis     r0, 0x3fe9
    ori     r0, r0, 0x21fb
    cmpw    r9, r0
    bgt     L_8016CB38
    bl      __kernel_cos
    b       L_8016CBCC
L_8016CB38:
    lis     r0, 0x7fef
    ori     r0, r0, 0xffff
    cmpw    r9, r0
    ble     L_8016CB50
    fsub    f1, f1, f1
    b       L_8016CBCC
L_8016CB50:
    addi    r3, r1, 0x8
    bl      __ieee754_rem_pio2
    clrlwi  r3, r3, 30
    cmpwi   r3, 0x1
    beq     L_8016CB90
    bgt     L_8016CB74
    cmpwi   r3, 0x0
    beq     L_8016CB80
    b       L_8016CBBC
L_8016CB74:
    cmpwi   r3, 0x2
    beq     L_8016CBA8
    b       L_8016CBBC
L_8016CB80:
    lfd     f1, 0x8(r1)
    lfd     f2, 0x10(r1)
    bl      __kernel_cos
    b       L_8016CBCC
L_8016CB90:
    lfd     f1, 0x8(r1)
    li      r3, 0x1
    lfd     f2, 0x10(r1)
    bl      __kernel_sin
    fneg    f1, f1
    b       L_8016CBCC
L_8016CBA8:
    lfd     f1, 0x8(r1)
    lfd     f2, 0x10(r1)
    bl      __kernel_cos
    fneg    f1, f1
    b       L_8016CBCC
L_8016CBBC:
    lfd     f1, 0x8(r1)
    li      r3, 0x1
    lfd     f2, 0x10(r1)
    bl      __kernel_sin
L_8016CBCC:
    lwz     r0, 0x24(r1)
    mtlr    r0
    addi    r1, r1, 0x20
    blr
    // clang-format on
}
