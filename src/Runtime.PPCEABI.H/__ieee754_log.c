/* fdlibm e_log.c's literal pool, in MWCC's first-use order. */
#pragma section R ".rodata.1"
__declspec(section ".rodata.1") const union {
    unsigned long w[2];
    double d;
} LogNegInfConst = {{0xFFF00000, 0x00000000}}; /* folded -two54/zero */
__declspec(section ".rodata.1") const double LogZeroConst = 0.0;
__declspec(section ".rodata.1") const double LogTwo54Const = 1.80143985094819840000e+16;
__declspec(section ".rodata.1") const double LogOneConst = 1.0;
__declspec(section ".rodata.1") const double LogCvtConst = 4503601774854144.0; /* MWCC's (double)k magic, not in e_log.c */
__declspec(section ".rodata.1") const double LogLn2HiConst = 6.93147180369123816490e-01;
__declspec(section ".rodata.1") const double LogLn2LoConst = 1.90821492927058770002e-10;
__declspec(section ".rodata.1") const double LogThirdConst = 3.33333333333333315e-01;
__declspec(section ".rodata.1") const double LogHalfConst = 0.5;
__declspec(section ".rodata.1") const double LogTwoConst = 2.0;
__declspec(section ".rodata.1") const double LogLg6Const = 1.531383769920937332e-01;
__declspec(section ".rodata.1") const double LogLg4Const = 2.222219843214978396e-01;
__declspec(section ".rodata.1") const double LogLg2Const = 3.999999999940941908e-01;
__declspec(section ".rodata.1") const double LogLg7Const = 1.479819860511658591e-01;
__declspec(section ".rodata.1") const double LogLg5Const = 1.818357216161805012e-01;
__declspec(section ".rodata.1") const double LogLg3Const = 2.857142874366239149e-01;
__declspec(section ".rodata.1") const double LogLg1Const = 6.666666666666735130e-01;

asm double __ieee754_log(double x)
{
    // clang-format off
    nofralloc
    stwu    r1, -0x18(r1)
    fmr     f0, f1
    stfd    f0, 0x8(r1)
    lwz     r9, 0x8(r1)
    lwz     r10, 0xc(r1)
    mr      r5, r9
    mr      r11, r10
    li      r4, 0x0
    lis     r0, 0xf
    ori     r0, r0, 0xffff
    cmpw    r5, r0
    bgt     L_8017793C
    clrlwi  r0, r5, 1
    or.     r9, r0, r11
    bne     L_801778FC
    lis     r9, LogNegInfConst@ha
    lfd     f1, LogNegInfConst@l(r9)
    b       L_80177BA8
L_801778FC:
    cmpwi   r5, 0x0
    bge     L_80177918
    fsub    f0, f1, f1
    lis     r9, LogZeroConst@ha
    lfd     f1, LogZeroConst@l(r9)
    fdiv    f1, f0, f1
    b       L_80177BA8
L_80177918:
    lis     r9, LogTwo54Const@ha
    li      r4, -0x36
    lfd     f0, LogTwo54Const@l(r9)
    fmul    f1, f1, f0
    fmr     f0, f1
    stfd    f0, 0x8(r1)
    lwz     r9, 0x8(r1)
    lwz     r10, 0xc(r1)
    mr      r5, r9
L_8017793C:
    lis     r0, 0x7fef
    ori     r0, r0, 0xffff
    cmpw    r5, r0
    ble     L_80177954
    fadd    f1, f1, f1
    b       L_80177BA8
L_80177954:
    srawi   r9, r5, 20
    subi    r0, r4, 0x3ff
    clrlwi  r5, r5, 12
    add     r4, r0, r9
    addis   r11, r5, 0x9
    addi    r11, r11, 0x5f64
    rlwinm  r11, r11, 0, 11, 11
    stfd    f1, 0x8(r1)
    lwz     r9, 0x8(r1)
    lwz     r10, 0xc(r1)
    xoris   r0, r11, 0x3ff0
    or      r9, r5, r0
    stw     r9, 0x8(r1)
    stw     r10, 0xc(r1)
    lfd     f0, 0x8(r1)
    fmr     f1, f0
    srawi   r11, r11, 20
    lis     r9, LogOneConst@ha
    addi    r0, r5, 0x2
    lfd     f0, LogOneConst@l(r9)
    clrlwi  r0, r0, 12
    add     r4, r4, r11
    cmpwi   r0, 0x2
    fsub    f3, f1, f0
    bgt     L_80177A78
    lis     r9, LogZeroConst@ha
    lfd     f1, LogZeroConst@l(r9)
    fcmpu   cr0, f3, f1
    bne     L_80177A0C
    cmpwi   r4, 0x0
    beq     L_80177BA8
    xoris   r0, r4, 0x8000
    stw     r0, 0x14(r1)
    lis     r11, 0x4330
    lis     r10, LogCvtConst@ha
    lis     r8, LogLn2LoConst@ha
    stw     r11, 0x10(r1)
    lis     r7, LogLn2HiConst@ha
    lfd     f13, LogCvtConst@l(r10)
    lfd     f4, 0x10(r1)
    lfd     f1, LogLn2LoConst@l(r8)
    fsub    f4, f4, f13
    lfd     f0, LogLn2HiConst@l(r7)
    fmul    f1, f4, f1
    fmadd   f1, f4, f0, f1
    b       L_80177BA8
L_80177A0C:
    lis     r9, LogThirdConst@ha
    lis     r11, LogHalfConst@ha
    lfd     f13, LogThirdConst@l(r9)
    fmul    f12, f3, f3
    lfd     f0, LogHalfConst@l(r11)
    cmpwi   r4, 0x0
    fmul    f13, f3, f13
    fsub    f0, f0, f13
    fmul    f12, f12, f0
    bne     L_80177A3C
    fsub    f1, f3, f12
    b       L_80177BA8
L_80177A3C:
    xoris   r0, r4, 0x8000
    stw     r0, 0x14(r1)
    lis     r11, 0x4330
    lis     r10, LogCvtConst@ha
    lis     r8, LogLn2LoConst@ha
    stw     r11, 0x10(r1)
    lis     r7, LogLn2HiConst@ha
    lfd     f0, LogCvtConst@l(r10)
    lfd     f4, 0x10(r1)
    lfd     f1, LogLn2LoConst@l(r8)
    fsub    f4, f4, f0
    lfd     f13, LogLn2HiConst@l(r7)
    fmul    f1, f4, f1
    fsub    f1, f12, f1
    b       L_80177B90
L_80177A78:
    lis     r9, LogTwoConst@ha
    lis     r11, LogLg7Const@ha
    lfd     f0, LogTwoConst@l(r9)
    lis     r10, LogLg5Const@ha
    lfd     f12, LogLg7Const@l(r11)
    lis     r9, LogLg3Const@ha
    fadd    f0, f3, f0
    lfd     f5, LogLg5Const@l(r10)
    fdiv    f2, f3, f0
    lfd     f6, LogLg3Const@l(r9)
    xoris   r0, r4, 0x8000
    lis     r9, LogLg6Const@ha
    lis     r10, LogLg4Const@ha
    lis     r7, LogLg1Const@ha
    stw     r0, 0x14(r1)
    lfd     f11, LogLg6Const@l(r9)
    lis     r8, 0x4330
    lfd     f7, LogLg4Const@l(r10)
    lis     r9, LogLg2Const@ha
    lfd     f8, LogLg1Const@l(r7)
    lis     r6, LogCvtConst@ha
    stw     r8, 0x10(r1)
    lis     r0, 0x6
    lfd     f9, LogLg2Const@l(r9)
    addis   r10, r5, -0x6
    lfd     f4, 0x10(r1)
    ori     r0, r0, 0xb851
    lfd     f10, LogCvtConst@l(r6)
    subf    r0, r5, r0
    subi    r11, r10, 0x147a
    or.     r9, r11, r0
    fmul    f13, f2, f2
    fmul    f0, f13, f13
    fmadd   f12, f0, f12, f5
    fmadd   f12, f0, f12, f6
    fmadd   f11, f0, f11, f7
    fmadd   f12, f0, f12, f8
    fmadd   f11, f0, f11, f9
    fmul    f13, f13, f12
    fsub    f4, f4, f10
    fmadd   f12, f0, f11, f13
    ble     L_80177B6C
    lis     r9, LogHalfConst@ha
    cmpwi   r4, 0x0
    lfd     f0, LogHalfConst@l(r9)
    fmul    f0, f3, f0
    fmul    f11, f0, f3
    bne     L_80177B48
    fadd    f1, f11, f12
    fmul    f1, f2, f1
    fsub    f1, f11, f1
    b       L_80177BA4
L_80177B48:
    lis     r11, LogLn2LoConst@ha
    fadd    f1, f11, f12
    lfd     f0, LogLn2LoConst@l(r11)
    lis     r9, LogLn2HiConst@ha
    lfd     f13, LogLn2HiConst@l(r9)
    fmul    f0, f4, f0
    fmadd   f1, f2, f1, f0
    fsub    f1, f11, f1
    b       L_80177B90
L_80177B6C:
    cmpwi   r4, 0x0
    beq     L_80177B9C
    lis     r11, LogLn2LoConst@ha
    fsub    f1, f3, f12
    lfd     f0, LogLn2LoConst@l(r11)
    lis     r9, LogLn2HiConst@ha
    lfd     f13, LogLn2HiConst@l(r9)
    fmul    f0, f4, f0
    fmsub   f1, f2, f1, f0
L_80177B90:
    fsub    f1, f1, f3
    fmsub   f1, f4, f13, f1
    b       L_80177BA8
L_80177B9C:
    fsub    f1, f3, f12
    fmul    f1, f2, f1
L_80177BA4:
    fsub    f1, f3, f1
L_80177BA8:
    addi    r1, r1, 0x18
    blr
    // clang-format on
}
