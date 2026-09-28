/* ef_atan2.c's float literal pool (.sdata 0x8066C0A0-0x8066C0D0), read only
 * by __ieee754_atan2f. */
float Atan2fPiConst = 3.1415925026e+00f;        /* 0x40490fda */
float Atan2fNegPiConst = -3.1415925026e+00f;    /* 0xc0490fda */
float Atan2fNegPiO2Const = -1.5707963705e+00f;  /* 0xbfc90fdb */
float Atan2fPiO2Const = 1.5707963705e+00f;      /* 0x3fc90fdb */
float Atan2fPiO4Const = 7.8539818525e-01f;      /* 0x3f490fdb */
float Atan2fNegPiO4Const = -7.8539818525e-01f;  /* 0xbf490fdb */
float Atan2f3PiO4Const = 2.3561944962e+00f;     /* 0x4016cbe4 */
float Atan2fNeg3PiO4Const = -2.3561944962e+00f; /* 0xc016cbe4 */
struct { float v; } Atan2fZeroConst = {0.0f};   /* 0x00000000 */
float Atan2fNegZeroConst = -0.0f;               /* 0x80000000 */
float Atan2fPiO2HiConst = 1.5707964897e+00f;    /* 0x3fc90fdc */
float Atan2fPiLoConst = 1.5099578832e-07f;      /* 0x34222168 */
extern float atanf(float x);
extern float fabsf(float x);

asm float __ieee754_atan2f(float y, float x)
{
    // clang-format off
    nofralloc
    stwu    r1, -0x18(r1)
    mflr    r0
    stw     r31, 0x14(r1)
    stw     r0, 0x1c(r1)
    fmr     f0, f2
    stfs    f0, 0x8(r1)
    lwz     r7, 0x8(r1)
    clrlwi  r10, r7, 1
    fmr     f0, f1
    stfs    f0, 0x8(r1)
    lwz     r8, 0x8(r1)
    clrlwi  r11, r8, 1
    lis     r0, 0x7f80
    cmpw    r10, r0
    bgt     L_nan
    cmpw    r11, r0
    ble     L_notnan
L_nan:
    fadds   f1, f2, f1
    b       L_end
L_notnan:
    lis     r0, 0x3f80
    cmpw    r7, r0
    bne     L_notone
    bl      atanf
    b       L_end
L_notone:
    srwi    r9, r8, 31
    rlwinm  r0, r7, 2, 30, 30
    or      r31, r9, r0
    cmpwi   r11, 0
    bne     L_ynz
    cmpwi   r31, 2
    beq     L_pi
    ble     L_ylow
    cmpwi   r31, 3
    beq     L_mpi
    b       L_ynz
L_ylow:
    cmpwi   r31, 0
    bge     L_end
L_ynz:
    cmpwi   r10, 0
    bne     L_xnz
L_xzero:
    cmpwi   r8, 0
    lfs     f1, Atan2fPiO2Const
    bge     L_end
    lfs     f1, Atan2fNegPiO2Const
    b       L_end
L_xnz:
    lis     r0, 0x7f80
    cmpw    r10, r0
    bne     L_xfin
    cmpw    r11, r10
    bne     L_yfin
    cmpwi   r31, 1
    beq     L_ii1
    bgt     L_ii23
    cmpwi   r31, 0
    beq     L_ii0
    b       L_xfin
L_ii23:
    cmpwi   r31, 2
    beq     L_ii2
    cmpwi   r31, 3
    beq     L_ii3
    b       L_xfin
L_ii0:
    lfs     f1, Atan2fPiO4Const
    b       L_end
L_ii1:
    lfs     f1, Atan2fNegPiO4Const
    b       L_end
L_ii2:
    lfs     f1, Atan2f3PiO4Const
    b       L_end
L_ii3:
    lfs     f1, Atan2fNeg3PiO4Const
    b       L_end
L_yfin:
    cmpwi   r31, 1
    beq     L_if1
    bgt     L_if23
    cmpwi   r31, 0
    beq     L_if0
    b       L_xfin
L_if23:
    cmpwi   r31, 2
    beq     L_pi
    cmpwi   r31, 3
    beq     L_mpi
    b       L_xfin
L_if0:
    lfs     f1, Atan2fZeroConst.v
    b       L_end
L_if1:
    lfs     f1, Atan2fNegZeroConst
    b       L_end
L_pi:
    lfs     f1, Atan2fPiConst
    b       L_end
L_mpi:
    lfs     f1, Atan2fNegPiConst
    b       L_end
L_xfin:
    lis     r0, 0x7f80
    cmpw    r11, r0
    beq     L_xzero
    subf    r0, r10, r11
    srawi   r0, r0, 23
    cmpwi   r0, 0x3c
    ble     L_kle
    lfs     f13, Atan2fPiO2HiConst
    b       L_zdone
L_kle:
    cmpwi   r7, 0
    bge     L_div
    cmpwi   r0, -0x3c
    bge     L_div
    lfs     f13, Atan2fZeroConst.v
    b       L_zdone
L_div:
    fdivs   f1, f1, f2
    bl      fabsf
    bl      atanf
    fmr     f13, f1
L_zdone:
    cmpwi   r31, 1
    beq     L_m1
    bgt     L_m23
    cmpwi   r31, 0
    beq     L_m0
    b       L_m3
L_m23:
    cmpwi   r31, 2
    beq     L_m2
    b       L_m3
L_m1:
    stfs    f13, 0x8(r1)
    lwz     r0, 0x8(r1)
    xoris   r0, r0, 0x8000
    stw     r0, 0x8(r1)
    lfs     f13, 0x8(r1)
L_m0:
    fmr     f1, f13
    b       L_end
L_m2:
    lfs     f1, Atan2fPiLoConst
    lfs     f0, Atan2fPiConst
    fsubs   f1, f13, f1
    fsubs   f1, f0, f1
    b       L_end
L_m3:
    lfs     f1, Atan2fPiLoConst
    lfs     f0, Atan2fPiConst
    fsubs   f1, f13, f1
    fsubs   f1, f1, f0
L_end:
    lwz     r0, 0x1c(r1)
    mtlr    r0
    lwz     r31, 0x14(r1)
    addi    r1, r1, 0x18
    blr
    // clang-format on
}
