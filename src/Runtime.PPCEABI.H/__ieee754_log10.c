/* fdlibm e_log10.c's literal pool, in MWCC's first-use order. */
#pragma section R ".rodata.1"
__declspec(section ".rodata.1") const union {
    unsigned long w[2];
    double d;
} Log10NegInfConst = {{0xFFF00000, 0x00000000}}; /* folded -two54/zero */
__declspec(section ".rodata.1") const double Log10ZeroConst = 0.0;
__declspec(section ".rodata.1") const double Log10Two54Const = 1.80143985094819840000e+16;
__declspec(section ".rodata.1") const double Log10CvtConst = 4503601774854144.0; /* MWCC's (double)k magic, not in e_log10.c */
__declspec(section ".rodata.1") const double Log10_2LoConst = 3.69423907715893078616e-13;
__declspec(section ".rodata.1") const double Log10Ivln10Const = 4.34294481903251816668e-01;
__declspec(section ".rodata.1") const double Log10_2HiConst = 3.01029995663611771306e-01;

extern double __ieee754_log(double x);

asm double __ieee754_log10(double x)
{
    // clang-format off
    nofralloc
    stwu    r1, -0x20(r1)
    mflr    r0
    stfd    f31, 0x18(r1)
    stw     r0, 0x24(r1)
    fmr     f0, f1
    stfd    f0, 8(r1)
    lwz     r9, 8(r1)
    lwz     r10, 0xc(r1)
    mr      r5, r9
    mr      r11, r10
    li      r8, 0
    lis     r0, 0xf
    ori     r0, r0, 0xffff
    cmpw    r5, r0
    bgt     L_pos
    clrlwi  r0, r5, 1
    or.     r9, r0, r11
    bne     L_nz
    lis     r9, Log10NegInfConst@ha
    lfd     f1, Log10NegInfConst@l(r9)
    b       L_end
L_nz:
    cmpwi   r5, 0
    bge     L_sub
    fsub    f0, f1, f1
    lis     r9, Log10ZeroConst@ha
    lfd     f1, Log10ZeroConst@l(r9)
    fdiv    f1, f0, f1
    b       L_end
L_sub:
    lis     r9, Log10Two54Const@ha
    li      r8, -0x36
    lfd     f0, Log10Two54Const@l(r9)
    fmul    f1, f1, f0
    fmr     f0, f1
    stfd    f0, 8(r1)
    lwz     r9, 8(r1)
    lwz     r10, 0xc(r1)
    mr      r5, r9
L_pos:
    lis     r0, 0x7fef
    ori     r0, r0, 0xffff
    cmpw    r5, r0
    bgt     L_inf
    srawi   r0, r5, 20
    subi    r9, r8, 0x3ff
    add     r8, r9, r0
    stfd    f1, 8(r1)
    srwi    r11, r8, 31
    add     r0, r8, r11
    lwz     r9, 8(r1)
    lwz     r10, 0xc(r1)
    subfic  r11, r11, 0x3ff
    xoris   r0, r0, 0x8000
    slwi    r11, r11, 20
    stw     r0, 0x14(r1)
    rlwimi  r5, r11, 0, 0, 11
    lis     r6, 0x4330
    mr      r9, r5
    stw     r6, 0x10(r1)
    stw     r9, 8(r1)
    stw     r10, 0xc(r1)
    lis     r8, Log10CvtConst@ha
    lfd     f0, Log10CvtConst@l(r8)
    lfd     f13, 8(r1)
    lfd     f31, 0x10(r1)
    fmr     f1, f13
    fsub    f31, f31, f0
    bl      __ieee754_log
    lis     r9, Log10Ivln10Const@ha
    lis     r11, Log10_2LoConst@ha
    lfd     f12, Log10Ivln10Const@l(r9)
    lis     r10, Log10_2HiConst@ha
    lfd     f0, Log10_2LoConst@l(r11)
    fmul    f1, f1, f12
    lfd     f13, Log10_2HiConst@l(r10)
    fmadd   f0, f31, f0, f1
    fmadd   f1, f31, f13, f0
    b       L_end
L_inf:
    fadd    f1, f1, f1
L_end:
    lwz     r0, 0x24(r1)
    mtlr    r0
    lfd     f31, 0x18(r1)
    addi    r1, r1, 0x20
    blr
    // clang-format on
}
