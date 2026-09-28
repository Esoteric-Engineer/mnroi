union { unsigned long w; float f; } LogfNegInfConst = {0xFF800000}; /* folded -two25/zero */
struct { float v; } LogfZeroConst = {0.0f};    /* 0x00000000 zero */
float LogfTwo25Const = 3.3554432000e+07f;      /* 0x4c000000 two25 */
float LogfOneConst = 1.0000000000e+00f;        /* 0x3f800000 one */
double LogfCvtConst = 4503601774854144.0;      /* MWCC's (float)k magic */
float LogfLn2HiConst = 6.9313812256e-01f;      /* 0x3f317180 ln2_hi */
float LogfLn2LoConst = 9.0580006145e-06f;      /* 0x3717f7d1 ln2_lo */
float LogfOneThirdConst = 3.3333334327e-01f;   /* 0x3eaaaaab 1/3 */
float LogfHalfConst = 5.0000000000e-01f;       /* 0x3f000000 half */
float LogfTwoConst = 2.0000000000e+00f;        /* 0x40000000 two */
float LogfLg6Const = 1.5313838422e-01f;        /* 0x3e1cd04f Lg6 */
float LogfLg4Const = 2.2222198546e-01f;        /* 0x3e638e29 Lg4 */
float LogfLg2Const = 4.0000000596e-01f;        /* 0x3ecccccd Lg2 */
float LogfLg7Const = 1.4798198640e-01f;        /* 0x3e178897 Lg7 */
float LogfLg5Const = 1.8183572590e-01f;        /* 0x3e3a3325 Lg5 */
float LogfLg3Const = 2.8571429849e-01f;        /* 0x3e924925 Lg3 */
float LogfLg1Const = 6.6666668653e-01f;        /* 0x3f2aaaab Lg1 */

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
    lfs f1, LogfNegInfConst.f
    b L_80400478
L_80400238:
    cmpwi r8, 0x0
    bge L_80400250
    lfs f0, LogfZeroConst.v
    fsubs f1, f1, f1
    fdivs f1, f1, f0
    b L_80400478
L_80400250:
    lfs f0, LogfTwo25Const
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
    lfs f0, LogfOneConst
    addi r0, r8, 0xf
    clrlwi r0, r0, 9
    add r7, r7, r9
    fsubs f3, f1, f0
    cmpwi r0, 0xf
    bgt L_8040037C
    lfs f1, LogfZeroConst.v
    fcmpu cr0, f3, f1
    bne L_80400318
    cmpwi r7, 0x0
    beq L_80400478
    xoris r0, r7, 0x8000
    stw r0, 0x14(r1)
    lis r11, 0x4330
    lfd f13, LogfCvtConst
    stw r11, 0x10(r1)
    lfs f1, LogfLn2LoConst
    lfd f0, 0x10(r1)
    lfs f12, LogfLn2HiConst
    fsub f0, f0, f13
    frsp f11, f0
    fmuls f1, f11, f1
    fmadds f1, f11, f12, f1
    b L_80400478
L_80400318:
    lfs f0, LogfOneThirdConst
    fmuls f12, f3, f3
    lfs f13, LogfHalfConst
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
    lfd f13, LogfCvtConst
    stw r11, 0x10(r1)
    lfs f1, LogfLn2LoConst
    lfd f0, 0x10(r1)
    lfs f12, LogfLn2HiConst
    fsub f0, f0, f13
    frsp f11, f0
    fmuls f1, f11, f1
    fsubs f1, f9, f1
    fsubs f1, f1, f3
    fmsubs f1, f11, f12, f1
    b L_80400478
L_8040037C:
    lfs f0, LogfTwoConst
    xoris r0, r7, 0x8000
    lis r10, 0x4330
    fadds f0, f3, f0
    stw r0, 0x14(r1)
    fdivs f2, f3, f0
    lfs f11, LogfLg7Const
    lfs f4, LogfLg5Const
    lis r0, 0x35
    stw r10, 0x10(r1)
    subis r11, r8, 0x31
    lfs f5, LogfLg3Const
    ori r0, r0, 0xc288
    lfs f10, LogfLg6Const
    subf r0, r8, r0
    lfs f6, LogfLg4Const
    addi r11, r11, 0x5c30
    lfs f7, LogfLg1Const
    or. r10, r11, r0
    lfd f9, LogfCvtConst
    lfd f12, 0x10(r1)
    lfs f8, LogfLg2Const
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
    lfs f0, LogfHalfConst
    cmpwi r7, 0x0
    fmuls f0, f3, f0
    fmuls f10, f0, f3
    bne L_80400428
    fadds f1, f10, f9
    fmuls f1, f2, f1
    fsubs f1, f10, f1
    b L_80400474
L_80400428:
    lfs f0, LogfLn2LoConst
    fadds f1, f10, f9
    lfs f13, LogfLn2HiConst
    fmuls f0, f11, f0
    fmadds f1, f2, f1, f0
    fsubs f1, f10, f1
    b L_80400460
L_80400444:
    cmpwi r7, 0x0
    beq L_8040046C
    lfs f0, LogfLn2LoConst
    fsubs f1, f3, f9
    lfs f13, LogfLn2HiConst
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
