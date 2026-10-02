#pragma force_active on

const float AtanfAtanHi0 = 4.6364760399e-01; /* atan(0.5)hi 0x3eed6338 */
const float AtanfAtanHi1 = 7.8539812565e-01; /* atan(1.0)hi 0x3f490fda */
const float AtanfAtanHi2 = 9.8279368877e-01; /* atan(1.5)hi 0x3f7b985e */
const float AtanfAtanHi3 = 1.5707962513e+00; /* atan(inf)hi 0x3fc90fda */

const float AtanfAtanLo0 = 5.0121582440e-09; /* atan(0.5)lo 0x31ac3769 */
const float AtanfAtanLo1 = 3.7748947079e-08; /* atan(1.0)lo 0x33222168 */
const float AtanfAtanLo2 = 3.4473217170e-08; /* atan(1.5)lo 0x33140fb4 */
const float AtanfAtanLo3 = 7.5497894159e-08; /* atan(inf)lo 0x33a22168 */

const float AtanfAT0 = 3.3333334327e-01;  /* 0x3eaaaaab */
const float AtanfAT1 = -2.0000000298e-01; /* 0xbe4ccccd */
const float AtanfAT2 = 1.4285714924e-01;  /* 0x3e124925 */
const float AtanfAT3 = -1.1111110449e-01; /* 0xbde38e38 */
const float AtanfAT4 = 9.0908870101e-02;  /* 0x3dba2e6e */
const float AtanfAT5 = -7.6918758452e-02; /* 0xbd9d8795 */
const float AtanfAT6 = 6.6610731184e-02;  /* 0x3d886b35 */
const float AtanfAT7 = -5.8335702866e-02; /* 0xbd6ef16b */
const float AtanfAT8 = 4.9768779427e-02;  /* 0x3d4bda59 */
const float AtanfAT9 = -3.6531571299e-02; /* 0xbd15a221 */
const float AtanfAT10 = 1.6285819933e-02; /* 0x3c8569d7 */

extern float AtanfHugeConst;
extern float AtanfOneConst;
extern float AtanfTwoConst;
extern float AtanfThreeHalvesConst;
extern float AtanfNegOneConst;
extern float fabsf(float x);

asm float atanf(float x)
{
    // clang-format off
    nofralloc
    stwu    r1, -0x18(r1)
    mflr    r0
    stmw    r30, 0x10(r1)
    stw     r0, 0x1c(r1)
    fmr     f5, f1
    fmr     f0, f5
    stfs    f0, 0x8(r1)
    lwz     r30, 0x8(r1)
    clrlwi  r31, r30, 1
    lis     r0, 0x507f
    ori     r0, r0, 0xffff
    cmpw    r31, r0
    ble     L_DAE4
    lis     r0, 0x7f80
    cmpw    r31, r0
    ble     L_DAB8
    fadds   f1, f5, f5
    b       L_DC6C
L_DAB8:
    cmpwi   r30, 0x0
    ble     L_DAD0
    lfs     f0, AtanfAtanHi3
    lfs     f1, AtanfAtanLo3
    fadds   f1, f0, f1
    b       L_DC6C
L_DAD0:
    lfs     f1, AtanfAtanHi3
    lfs     f0, AtanfAtanLo3
    fneg    f1, f1
    fsubs   f1, f1, f0
    b       L_DC6C
L_DAE4:
    lis     r0, 0x3edf
    ori     r0, r0, 0xffff
    cmpw    r31, r0
    bgt     L_DB28
    lis     r0, 0x30ff
    ori     r0, r0, 0xffff
    cmpw    r31, r0
    bgt     L_DB20
    lfs     f0, AtanfHugeConst
    lfs     f13, AtanfOneConst
    fadds   f0, f5, f0
    fcmpu   cr0, f0, f13
    ble     L_DB20
    fmr     f1, f5
    b       L_DC6C
L_DB20:
    li      r0, -0x1
    b       L_DBC4
L_DB28:
    fmr     f1, f5
    bl      fabsf
    lis     r0, 0x3f97
    fmr     f5, f1
    ori     r0, r0, 0xffff
    cmpw    r31, r0
    bgt     L_DB8C
    lis     r0, 0x3f2f
    ori     r0, r0, 0xffff
    cmpw    r31, r0
    bgt     L_DB74
    lfs     f12, AtanfOneConst
    fadds   f13, f5, f5
    lfs     f0, AtanfTwoConst
    li      r0, 0x0
    fsubs   f13, f13, f12
    fadds   f0, f5, f0
    fdivs   f5, f13, f0
    b       L_DBC4
L_DB74:
    lfs     f0, AtanfOneConst
    li      r0, 0x1
    fadds   f13, f5, f0
    fsubs   f0, f5, f0
    fdivs   f5, f0, f13
    b       L_DBC4
L_DB8C:
    lis     r0, 0x401b
    ori     r0, r0, 0xffff
    cmpw    r31, r0
    bgt     L_DBB8
    lfs     f0, AtanfThreeHalvesConst
    li      r0, 0x2
    lfs     f13, AtanfOneConst
    fsubs   f12, f5, f0
    fmadds  f0, f5, f0, f13
    fdivs   f5, f12, f0
    b       L_DBC4
L_DBB8:
    lfs     f0, AtanfNegOneConst
    li      r0, 0x3
    fdivs   f5, f0, f5
L_DBC4:
    fmuls   f6, f5, f5
    lfs     f10, AtanfAT8
    lfs     f13, AtanfAT10
    fmuls   f12, f6, f6
    lfs     f9, AtanfAT6
    cmpwi   r0, 0x0
    fmadds  f13, f12, f13, f10
    lfs     f11, AtanfAT7
    fmadds  f13, f12, f13, f9
    lfs     f10, AtanfAT4
    lfs     f0, AtanfAT9
    lfs     f9, AtanfAT5
    fmadds  f13, f12, f13, f10
    fmadds  f0, f12, f0, f11
    lfs     f8, AtanfAT2
    lfs     f7, AtanfAT3
    fmadds  f0, f12, f0, f9
    lfs     f10, AtanfAT0
    fmadds  f13, f12, f13, f8
    lfs     f11, AtanfAT1
    fmadds  f0, f12, f0, f7
    fmadds  f13, f12, f13, f10
    fmadds  f0, f12, f0, f11
    fmuls   f1, f6, f13
    fmuls   f0, f12, f0
    bge     L_DC3C
    fadds   f1, f1, f0
    fmuls   f1, f5, f1
    fsubs   f1, f5, f1
    b       L_DC6C
L_DC3C:
    slwi    r0, r0, 2
    la    r9, AtanfAtanLo0
    lfsx    f12, r9, r0
    fadds   f0, f1, f0
    la    r9, AtanfAtanHi0
    cmpwi   r30, 0x0
    fmsubs  f0, f5, f0, f12
    lfsx    f13, r9, r0
    fsubs   f0, f0, f5
    fsubs   f1, f13, f0
    bge     L_DC6C
    fneg    f1, f1
L_DC6C:
    lwz     r0, 0x1c(r1)
    mtlr    r0
    lmw     r30, 0x10(r1)
    addi    r1, r1, 0x18
    blr
    // clang-format on
}
