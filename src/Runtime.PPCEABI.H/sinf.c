extern struct { float v; } SinfZeroConst;
extern float __kernel_cosf(float x, float y);
extern float __kernel_sinf(float x, float y, int iy);
extern int __ieee754_rem_pio2f(float x, float* y);

asm float sinf(float x)
{
    // clang-format off
    nofralloc
    stwu    r1, -0x18(r1)
    mflr    r0
    stw     r0, 0x1c(r1)
    lfs     f2, SinfZeroConst.v
    fmr     f0, f1
    stfs    f0, 0x10(r1)
    lwz     r9, 0x10(r1)
    clrlwi  r9, r9, 1
    lis     r0, 0x3f49
    ori     r0, r0, 0xfd8
    cmpw    r9, r0
    bgt     L_gt
    li      r3, 0
    bl      __kernel_sinf
    b       L_end
L_gt:
    lis     r0, 0x7f7f
    ori     r0, r0, 0xffff
    cmpw    r9, r0
    ble     L_fin
    fsubs   f1, f1, f1
    b       L_end
L_fin:
    addi    r3, r1, 8
    bl      __ieee754_rem_pio2f
    clrlwi  r3, r3, 30
    cmpwi   r3, 1
    beq     L_n1
    bgt     L_gt1
    cmpwi   r3, 0
    beq     L_n0
    b       L_n3
L_gt1:
    cmpwi   r3, 2
    beq     L_n2
    b       L_n3
L_n0:
    lfs     f1, 8(r1)
    li      r3, 1
    lfs     f2, 0xc(r1)
    bl      __kernel_sinf
    b       L_end
L_n1:
    lfs     f1, 8(r1)
    lfs     f2, 0xc(r1)
    bl      __kernel_cosf
    b       L_end
L_n2:
    lfs     f1, 8(r1)
    li      r3, 1
    lfs     f2, 0xc(r1)
    bl      __kernel_sinf
    b       L_neg
L_n3:
    lfs     f1, 8(r1)
    lfs     f2, 0xc(r1)
    bl      __kernel_cosf
L_neg:
    fneg    f1, f1
L_end:
    lwz     r0, 0x1c(r1)
    mtlr    r0
    addi    r1, r1, 0x18
    blr
    // clang-format on
}
