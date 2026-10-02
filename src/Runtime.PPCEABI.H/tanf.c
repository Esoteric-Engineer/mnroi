/* Shared with sinf.c: sf_sin.c/sf_tan.c's zero literals are contiguous in
 * .sdata (0x8066C178-0x8066C180) and only this unit's object starts
 * 8-aligned, so it owns the whole block; sinf.c externs. */
struct { float v; } SinfZeroConst = {0.0f};
struct { float v; } TanfZeroConst = {0.0f};
extern float __kernel_tanf(float x, float y, int iy);
extern int __ieee754_rem_pio2f(float x, float* y);

asm float tanf(float x)
{
    // clang-format off
    nofralloc
    stwu    r1, -0x18(r1)
    mflr    r0
    stw     r0, 0x1c(r1)
    lfs     f2, TanfZeroConst.v
    fmr     f0, f1
    stfs    f0, 0x10(r1)
    lwz     r9, 0x10(r1)
    clrlwi  r9, r9, 1
    lis     r0, 0x3f49
    ori     r0, r0, 0xfda
    cmpw    r9, r0
    bgt     L_gt
    li      r3, 1
    bl      __kernel_tanf
    b       L_end
L_gt:
    lis     r0, 0x7f7f
    ori     r0, r0, 0xffff
    cmpw    r9, r0
    bgt     L_nan
    addi    r3, r1, 8
    bl      __ieee754_rem_pio2f
    clrlslwi r3, r3, 31, 1
    lfs     f1, 8(r1)
    lfs     f2, 0xc(r1)
    subfic  r3, r3, 1
    bl      __kernel_tanf
    b       L_end
L_nan:
    fsubs   f1, f1, f1
L_end:
    lwz     r0, 0x1c(r1)
    mtlr    r0
    addi    r1, r1, 0x18
    blr
    // clang-format on
}
