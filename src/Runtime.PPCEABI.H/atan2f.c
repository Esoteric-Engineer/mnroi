extern float lbl_8066C0A0;
extern float lbl_8066C0A4;
extern float lbl_8066C0A8;
extern float lbl_8066C0AC;
extern float lbl_8066C0B0;
extern float lbl_8066C0B4;
extern float lbl_8066C0B8;
extern float lbl_8066C0BC;
extern float lbl_8066C0C0;
extern float lbl_8066C0C4;
extern float lbl_8066C0C8;
extern float lbl_8066C0CC;
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
    lfs     f1, lbl_8066C0AC
    bge     L_end
    lfs     f1, lbl_8066C0A8
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
    lfs     f1, lbl_8066C0B0
    b       L_end
L_ii1:
    lfs     f1, lbl_8066C0B4
    b       L_end
L_ii2:
    lfs     f1, lbl_8066C0B8
    b       L_end
L_ii3:
    lfs     f1, lbl_8066C0BC
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
    lfs     f1, lbl_8066C0C0
    b       L_end
L_if1:
    lfs     f1, lbl_8066C0C4
    b       L_end
L_pi:
    lfs     f1, lbl_8066C0A0
    b       L_end
L_mpi:
    lfs     f1, lbl_8066C0A4
    b       L_end
L_xfin:
    lis     r0, 0x7f80
    cmpw    r11, r0
    beq     L_xzero
    subf    r0, r10, r11
    srawi   r0, r0, 23
    cmpwi   r0, 0x3c
    ble     L_kle
    lfs     f13, lbl_8066C0C8
    b       L_zdone
L_kle:
    cmpwi   r7, 0
    bge     L_div
    cmpwi   r0, -0x3c
    bge     L_div
    lfs     f13, lbl_8066C0C0
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
    lfs     f1, lbl_8066C0CC
    lfs     f0, lbl_8066C0A0
    fsubs   f1, f13, f1
    fsubs   f1, f0, f1
    b       L_end
L_m3:
    lfs     f1, lbl_8066C0CC
    lfs     f0, lbl_8066C0A0
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
