#pragma force_active on
float PowfOneConst = 1.0f;                  /* 0x3f800000 */
struct { float v; } PowfZeroConst = {0.0f}; /* 0x00000000 */
union { unsigned long w; float f; } PowfOflowConst = {0x7F800000}; /* +inf, folded huge*huge */
float PowfQuarterConst = 0.25f;             /* 0x3e800000, inline (float)0.25 literal */
float PowfL3Const = 0.3333333432674408f;    /* 0x3eaaaaab, doubles as the inline 0.333333333333f literal */
float PowfHalfConst = 0.5f;                 /* 0x3f000000, inline (float)0.5 literal */
float PowfIvln2HiConst = 1.44268798828125f; /* 0x3fb8aa00 */
float PowfIvln2LoConst = 7.052607543300837e-06f; /* 0x36eca570 */
float PowfIvln2Const = 1.4426950216293335f; /* 0x3fb8aa3b */
float PowfTwo24Const = 16777216.0f;         /* 0x4b800000 */
float PowfL6Const = 0.20697501301765442f;   /* 0x3e53f142 */
float PowfL5Const = 0.23066075146198273f;   /* 0x3e6c3255 */
float PowfL4Const = 0.2727281153202057f;    /* 0x3e8ba305 */
float PowfL2Const = 0.4285714328289032f;    /* 0x3edb6db7 */
float PowfL1Const = 0.6000000238418579f;    /* 0x3f19999a */
float PowfThreeConst = 3.0f;                /* 0x40400000, inline (float)3.0 literal */
float PowfCpHiConst = 0.9617919921875f;     /* 0x3f763800 */
float PowfCpLoConst = 4.701738362200558e-06f; /* 0x369dc3a0 */
float PowfCpConst = 0.9617967009544373f;    /* 0x3f76384f */
double PowfCvtConst = 4503601774854144.0;   /* 0x4330000080000000, MWCC's (float)n magic, not in ef_pow.c */
float PowfNegOneConst = -1.0f;              /* 0xbf800000 */
float PowfHugeConst = 1.0000000150474662e+30f; /* 0x7149f2ca */
float PowfOvtConst = 4.299566569443414e-08f;   /* 0x3338aa3c */
float PowfTinyConst = 1.0000000031710769e-30f; /* 0x0da24260 */
float PowfLg2HiConst = 0.693145751953125f;  /* 0x3f317200 */
float PowfLg2Const = 0.6931471824645996f;   /* 0x3f317218 */
float PowfLg2LoConst = 1.4286065379565116e-06f; /* 0x35bfbe8c */
float PowfP5Const = 4.138136944220605e-08f;    /* 0x3331bb4c */
float PowfP4Const = -1.6533901998627698e-06f;  /* 0xb5ddea0e */
float PowfP3Const = 6.61375597701408e-05f;     /* 0x388ab355 */
float PowfP2Const = -0.0027777778450399637f;   /* 0xbb360b61 */
float PowfP1Const = 0.1666666716337204f;       /* 0x3e2aaaab */
float PowfTwoConst = 2.0f;                  /* 0x40000000 */
/* bp[2]/dp_h[2]/dp_l[2], split into scalars so `la` gets an sda21 reloc instead of MWCC pre-resolving the array as far data. */
const float PowfBp0Const = 1.0f;
const float PowfBp1Const = 1.5f;
const float PowfDpHi0Const = 0.0f;
const float PowfDpHi1Const = 0.5849609375f;
const float PowfDpLo0Const = 0.0f;
const float PowfDpLo1Const = 1.5632208487659227e-06f;
extern float __ieee754_sqrtf(float x);
extern float fabsf(float x);
extern float scalbnf(float x, int n);

asm float __ieee754_powf(float x, float y)
{
    // clang-format off
    nofralloc
    stwu r1, -0x40(r1)
    mflr r0
    mfcr r12
    stfd f30, 0x30(r1)
    stfd f31, 0x38(r1)
    stmw r27, 0x1c(r1)
    stw r0, 0x44(r1)
    stw r12, 0x18(r1)
    fmr f30, f2
    fmr f31, f1
    fmr f0, f31
    stfs f0, 0x8(r1)
    lwz r28, 0x8(r1)
    fmr f12, f30
    stfs f12, 0x8(r1)
    lwz r29, 0x8(r1)
    clrlwi r31, r28, 1
    clrlwi. r30, r29, 1
    bne L_8016D2D8
    lfs f1, PowfOneConst
    b L_8016D954
L_8016D2D8:
    lis r0, 0x7f80
    cmpw r31, r0
    bgt L_8016D2EC
    cmpw r30, r0
    ble L_8016D2F4
L_8016D2EC:
    fadds f1, f31, f30
    b L_8016D954
L_8016D2F4:
    li r27, 0x0
    cmpwi cr4, r28, 0x0
    bge cr4, L_8016D348
    lis r0, 0x4b7f
    ori r0, r0, 0xffff
    cmpw r30, r0
    ble L_8016D318
    li r27, 0x2
    b L_8016D348
L_8016D318:
    lis r0, 0x3f7f
    ori r0, r0, 0xffff
    cmpw r30, r0
    ble L_8016D348
    srawi r0, r30, 23
    subfic r0, r0, 0x96
    sraw r10, r30, r0
    slw r0, r10, r0
    cmpw r0, r30
    bne L_8016D348
    clrlwi r0, r10, 31
    subfic r27, r0, 0x2
L_8016D348:
    lis r0, 0x7f80
    cmpw r30, r0
    bne L_8016D394
    lis r0, 0x3f80
    cmpw r31, r0
    bne L_8016D368
    fsubs f1, f30, f30
    b L_8016D954
L_8016D368:
    ble L_8016D380
    cmpwi r29, 0x0
    lfs f1, PowfZeroConst.v
    blt L_8016D954
    fmr f1, f30
    b L_8016D954
L_8016D380:
    cmpwi r29, 0x0
    lfs f1, PowfZeroConst.v
    bge L_8016D954
    fneg f1, f30
    b L_8016D954
L_8016D394:
    lis r0, 0x3f80
    cmpw r30, r0
    bne L_8016D3BC
    cmpwi r29, 0x0
    bge L_8016D3B4
    lfs f1, PowfOneConst
    fdivs f1, f1, f31
    b L_8016D954
L_8016D3B4:
    fmr f1, f31
    b L_8016D954
L_8016D3BC:
    lis r0, 0x4000
    cmpw r29, r0
    bne L_8016D3D0
    fmuls f1, f31, f31
    b L_8016D954
L_8016D3D0:
    lis r0, 0x3f00
    cmpw r29, r0
    bne L_8016D3EC
    blt cr4, L_8016D3EC
    fmr f1, f31
    bl __ieee754_sqrtf
    b L_8016D954
L_8016D3EC:
    fmr f1, f31
    bl fabsf
    lis r0, 0x7f80
    cmpw r31, r0
    beq L_8016D414
    cmpwi r31, 0x0
    beq L_8016D414
    lis r0, 0x3f80
    cmpw r31, r0
    bne L_8016D458
L_8016D414:
    fmr f2, f1
    cmpwi r29, 0x0
    bge L_8016D428
    lfs f0, PowfOneConst
    fdivs f2, f0, f2
L_8016D428:
    bge cr4, L_8016D450
    addis r0, r31, -0x3f80
    or. r9, r0, r27
    bne L_8016D444
    fsubs f0, f2, f2
    fdivs f2, f0, f0
    b L_8016D450
L_8016D444:
    cmpwi r27, 0x1
    bne L_8016D450
    fneg f2, f2
L_8016D450:
    fmr f1, f2
    b L_8016D954
L_8016D458:
    srwi r9, r28, 31
    mr r6, r9
    subi r9, r9, 0x1
    or. r10, r9, r27
    bne L_8016D478
    fsubs f1, f31, f31
    fdivs f1, f1, f1
    b L_8016D954
L_8016D478:
    lis r0, 0x4d00
    cmpw r30, r0
    ble L_8016D538
    lis r0, 0x3f7f
    ori r0, r0, 0xfff7
    cmpw r31, r0
    bgt L_8016D4A8
    cmpwi r29, 0x0
    lfs f1, PowfZeroConst.v
    bge L_8016D954
    lfs f1, PowfOflowConst.f
    b L_8016D954
L_8016D4A8:
    lis r0, 0x3f80
    ori r0, r0, 0x7
    cmpw r31, r0
    ble L_8016D4CC
    cmpwi r29, 0x0
    lfs f1, PowfZeroConst.v
    ble L_8016D954
    lfs f1, PowfOflowConst.f
    b L_8016D954
L_8016D4CC:
    lfs f9, PowfOneConst
    lfs f13, PowfQuarterConst
    fsubs f1, f31, f9
    lfs f0, PowfL3Const
    fmuls f13, f1, f13
    lfs f12, PowfHalfConst
    fsubs f0, f0, f13
    lfs f11, PowfIvln2Const
    fmuls f0, f1, f0
    lfs f10, PowfIvln2HiConst
    fsubs f12, f12, f0
    lfs f13, PowfIvln2LoConst
    fmuls f0, f1, f1
    fmuls f0, f0, f12
    fmuls f11, f0, f11
    fmsubs f4, f1, f13, f11
    fmuls f5, f1, f10
    fadds f0, f5, f4
    stfs f0, 0x8(r1)
    lwz r0, 0x8(r1)
    clrrwi r11, r0, 12
    stw r11, 0x8(r1)
    lfs f12, 0x8(r1)
    fsubs f0, f12, f5
    fsubs f0, f4, f0
    fmr f7, f9
    b L_8016D744
L_8016D538:
    lis r0, 0x7f
    li r3, 0x0
    ori r0, r0, 0xffff
    cmpw r31, r0
    bgt L_8016D564
    lfs f0, PowfTwo24Const
    li r3, -0x18
    fmuls f1, f1, f0
    stfs f1, 0x8(r1)
    lwz r0, 0x8(r1)
    mr r31, r0
L_8016D564:
    lis r0, 0x1c
    srawi r9, r31, 23
    clrlwi r10, r31, 9
    subi r11, r3, 0x7f
    ori r0, r0, 0xc471
    add r3, r11, r9
    cmpw r10, r0
    oris r31, r10, 0x3f80
    bgt L_8016D590
    li r7, 0x0
    b L_8016D5B0
L_8016D590:
    lis r0, 0x5d
    li r7, 0x1
    ori r0, r0, 0xb3d6
    cmpw r10, r0
    ble L_8016D5B0
    li r7, 0x0
    addi r3, r3, 0x1
    addis r31, r31, -0x80
L_8016D5B0:
    stw r31, 0x8(r1)
    lfs f13, 0x8(r1)
    fmr f1, f13
    slwi r8, r7, 2
    la r9, PowfBp0Const
    lfs f7, PowfOneConst
    lfsx f13, r9, r8
    fadds f0, f1, f13
    fdivs f4, f7, f0
    fsubs f5, f1, f13
    fmuls f31, f5, f4
    fmr f0, f31
    stfs f0, 0x8(r1)
    lwz r0, 0x8(r1)
    clrrwi r9, r0, 12
    stw r9, 0x8(r1)
    lfs f9, 0x8(r1)
    srawi r11, r31, 1
    slwi r9, r7, 21
    oris r11, r11, 0x2000
    addis r9, r9, 0x4
    add r0, r11, r9
    stw r0, 0x8(r1)
    lfs f0, 0x8(r1)
    fsubs f13, f0, f13
    lfs f10, PowfL5Const
    fmuls f6, f31, f31
    lfs f12, PowfL6Const
    fmuls f11, f9, f0
    lfs f8, PowfL4Const
    fsubs f1, f1, f13
    fmadds f12, f6, f12, f10
    lfs f0, PowfL3Const
    fmadds f12, f6, f12, f8
    lfs f13, PowfL2Const
    fmadds f12, f6, f12, f0
    lfs f8, PowfL1Const
    fmuls f0, f9, f1
    lfs f10, PowfThreeConst
    fmadds f12, f6, f12, f13
    fsubs f11, f5, f11
    fmadds f12, f6, f12, f8
    fsubs f11, f11, f0
    fmuls f8, f6, f6
    fmuls f11, f4, f11
    fadds f13, f9, f31
    fmuls f13, f11, f13
    fmuls f6, f9, f9
    fmadds f1, f8, f12, f13
    fadds f0, f6, f10
    fadds f0, f0, f1
    stfs f0, 0x8(r1)
    lwz r0, 0x8(r1)
    clrrwi r0, r0, 12
    stw r0, 0x8(r1)
    lfs f12, 0x8(r1)
    fsubs f10, f12, f10
    fsubs f10, f10, f6
    fsubs f1, f1, f10
    fmuls f0, f1, f31
    fmadds f4, f11, f12, f0
    fmuls f5, f9, f12
    fadds f13, f5, f4
    stfs f13, 0x8(r1)
    lwz r0, 0x8(r1)
    clrrwi r9, r0, 12
    stw r9, 0x8(r1)
    lfs f6, 0x8(r1)
    fsubs f13, f6, f5
    xoris r0, r3, 0x8000
    lfs f0, PowfCpConst
    fsubs f9, f4, f13
    stw r0, 0x14(r1)
    lis r9, 0x4330
    fmuls f0, f9, f0
    la r11, PowfDpLo0Const
    lfs f11, PowfCpLoConst
    stw r9, 0x10(r1)
    lfsx f9, r11, r8
    fmadds f11, f6, f11, f0
    lfs f10, PowfCpHiConst
    la r9, PowfDpHi0Const
    fadds f11, f11, f9
    lfd f13, 0x10(r1)
    lfd f12, PowfCvtConst
    fmuls f10, f6, f10
    lfsx f9, r9, r8
    fadds f0, f10, f11
    fsub f13, f13, f12
    frsp f1, f13
    fadds f0, f0, f9
    fadds f0, f0, f1
    stfs f0, 0x8(r1)
    lwz r0, 0x8(r1)
    clrrwi r11, r0, 12
    stw r11, 0x8(r1)
    lfs f12, 0x8(r1)
    fsubs f0, f12, f1
    fsubs f0, f0, f9
    fsubs f0, f0, f10
    fsubs f0, f11, f0
L_8016D744:
    subi r9, r6, 0x1
    subi r0, r27, 0x1
    or. r10, r9, r0
    fmr f31, f7
    bne L_8016D75C
    lfs f31, PowfNegOneConst
L_8016D75C:
    fmr f12, f30
    stfs f12, 0x8(r1)
    lwz r0, 0x8(r1)
    clrrwi r9, r0, 12
    stw r9, 0x8(r1)
    lfs f12, 0x8(r1)
    stw r11, 0x8(r1)
    fsubs f13, f30, f12
    lfs f12, 0x8(r1)
    fmuls f0, f30, f0
    stw r9, 0x8(r1)
    fmadds f9, f13, f12, f0
    lfs f13, 0x8(r1)
    fmuls f6, f13, f12
    fadds f2, f9, f6
    fmr f0, f2
    stfs f0, 0x8(r1)
    lwz r8, 0x8(r1)
    mr r10, r8
    lis r0, 0x4300
    cmpw r10, r0
    ble L_8016D7BC
    lfs f0, PowfHugeConst
    b L_8016D80C
L_8016D7BC:
    bne L_8016D7DC
    lfs f0, PowfOvtConst
    fsubs f13, f2, f6
    fadds f0, f9, f0
    fcmpu cr0, f0, f13
    ble L_8016D818
    lfs f0, PowfHugeConst
    b L_8016D80C
L_8016D7DC:
    lis r9, 0x4316
    clrlwi r0, r10, 1
    cmpw r0, r9
    bgt L_8016D808
    lis r0, 0xc316
    cmpw r10, r0
    bne L_8016D818
    fsubs f0, f2, f6
    fcmpu cr0, f9, f0
    cror 3, 2, 0
    bns L_8016D818
L_8016D808:
    lfs f0, PowfTinyConst
L_8016D80C:
    fmuls f1, f31, f0
    fmuls f1, f1, f0
    b L_8016D954
L_8016D818:
    clrlwi r0, r10, 1
    lis r9, 0x3f00
    srawi r11, r0, 23
    cmpw r0, r9
    li r3, 0x0
    ble L_8016D880
    subi r9, r11, 0x7e
    lis r0, 0x80
    sraw r0, r0, r9
    add r3, r8, r0
    extrwi r9, r3, 8, 1
    subi r7, r9, 0x7f
    lis r0, 0x7f
    ori r0, r0, 0xffff
    sraw r0, r0, r7
    andc r0, r3, r0
    stw r0, 0x8(r1)
    lfs f1, 0x8(r1)
    clrlwi r9, r3, 9
    oris r9, r9, 0x80
    subfic r0, r7, 0x17
    sraw r3, r9, r0
    cmpwi r8, 0x0
    bge L_8016D87C
    neg r3, r3
L_8016D87C:
    fsubs f6, f6, f1
L_8016D880:
    fadds f12, f9, f6
    stfs f12, 0x8(r1)
    lwz r0, 0x8(r1)
    clrrwi r9, r0, 12
    stw r9, 0x8(r1)
    lfs f1, 0x8(r1)
    lfs f8, PowfLg2HiConst
    lfs f12, PowfLg2LoConst
    fsubs f13, f1, f6
    lfs f11, PowfLg2Const
    fmuls f12, f1, f12
    lfs f0, PowfP5Const
    fsubs f13, f9, f13
    lfs f10, PowfP3Const
    fmadds f4, f13, f11, f12
    lfs f9, PowfP4Const
    fmuls f5, f1, f8
    lfs f11, PowfP2Const
    fadds f2, f5, f4
    lfs f12, PowfP1Const
    fmuls f1, f2, f2
    lfs f13, PowfTwoConst
    fmadds f0, f1, f0, f9
    fmadds f0, f1, f0, f10
    fmadds f0, f1, f0, f11
    fmadds f0, f1, f0, f12
    fmuls f0, f1, f0
    fsubs f0, f2, f0
    fsubs f13, f0, f13
    stfs f0, 0x8(r1)
    fmuls f12, f2, f0
    fdivs f12, f12, f13
    fsubs f0, f2, f5
    fsubs f0, f4, f0
    fmadds f13, f2, f0, f0
    fsubs f1, f12, f13
    fsubs f0, f1, f2
    fsubs f2, f7, f0
    fmr f12, f2
    stfs f12, 0x8(r1)
    lwz r9, 0x8(r1)
    slwi r0, r3, 23
    add r10, r9, r0
    srawi. r0, r10, 23
    bgt L_8016D944
    fmr f1, f2
    bl scalbnf
    fmr f2, f1
    b L_8016D950
L_8016D944:
    stw r10, 0x8(r1)
    lfs f0, 0x8(r1)
    fmr f2, f0
L_8016D950:
    fmuls f1, f31, f2
L_8016D954:
    lwz r0, 0x44(r1)
    lwz r12, 0x18(r1)
    mtlr r0
    lmw r27, 0x1c(r1)
    lfd f30, 0x30(r1)
    lfd f31, 0x38(r1)
    mtcrf 8, r12
    addi r1, r1, 0x40
    blr
    // clang-format on
}
