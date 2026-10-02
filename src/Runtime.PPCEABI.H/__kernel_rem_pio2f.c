#pragma force_active on

/* kf_rem_pio2.c scalars, in .sdata address order (not source order). */
double KernelRemPio2fCvtConst = 4503601774854144.0; /* MWCC's (float)ipio2[j] magic, 0x4330000080000000 */
struct { float v; } KernelRemPio2fZeroConst = {0.0f}; /* zero */
float KernelRemPio2fTwon8Const = 3.9062500000e-03f;   /* twon8 */
float KernelRemPio2fTwo8Const = 2.5600000000e+02f;    /* two8 */
float KernelRemPio2fEighthConst = 1.2500000000e-01f;  /* (float)0.125 */
float KernelRemPio2fEightConst = 8.0000000000e+00f;   /* (float)8.0 */
float KernelRemPio2fHalfConst = 5.0000000000e-01f;    /* (float)0.5 */
float KernelRemPio2fOneConst = 1.0000000000e+00f;     /* one */

/* init_jk[3], split into scalars so each stays under the .sdata2 threshold. */
const int KernelRemPio2fInitJk0 = 4;
const int KernelRemPio2fInitJk1 = 7;
const int KernelRemPio2fInitJk2 = 9;

/* PIo2[11], split the same way. */
const float KernelRemPio2fPIo2Const0 = 1.5703125000e+00f;
const float KernelRemPio2fPIo2Const1 = 4.5776367188e-04f;
const float KernelRemPio2fPIo2Const2 = 2.5987625122e-05f;
const float KernelRemPio2fPIo2Const3 = 7.5437128544e-08f;
const float KernelRemPio2fPIo2Const4 = 6.0026650317e-11f;
const float KernelRemPio2fPIo2Const5 = 7.3896444519e-13f;
const float KernelRemPio2fPIo2Const6 = 5.3845816694e-15f;
const float KernelRemPio2fPIo2Const7 = 5.6378512969e-18f;
const float KernelRemPio2fPIo2Const8 = 8.3009228831e-20f;
const float KernelRemPio2fPIo2Const9 = 3.2756352257e-22f;
const float KernelRemPio2fPIo2Const10 = 6.3331015649e-25f;

extern float scalbnf(float x, int n);
extern float floorf(float x);

asm int __kernel_rem_pio2f(float* x, float* y, int e0, int nx, int prec, const int* ipio2)
{
    // clang-format off
    nofralloc
    stwu    r1, -0x1a0(r1)
    mflr    r0
    mfcr    r12
    stfd    f31, 0x198(r1)
    stmw    r18, 0x160(r1)
    stw     r0, 0x1a4(r1)
    stw     r12, 0x15c(r1)
    mr      r19, r7
    la      r9, KernelRemPio2fInitJk0
    slwi    r0, r19, 2
    mr      r20, r3
    lwzx    r27, r9, r0
    mr      r26, r4
    mr      r18, r8
    subi    r29, r6, 0x1
    subic.  r0, r5, 0x3
    bge     L_8016F538
    addi    r0, r5, 0x4
L_8016F538:
    srawi.  r24, r0, 3
    bge     L_8016F544
    li      r24, 0x0
L_8016F544:
    addi    r0, r24, 0x1
    subf    r6, r29, r24
    slwi    r0, r0, 3
    mtctr   r6
    addi    r21, r1, 0xf8
    subf    r28, r0, r5
    addi    r30, r1, 0x8
    cmpwi   cr3, r19, 0x2
    add.    r9, r29, r27
    blt     L_8016F5D8
    slwi    r0, r6, 2
    lfd     f13, KernelRemPio2fCvtConst
    lfs     f12, KernelRemPio2fZeroConst
    add     r10, r0, r18
    addi    r8, r9, 0x1
    lis     r7, 0x4330
    addi    r11, r1, 0x58
L_8016F588:
    mfctr   r9
    cmpwi   r9, 0x0
    blt     L_8016F5B8
    lwz     r0, 0x0(r10)
    xoris   r0, r0, 0x8000
    stw     r0, 0x154(r1)
    stw     r7, 0x150(r1)
    lfd     f0, 0x150(r1)
    fsub    f0, f0, f13
    frsp    f0, f0
    stfs    f0, 0x0(r11)
    b       L_8016F5BC
L_8016F5B8:
    stfs    f12, 0x0(r11)
L_8016F5BC:
    mfctr   r6
    addi    r11, r11, 0x4
    addi    r6, r6, 0x1
    addi    r10, r10, 0x4
    mtctr   r6
    subic.  r8, r8, 0x1
    bne     L_8016F588
L_8016F5D8:
    li      r8, 0x0
    cmpwi   cr4, r28, 0x0
    cmpw    r8, r27
    bgt     L_8016F648
    lfs     f12, KernelRemPio2fZeroConst
    mr      r10, r21
L_8016F5F0:
    fmr     f1, f12
    cmpwi   r29, 0x0
    slwi    r6, r8, 2
    addi    r5, r8, 0x1
    blt     L_8016F638
    add     r0, r29, r8
    addi    r9, r1, 0x58
    slwi    r0, r0, 2
    mr      r11, r20
    add     r9, r0, r9
    addi    r0, r29, 0x1
    mtctr   r0
L_8016F620:
    lfs     f13, 0x0(r11)
    lfs     f0, 0x0(r9)
    addi    r11, r11, 0x4
    subi    r9, r9, 0x4
    fmadds  f1, f13, f0, f1
    bdnz    L_8016F620
L_8016F638:
    mr      r8, r5
    stfsx   f1, r10, r6
    cmpw    r8, r27
    ble     L_8016F5F0
L_8016F648:
    mr      r31, r27
L_8016F64C:
    slwi    r0, r31, 2
    mtctr   r31
    mr      r22, r0
    lfsx    f31, r21, r0
    cmpwi   r31, 0x0
    ble     L_8016F6E8
    subi    r0, r22, 0x4
    lfs     f9, KernelRemPio2fTwon8Const
    add     r7, r0, r21
    lfd     f11, KernelRemPio2fCvtConst
    lfs     f10, KernelRemPio2fTwo8Const
    lis     r0, 0x4330
    mr      r8, r30
L_8016F680:
    fmuls   f0, f31, f9
    mr      r11, r9
    fctiwz  f13, f0
    mr      r10, r9
    stfd    f13, 0x150(r1)
    mfctr   r6
    subic.  r6, r6, 0x1
    lwz     r9, 0x154(r1)
    mtctr   r6
    xoris   r9, r9, 0x8000
    stw     r9, 0x154(r1)
    stw     r0, 0x150(r1)
    lfd     f0, 0x150(r1)
    fsub    f0, f0, f11
    frsp    f1, f0
    fmuls   f13, f1, f10
    fsubs   f13, f31, f13
    fctiwz  f12, f13
    stfd    f12, 0x150(r1)
    lwz     r10, 0x154(r1)
    stw     r10, 0x0(r8)
    addi    r8, r8, 0x4
    lfs     f0, 0x0(r7)
    subi    r7, r7, 0x4
    fadds   f31, f0, f1
    bgt     L_8016F680
L_8016F6E8:
    fmr     f1, f31
    mr      r3, r28
    bl      scalbnf
    lfs     f0, KernelRemPio2fEighthConst
    fmr     f31, f1
    fmuls   f1, f31, f0
    bl      floorf
    lfs     f0, KernelRemPio2fEightConst
    mr      r9, r11
    lis     r10, 0x4330
    fmuls   f1, f1, f0
    lfd     f12, KernelRemPio2fCvtConst
    fsubs   f31, f31, f1
    li      r8, 0x0
    fmr     f0, f31
    fctiwz  f13, f0
    stfd    f13, 0x150(r1)
    lwz     r23, 0x154(r1)
    xoris   r0, r23, 0x8000
    stw     r0, 0x154(r1)
    stw     r10, 0x150(r1)
    lfd     f0, 0x150(r1)
    fsub    f0, f0, f12
    frsp    f0, f0
    fsubs   f31, f31, f0
    ble     cr4, L_8016F780
    subi    r11, r31, 0x1
    subfic  r9, r28, 0x8
    slwi    r11, r11, 2
    subfic  r10, r28, 0x7
    lwzx    r0, r30, r11
    sraw    r8, r0, r9
    slw     r9, r8, r9
    add     r23, r23, r8
    subf    r0, r9, r0
    sraw    r8, r0, r10
    stwx    r0, r30, r11
    b       L_8016F7AC
L_8016F780:
    bne     cr4, L_8016F798
    subi    r0, r31, 0x1
    slwi    r0, r0, 2
    lwzx    r9, r30, r0
    srawi   r8, r9, 8
    b       L_8016F7AC
L_8016F798:
    lfs     f0, KernelRemPio2fHalfConst
    fcmpu   cr0, f31, f0
    cror    un, eq, gt
    bns     L_8016F7AC
    li      r8, 0x2
L_8016F7AC:
    cmpwi   r8, 0x0
    mfcr    r25
    ble     L_8016F874
    cmpwi   cr7, r8, 0x2
    addi    r23, r23, 0x1
    li      r10, 0x0
    cmpwi   r31, 0x0
    ble     L_8016F814
    mr      r11, r30
    li      r9, 0x0
    mr      r8, r31
L_8016F7D8:
    lwzx    r0, r9, r11
    cmpwi   r10, 0x0
    mtctr   r0
    bne     L_8016F7FC
    cmpwi   r0, 0x0
    beq     L_8016F808
    subfic  r0, r0, 0x100
    li      r10, 0x1
    b       L_8016F804
L_8016F7FC:
    mfctr   r6
    subfic  r0, r6, 0xff
L_8016F804:
    stwx    r0, r9, r30
L_8016F808:
    addi    r9, r9, 0x4
    subic.  r8, r8, 0x1
    bne     L_8016F7D8
L_8016F814:
    ble     cr4, L_8016F854
    cmpwi   r28, 0x1
    beq     L_8016F82C
    cmpwi   r28, 0x2
    beq     L_8016F840
    b       L_8016F854
L_8016F82C:
    subi    r9, r31, 0x1
    slwi    r9, r9, 2
    lwzx    r0, r30, r9
    clrlwi  r0, r0, 25
    b       L_8016F850
L_8016F840:
    subi    r9, r31, 0x1
    slwi    r9, r9, 2
    lwzx    r0, r30, r9
    clrlwi  r0, r0, 26
L_8016F850:
    stwx    r0, r30, r9
L_8016F854:
    bne     cr7, L_8016F874
    lfs     f1, KernelRemPio2fOneConst
    cmpwi   r10, 0x0
    fsubs   f31, f1, f31
    beq     L_8016F874
    mr      r3, r28
    bl      scalbnf
    fsubs   f31, f31, f1
L_8016F874:
    lfs     f0, KernelRemPio2fZeroConst
    fmr     f13, f0
    fcmpu   cr0, f31, f0
    bne     L_8016F9B8
    subi    r8, r31, 0x1
    li      r0, 0x0
    mtctr   r0
    cmpw    r8, r27
    blt     L_8016F8C0
    slwi    r0, r8, 2
    add     r9, r0, r30
L_8016F8A0:
    lwz     r0, 0x0(r9)
    mfctr   r6
    subi    r8, r8, 0x1
    subi    r9, r9, 0x4
    or      r6, r6, r0
    cmpw    r8, r27
    mtctr   r6
    bge     L_8016F8A0
L_8016F8C0:
    mfctr   r7
    cmpwi   r7, 0x0
    bne     L_8016F9B8
    subi    r0, r27, 0x1
    li      r7, 0x1
    slwi    r0, r0, 2
    addi    r11, r31, 0x1
    lwzx    r9, r30, r0
    cmpwi   r9, 0x0
    bne     L_8016F904
    slwi    r9, r27, 2
    add     r9, r9, r30
    subi    r9, r9, 0x4
L_8016F8F4:
    lwzu    r0, -0x4(r9)
    addi    r7, r7, 0x1
    cmpwi   r0, 0x0
    beq     L_8016F8F4
L_8016F904:
    add     r0, r31, r7
    mr      r8, r11
    mr      r7, r0
    cmpw    r8, r0
    bgt     L_8016F9B0
    addi    r4, r1, 0x58
    lfd     f12, KernelRemPio2fCvtConst
    lfs     f11, KernelRemPio2fZeroConst
    mr      r25, r4
    lis     r31, 0x4330
    mr      r12, r21
    mr      r3, r7
L_8016F934:
    add     r0, r24, r8
    slwi    r0, r0, 2
    add     r9, r29, r8
    lwzx    r11, r18, r0
    slwi    r9, r9, 2
    addi    r5, r8, 0x1
    fmr     f1, f11
    xoris   r11, r11, 0x8000
    cmpwi   r29, 0x0
    stw     r11, 0x154(r1)
    slwi    r6, r8, 2
    stw     r31, 0x150(r1)
    lfd     f0, 0x150(r1)
    fsub    f0, f0, f12
    frsp    f0, f0
    stfsx   f0, r4, r9
    blt     L_8016F9A0
    addi    r10, r29, 0x1
    add     r9, r9, r25
    mtctr   r10
    mr      r11, r20
L_8016F988:
    lfs     f13, 0x0(r11)
    lfs     f0, 0x0(r9)
    addi    r11, r11, 0x4
    subi    r9, r9, 0x4
    fmadds  f1, f13, f0, f1
    bdnz    L_8016F988
L_8016F9A0:
    mr      r8, r5
    stfsx   f1, r12, r6
    cmpw    r8, r3
    ble     L_8016F934
L_8016F9B0:
    mr      r31, r7
    b       L_8016F64C
L_8016F9B8:
    fcmpu   cr0, f31, f13
    bne     L_8016F9F4
    subi    r31, r31, 0x1
    subi    r28, r28, 0x8
    slwi    r9, r31, 2
    lwzx    r0, r30, r9
    cmpwi   r0, 0x0
    bne     L_8016FAA4
    add     r9, r9, r30
L_8016F9DC:
    lwzu    r0, -0x4(r9)
    subi    r31, r31, 0x1
    subi    r28, r28, 0x8
    cmpwi   r0, 0x0
    beq     L_8016F9DC
    b       L_8016FAA4
L_8016F9F4:
    fmr     f1, f31
    neg     r3, r28
    bl      scalbnf
    lfs     f9, KernelRemPio2fTwo8Const
    fmr     f31, f1
    fcmpu   cr0, f31, f9
    cror    un, eq, gt
    bns     L_8016FA90
    lfs     f0, KernelRemPio2fTwon8Const
    mr      r8, r9
    mr      r11, r9
    fmuls   f0, f31, f0
    mr      r10, r9
    lis     r0, 0x4330
    fctiwz  f13, f0
    lfd     f10, KernelRemPio2fCvtConst
    stfd    f13, 0x150(r1)
    addi    r31, r31, 0x1
    slwi    r7, r31, 2
    addi    r28, r28, 0x8
    lwz     r9, 0x154(r1)
    xoris   r9, r9, 0x8000
    stw     r9, 0x154(r1)
    stw     r0, 0x150(r1)
    lfd     f0, 0x150(r1)
    fsub    f0, f0, f10
    frsp    f1, f0
    fmuls   f13, f1, f9
    fsubs   f13, f31, f13
    fctiwz  f12, f13
    stfd    f12, 0x150(r1)
    fmr     f0, f1
    fctiwz  f11, f0
    lwz     r11, 0x154(r1)
    stfd    f11, 0x150(r1)
    stwx    r11, r30, r22
    lwz     r10, 0x154(r1)
    stwx    r10, r30, r7
    b       L_8016FAA4
L_8016FA90:
    fmr     f0, f31
    fctiwz  f13, f0
    stfd    f13, 0x150(r1)
    lwz     r9, 0x154(r1)
    stwx    r9, r30, r22
L_8016FAA4:
    lfs     f1, KernelRemPio2fOneConst
    mr      r3, r28
    bl      scalbnf
    mr.     r8, r31
    blt     L_8016FB04
    lfd     f13, KernelRemPio2fCvtConst
    mr      r7, r30
    lfs     f12, KernelRemPio2fTwon8Const
    mr      r10, r21
    lis     r6, 0x4330
    slwi    r11, r8, 2
L_8016FAD0:
    lwzx    r0, r11, r7
    subic.  r8, r8, 0x1
    xoris   r0, r0, 0x8000
    stw     r0, 0x154(r1)
    stw     r6, 0x150(r1)
    lfd     f0, 0x150(r1)
    fsub    f0, f0, f13
    frsp    f0, f0
    fmuls   f0, f1, f0
    stfsx   f0, r11, r10
    fmuls   f1, f1, f12
    subi    r11, r11, 0x4
    bge     L_8016FAD0
L_8016FB04:
    mr.     r8, r31
    blt     L_8016FB7C
    mr      r3, r21
L_8016FB10:
    li      r7, 0x0
    lfs     f1, KernelRemPio2fZeroConst
    cmpw    r7, r27
    subi    r4, r8, 0x1
    subf    r11, r8, r31
    addi    r6, r1, 0xa8
    bgt     L_8016FB6C
    mr      r5, r11
    cmpw    r7, r11
    bgt     L_8016FB6C
    slwi    r0, r8, 2
    la      r10, KernelRemPio2fPIo2Const0
    add     r9, r0, r3
L_8016FB44:
    lfs     f13, 0x0(r10)
    addi    r7, r7, 0x1
    lfs     f0, 0x0(r9)
    addi    r10, r10, 0x4
    addi    r9, r9, 0x4
    cmpw    r7, r27
    fmadds  f1, f13, f0, f1
    bgt     L_8016FB6C
    cmpw    r7, r5
    ble     L_8016FB44
L_8016FB6C:
    slwi    r0, r11, 2
    mr.     r8, r4
    stfsx   f1, r6, r0
    bge     L_8016FB10
L_8016FB7C:
    bgt     cr3, L_8016FB94
    cmpwi   r19, 0x1
    bge     L_8016FBE4
    cmpwi   r19, 0x0
    beq     L_8016FBA0
    b       L_8016FD50
L_8016FB94:
    cmpwi   r19, 0x3
    beq     L_8016FC64
    b       L_8016FD50
L_8016FBA0:
    lfs     f1, KernelRemPio2fZeroConst
    mr.     r8, r31
    blt     L_8016FBCC
    addi    r9, r1, 0xa8
    slwi    r0, r8, 2
    add     r9, r9, r0
L_8016FBB8:
    lfs     f0, 0x0(r9)
    subic.  r8, r8, 0x1
    subi    r9, r9, 0x4
    fadds   f1, f1, f0
    bge     L_8016FBB8
L_8016FBCC:
    stfs    f1, 0x0(r26)
    mtcrf   128, r25
    beq     L_8016FD50
    fneg    f0, f1
    stfs    f0, 0x0(r26)
    b       L_8016FD50
L_8016FBE4:
    lfs     f1, KernelRemPio2fZeroConst
    mr.     r8, r31
    blt     L_8016FC10
    addi    r9, r1, 0xa8
    slwi    r0, r8, 2
    add     r9, r9, r0
L_8016FBFC:
    lfs     f0, 0x0(r9)
    subic.  r8, r8, 0x1
    subi    r9, r9, 0x4
    fadds   f1, f1, f0
    bge     L_8016FBFC
L_8016FC10:
    stfs    f1, 0x0(r26)
    mtcrf   128, r25
    beq     L_8016FC24
    fneg    f0, f1
    stfs    f0, 0x0(r26)
L_8016FC24:
    lfs     f0, 0xa8(r1)
    cmpwi   r31, 0x0
    fsubs   f1, f0, f1
    ble     L_8016FC50
    mr      r8, r31
    addi    r9, r1, 0xac
L_8016FC3C:
    lfs     f0, 0x0(r9)
    subic.  r8, r8, 0x1
    addi    r9, r9, 0x4
    fadds   f1, f1, f0
    bne     L_8016FC3C
L_8016FC50:
    stfs    f1, 0x4(r26)
    mtcrf   128, r25
    beq     L_8016FD50
    fneg    f0, f1
    b       L_8016FD4C
L_8016FC64:
    mr.     r8, r31
    ble     L_8016FCA0
    addi    r9, r1, 0xa4
    slwi    r0, r8, 2
    add     r9, r9, r0
L_8016FC78:
    lfs     f13, 0x0(r9)
    subic.  r8, r8, 0x1
    lfs     f0, 0x4(r9)
    fadds   f1, f13, f0
    fsubs   f13, f13, f1
    stfs    f1, 0x0(r9)
    fadds   f0, f0, f13
    stfs    f0, 0x4(r9)
    subi    r9, r9, 0x4
    bgt     L_8016FC78
L_8016FCA0:
    mr      r8, r31
    cmpwi   r8, 0x1
    ble     L_8016FCE4
    addi    r9, r1, 0xa4
    slwi    r0, r8, 2
    add     r9, r9, r0
L_8016FCB8:
    lfs     f13, 0x0(r9)
    subi    r8, r8, 0x1
    lfs     f0, 0x4(r9)
    cmpwi   r8, 0x1
    fadds   f1, f13, f0
    fsubs   f13, f13, f1
    stfs    f1, 0x0(r9)
    fadds   f0, f0, f13
    stfs    f0, 0x4(r9)
    subi    r9, r9, 0x4
    bgt     L_8016FCB8
L_8016FCE4:
    mr      r8, r31
    lfs     f1, KernelRemPio2fZeroConst
    cmpwi   r8, 0x1
    lfs     f13, 0xa8(r1)
    ble     L_8016FD1C
    addi    r9, r1, 0xa8
    slwi    r0, r8, 2
    add     r9, r9, r0
L_8016FD04:
    lfs     f0, 0x0(r9)
    subi    r8, r8, 0x1
    subi    r9, r9, 0x4
    cmpwi   r8, 0x1
    fadds   f1, f1, f0
    bgt     L_8016FD04
L_8016FD1C:
    mtcrf   128, r25
    bne     L_8016FD34
    lfs     f0, 0xac(r1)
    stfs    f1, 0x8(r26)
    stfs    f13, 0x0(r26)
    b       L_8016FD4C
L_8016FD34:
    lfs     f0, 0xac(r1)
    fneg    f13, f13
    fneg    f12, f1
    stfs    f13, 0x0(r26)
    fneg    f0, f0
    stfs    f12, 0x8(r26)
L_8016FD4C:
    stfs    f0, 0x4(r26)
L_8016FD50:
    clrlwi  r3, r23, 29
    lwz     r0, 0x1a4(r1)
    lwz     r12, 0x15c(r1)
    mtlr    r0
    lmw     r18, 0x160(r1)
    lfd     f31, 0x198(r1)
    mtcrf   24, r12
    addi    r1, r1, 0x1a0
    blr
    // clang-format on
}
