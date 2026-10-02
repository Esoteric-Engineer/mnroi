#pragma force_active on

/* ef_rem_pio2.c scalars, in .sdata address order (not source order). */
struct { float v; } RemPio2fZeroConst = { 0.0f }; /* zero */
float RemPio2fPio2_1Const = 1.5707855225e+00f;    /* pio2_1 */
float RemPio2fPio2_1tConst = 1.0804334124e-05f;   /* pio2_1t */
float RemPio2fPio2_2Const = 1.0804273188e-05f;    /* pio2_2 */
float RemPio2fPio2_2tConst = 6.0770999344e-11f;   /* pio2_2t */
float RemPio2fInvPio2Const = 6.3661980629e-01f;   /* invpio2 */
float RemPio2fHalfConst = 5.0000000000e-01f;      /* half */
double RemPio2fCvtConst = 4503601774854144.0;     /* MWCC's (float)n magic, not in ef_rem_pio2.c */
float RemPio2fPio2_3Const = 6.0770943833e-11f;    /* pio2_3 */
float RemPio2fPio2_3tConst = 6.1232342629e-17f;   /* pio2_3t */
float RemPio2fTwo8Const = 2.5600000000e+02f;      /* two8 */

/* __kernel_tanf.c's KernelTanfT8..T12 (kf_tan.c's T[8..12]).
Widens this unit's .sdata2 claim back to their 8-aligned start. */
const float KernelTanfT8 = 2.4646313977e-04f;  /* 0x398137b9 */
const float KernelTanfT9 = 7.8179444245e-05f;  /* 0x38a3f445 */
const float KernelTanfT10 = 7.1407252108e-05f; /* 0x3895c07a */
const float KernelTanfT11 = -1.8558637748e-05f; /* 0xb79bae5f */
const float KernelTanfT12 = 2.5907305826e-05f; /* 0x37d95384 */

/* two_over_pi[198], split into scalars so each stays under the .sdata2 threshold. */
const int RemPio2fTwoOverPi0 = 0xA2;
const int RemPio2fTwoOverPi1 = 0xF9;
const int RemPio2fTwoOverPi2 = 0x83;
const int RemPio2fTwoOverPi3 = 0x6E;
const int RemPio2fTwoOverPi4 = 0x4E;
const int RemPio2fTwoOverPi5 = 0x44;
const int RemPio2fTwoOverPi6 = 0x15;
const int RemPio2fTwoOverPi7 = 0x29;
const int RemPio2fTwoOverPi8 = 0xFC;
const int RemPio2fTwoOverPi9 = 0x27;
const int RemPio2fTwoOverPi10 = 0x57;
const int RemPio2fTwoOverPi11 = 0xD1;
const int RemPio2fTwoOverPi12 = 0xF5;
const int RemPio2fTwoOverPi13 = 0x34;
const int RemPio2fTwoOverPi14 = 0xDD;
const int RemPio2fTwoOverPi15 = 0xC0;
const int RemPio2fTwoOverPi16 = 0xDB;
const int RemPio2fTwoOverPi17 = 0x62;
const int RemPio2fTwoOverPi18 = 0x95;
const int RemPio2fTwoOverPi19 = 0x99;
const int RemPio2fTwoOverPi20 = 0x3C;
const int RemPio2fTwoOverPi21 = 0x43;
const int RemPio2fTwoOverPi22 = 0x90;
const int RemPio2fTwoOverPi23 = 0x41;
const int RemPio2fTwoOverPi24 = 0xFE;
const int RemPio2fTwoOverPi25 = 0x51;
const int RemPio2fTwoOverPi26 = 0x63;
const int RemPio2fTwoOverPi27 = 0xAB;
const int RemPio2fTwoOverPi28 = 0xDE;
const int RemPio2fTwoOverPi29 = 0xBB;
const int RemPio2fTwoOverPi30 = 0xC5;
const int RemPio2fTwoOverPi31 = 0x61;
const int RemPio2fTwoOverPi32 = 0xB7;
const int RemPio2fTwoOverPi33 = 0x24;
const int RemPio2fTwoOverPi34 = 0x6E;
const int RemPio2fTwoOverPi35 = 0x3A;
const int RemPio2fTwoOverPi36 = 0x42;
const int RemPio2fTwoOverPi37 = 0x4D;
const int RemPio2fTwoOverPi38 = 0xD2;
const int RemPio2fTwoOverPi39 = 0xE0;
const int RemPio2fTwoOverPi40 = 0x06;
const int RemPio2fTwoOverPi41 = 0x49;
const int RemPio2fTwoOverPi42 = 0x2E;
const int RemPio2fTwoOverPi43 = 0xEA;
const int RemPio2fTwoOverPi44 = 0x09;
const int RemPio2fTwoOverPi45 = 0xD1;
const int RemPio2fTwoOverPi46 = 0x92;
const int RemPio2fTwoOverPi47 = 0x1C;
const int RemPio2fTwoOverPi48 = 0xFE;
const int RemPio2fTwoOverPi49 = 0x1D;
const int RemPio2fTwoOverPi50 = 0xEB;
const int RemPio2fTwoOverPi51 = 0x1C;
const int RemPio2fTwoOverPi52 = 0xB1;
const int RemPio2fTwoOverPi53 = 0x29;
const int RemPio2fTwoOverPi54 = 0xA7;
const int RemPio2fTwoOverPi55 = 0x3E;
const int RemPio2fTwoOverPi56 = 0xE8;
const int RemPio2fTwoOverPi57 = 0x82;
const int RemPio2fTwoOverPi58 = 0x35;
const int RemPio2fTwoOverPi59 = 0xF5;
const int RemPio2fTwoOverPi60 = 0x2E;
const int RemPio2fTwoOverPi61 = 0xBB;
const int RemPio2fTwoOverPi62 = 0x44;
const int RemPio2fTwoOverPi63 = 0x84;
const int RemPio2fTwoOverPi64 = 0xE9;
const int RemPio2fTwoOverPi65 = 0x9C;
const int RemPio2fTwoOverPi66 = 0x70;
const int RemPio2fTwoOverPi67 = 0x26;
const int RemPio2fTwoOverPi68 = 0xB4;
const int RemPio2fTwoOverPi69 = 0x5F;
const int RemPio2fTwoOverPi70 = 0x7E;
const int RemPio2fTwoOverPi71 = 0x41;
const int RemPio2fTwoOverPi72 = 0x39;
const int RemPio2fTwoOverPi73 = 0x91;
const int RemPio2fTwoOverPi74 = 0xD6;
const int RemPio2fTwoOverPi75 = 0x39;
const int RemPio2fTwoOverPi76 = 0x83;
const int RemPio2fTwoOverPi77 = 0x53;
const int RemPio2fTwoOverPi78 = 0x39;
const int RemPio2fTwoOverPi79 = 0xF4;
const int RemPio2fTwoOverPi80 = 0x9C;
const int RemPio2fTwoOverPi81 = 0x84;
const int RemPio2fTwoOverPi82 = 0x5F;
const int RemPio2fTwoOverPi83 = 0x8B;
const int RemPio2fTwoOverPi84 = 0xBD;
const int RemPio2fTwoOverPi85 = 0xF9;
const int RemPio2fTwoOverPi86 = 0x28;
const int RemPio2fTwoOverPi87 = 0x3B;
const int RemPio2fTwoOverPi88 = 0x1F;
const int RemPio2fTwoOverPi89 = 0xF8;
const int RemPio2fTwoOverPi90 = 0x97;
const int RemPio2fTwoOverPi91 = 0xFF;
const int RemPio2fTwoOverPi92 = 0xDE;
const int RemPio2fTwoOverPi93 = 0x05;
const int RemPio2fTwoOverPi94 = 0x98;
const int RemPio2fTwoOverPi95 = 0x0F;
const int RemPio2fTwoOverPi96 = 0xEF;
const int RemPio2fTwoOverPi97 = 0x2F;
const int RemPio2fTwoOverPi98 = 0x11;
const int RemPio2fTwoOverPi99 = 0x8B;
const int RemPio2fTwoOverPi100 = 0x5A;
const int RemPio2fTwoOverPi101 = 0x0A;
const int RemPio2fTwoOverPi102 = 0x6D;
const int RemPio2fTwoOverPi103 = 0x1F;
const int RemPio2fTwoOverPi104 = 0x6D;
const int RemPio2fTwoOverPi105 = 0x36;
const int RemPio2fTwoOverPi106 = 0x7E;
const int RemPio2fTwoOverPi107 = 0xCF;
const int RemPio2fTwoOverPi108 = 0x27;
const int RemPio2fTwoOverPi109 = 0xCB;
const int RemPio2fTwoOverPi110 = 0x09;
const int RemPio2fTwoOverPi111 = 0xB7;
const int RemPio2fTwoOverPi112 = 0x4F;
const int RemPio2fTwoOverPi113 = 0x46;
const int RemPio2fTwoOverPi114 = 0x3F;
const int RemPio2fTwoOverPi115 = 0x66;
const int RemPio2fTwoOverPi116 = 0x9E;
const int RemPio2fTwoOverPi117 = 0x5F;
const int RemPio2fTwoOverPi118 = 0xEA;
const int RemPio2fTwoOverPi119 = 0x2D;
const int RemPio2fTwoOverPi120 = 0x75;
const int RemPio2fTwoOverPi121 = 0x27;
const int RemPio2fTwoOverPi122 = 0xBA;
const int RemPio2fTwoOverPi123 = 0xC7;
const int RemPio2fTwoOverPi124 = 0xEB;
const int RemPio2fTwoOverPi125 = 0xE5;
const int RemPio2fTwoOverPi126 = 0xF1;
const int RemPio2fTwoOverPi127 = 0x7B;
const int RemPio2fTwoOverPi128 = 0x3D;
const int RemPio2fTwoOverPi129 = 0x07;
const int RemPio2fTwoOverPi130 = 0x39;
const int RemPio2fTwoOverPi131 = 0xF7;
const int RemPio2fTwoOverPi132 = 0x8A;
const int RemPio2fTwoOverPi133 = 0x52;
const int RemPio2fTwoOverPi134 = 0x92;
const int RemPio2fTwoOverPi135 = 0xEA;
const int RemPio2fTwoOverPi136 = 0x6B;
const int RemPio2fTwoOverPi137 = 0xFB;
const int RemPio2fTwoOverPi138 = 0x5F;
const int RemPio2fTwoOverPi139 = 0xB1;
const int RemPio2fTwoOverPi140 = 0x1F;
const int RemPio2fTwoOverPi141 = 0x8D;
const int RemPio2fTwoOverPi142 = 0x5D;
const int RemPio2fTwoOverPi143 = 0x08;
const int RemPio2fTwoOverPi144 = 0x56;
const int RemPio2fTwoOverPi145 = 0x03;
const int RemPio2fTwoOverPi146 = 0x30;
const int RemPio2fTwoOverPi147 = 0x46;
const int RemPio2fTwoOverPi148 = 0xFC;
const int RemPio2fTwoOverPi149 = 0x7B;
const int RemPio2fTwoOverPi150 = 0x6B;
const int RemPio2fTwoOverPi151 = 0xAB;
const int RemPio2fTwoOverPi152 = 0xF0;
const int RemPio2fTwoOverPi153 = 0xCF;
const int RemPio2fTwoOverPi154 = 0xBC;
const int RemPio2fTwoOverPi155 = 0x20;
const int RemPio2fTwoOverPi156 = 0x9A;
const int RemPio2fTwoOverPi157 = 0xF4;
const int RemPio2fTwoOverPi158 = 0x36;
const int RemPio2fTwoOverPi159 = 0x1D;
const int RemPio2fTwoOverPi160 = 0xA9;
const int RemPio2fTwoOverPi161 = 0xE3;
const int RemPio2fTwoOverPi162 = 0x91;
const int RemPio2fTwoOverPi163 = 0x61;
const int RemPio2fTwoOverPi164 = 0x5E;
const int RemPio2fTwoOverPi165 = 0xE6;
const int RemPio2fTwoOverPi166 = 0x1B;
const int RemPio2fTwoOverPi167 = 0x08;
const int RemPio2fTwoOverPi168 = 0x65;
const int RemPio2fTwoOverPi169 = 0x99;
const int RemPio2fTwoOverPi170 = 0x85;
const int RemPio2fTwoOverPi171 = 0x5F;
const int RemPio2fTwoOverPi172 = 0x14;
const int RemPio2fTwoOverPi173 = 0xA0;
const int RemPio2fTwoOverPi174 = 0x68;
const int RemPio2fTwoOverPi175 = 0x40;
const int RemPio2fTwoOverPi176 = 0x8D;
const int RemPio2fTwoOverPi177 = 0xFF;
const int RemPio2fTwoOverPi178 = 0xD8;
const int RemPio2fTwoOverPi179 = 0x80;
const int RemPio2fTwoOverPi180 = 0x4D;
const int RemPio2fTwoOverPi181 = 0x73;
const int RemPio2fTwoOverPi182 = 0x27;
const int RemPio2fTwoOverPi183 = 0x31;
const int RemPio2fTwoOverPi184 = 0x06;
const int RemPio2fTwoOverPi185 = 0x06;
const int RemPio2fTwoOverPi186 = 0x15;
const int RemPio2fTwoOverPi187 = 0x56;
const int RemPio2fTwoOverPi188 = 0xCA;
const int RemPio2fTwoOverPi189 = 0x73;
const int RemPio2fTwoOverPi190 = 0xA8;
const int RemPio2fTwoOverPi191 = 0xC9;
const int RemPio2fTwoOverPi192 = 0x60;
const int RemPio2fTwoOverPi193 = 0xE2;
const int RemPio2fTwoOverPi194 = 0x7B;
const int RemPio2fTwoOverPi195 = 0xC0;
const int RemPio2fTwoOverPi196 = 0x8C;
const int RemPio2fTwoOverPi197 = 0x6B;

/* npio2_hw[32], split the same way. */
const int RemPio2fNpio2Hw0 = 0x3fc90f00;
const int RemPio2fNpio2Hw1 = 0x40490f00;
const int RemPio2fNpio2Hw2 = 0x4096cb00;
const int RemPio2fNpio2Hw3 = 0x40c90f00;
const int RemPio2fNpio2Hw4 = 0x40fb5300;
const int RemPio2fNpio2Hw5 = 0x4116cb00;
const int RemPio2fNpio2Hw6 = 0x412fed00;
const int RemPio2fNpio2Hw7 = 0x41490f00;
const int RemPio2fNpio2Hw8 = 0x41623100;
const int RemPio2fNpio2Hw9 = 0x417b5300;
const int RemPio2fNpio2Hw10 = 0x418a3a00;
const int RemPio2fNpio2Hw11 = 0x4196cb00;
const int RemPio2fNpio2Hw12 = 0x41a35c00;
const int RemPio2fNpio2Hw13 = 0x41afed00;
const int RemPio2fNpio2Hw14 = 0x41bc7e00;
const int RemPio2fNpio2Hw15 = 0x41c90f00;
const int RemPio2fNpio2Hw16 = 0x41d5a000;
const int RemPio2fNpio2Hw17 = 0x41e23100;
const int RemPio2fNpio2Hw18 = 0x41eec200;
const int RemPio2fNpio2Hw19 = 0x41fb5300;
const int RemPio2fNpio2Hw20 = 0x4203f200;
const int RemPio2fNpio2Hw21 = 0x420a3a00;
const int RemPio2fNpio2Hw22 = 0x42108300;
const int RemPio2fNpio2Hw23 = 0x4216cb00;
const int RemPio2fNpio2Hw24 = 0x421d1400;
const int RemPio2fNpio2Hw25 = 0x42235c00;
const int RemPio2fNpio2Hw26 = 0x4229a500;
const int RemPio2fNpio2Hw27 = 0x422fed00;
const int RemPio2fNpio2Hw28 = 0x42363600;
const int RemPio2fNpio2Hw29 = 0x423c7e00;
const int RemPio2fNpio2Hw30 = 0x4242c700;
const int RemPio2fNpio2Hw31 = 0x42490f00;

extern float fabsf(float x);
extern int __kernel_rem_pio2f(float* x, float* y, int e0, int nx, int prec, const int* ipio2);

asm int __ieee754_rem_pio2f(float x, float* y)
{
    // clang-format off
    nofralloc
    stwu    r1, -0x40(r1)
    mflr    r0
    stmw    r29, 0x34(r1)
    stw     r0, 0x44(r1)
    mr      r31, r3
    fmr     f0, f1
    stfs    f0, 0x18(r1)
    lwz     r29, 0x18(r1)
    clrlwi  r30, r29, 1
    lis     r0, 0x3f49
    ori     r0, r0, 0xfd8
    cmpw    r30, r0
    bgt     L_reduce
    lfs     f0, RemPio2fZeroConst.v
    li      r3, 0
    stfs    f1, 0(r31)
    b       L_ret_y1
L_reduce:
    lis     r0, 0x4016
    ori     r0, r0, 0xcbe3
    cmpw    r30, r0
    bgt     L_medium
    cmpwi   r29, 0
    ble     L_neg
    lfs     f0, RemPio2fPio2_1Const
    lis     r0, 0x3fc9
    rlwinm  r9, r29, 0, 1, 27
    ori     r0, r0, 0xfd0
    fsubs   f1, f1, f0
    cmpw    r9, r0
    beq     L_pos_near
    lfs     f12, RemPio2fPio2_1tConst
    b       L_pos_fin
L_pos_near:
    lfs     f0, RemPio2fPio2_2Const
    lfs     f12, RemPio2fPio2_2tConst
    fsubs   f1, f1, f0
L_pos_fin:
    fsubs   f13, f1, f12
    fsubs   f0, f1, f13
    stfs    f13, 0(r31)
    fsubs   f0, f0, f12
    stfs    f0, 4(r31)
    li      r3, 1
    b       L_end
L_neg:
    lfs     f0, RemPio2fPio2_1Const
    lis     r0, 0x3fc9
    rlwinm  r9, r29, 0, 1, 27
    ori     r0, r0, 0xfd0
    fadds   f1, f1, f0
    cmpw    r9, r0
    beq     L_neg_near
    lfs     f12, RemPio2fPio2_1tConst
    b       L_neg_fin
L_neg_near:
    lfs     f0, RemPio2fPio2_2Const
    lfs     f12, RemPio2fPio2_2tConst
    fadds   f1, f1, f0
L_neg_fin:
    fadds   f13, f1, f12
    fsubs   f0, f1, f13
    stfs    f13, 0(r31)
    fadds   f0, f0, f12
    stfs    f0, 4(r31)
    li      r3, -1
    b       L_end
L_medium:
    lis     r0, 0x4349
    ori     r0, r0, 0xf80
    cmpw    r30, r0
    bgt     L_large
    bl      fabsf
    lfs     f13, RemPio2fHalfConst
    fmr     f9, f1
    lfs     f0, RemPio2fInvPio2Const
    mr      r9, r11
    lis     r10, 0x4330
    fmadds  f0, f9, f0, f13
    lfd     f11, RemPio2fCvtConst
    lfs     f13, RemPio2fPio2_1Const
    fctiwz  f12, f0
    lfs     f10, RemPio2fPio2_1tConst
    stfd    f12, 0x28(r1)
    lwz     r3, 0x2c(r1)
    xoris   r0, r3, 0x8000
    cmpwi   r3, 0x1f
    stw     r0, 0x2c(r1)
    stw     r10, 0x28(r1)
    lfd     f0, 0x28(r1)
    fsub    f0, f0, f11
    frsp    f8, f0
    fmuls   f13, f8, f13
    fsubs   f11, f9, f13
    fmuls   f1, f8, f10
    bgt     L_iter1
    subi    r0, r3, 1
    la      r10, RemPio2fNpio2Hw0
    slwi    r0, r0, 2
    rlwinm  r11, r29, 0, 1, 23
    lwzx    r9, r10, r0
    cmpw    r11, r9
    beq     L_iter1
    fsubs   f0, f11, f1
    stfs    f0, 0(r31)
    b       L_med_fin
L_iter1:
    fsubs   f0, f11, f1
    srawi   r9, r30, 23
    stfs    f0, 0(r31)
    stfs    f0, 0x18(r1)
    lwz     r0, 0x18(r1)
    extrwi  r0, r0, 8, 1
    subf    r0, r0, r9
    cmpwi   r0, 8
    ble     L_med_fin
    lfs     f0, RemPio2fPio2_2Const
    fmr     f9, f11
    lfs     f12, RemPio2fPio2_2tConst
    fmuls   f1, f8, f0
    fsubs   f11, f11, f1
    fsubs   f0, f9, f11
    fsubs   f0, f0, f1
    fmsubs  f1, f8, f12, f0
    fsubs   f13, f11, f1
    stfs    f13, 0(r31)
    stfs    f13, 0x18(r1)
    lwz     r0, 0x18(r1)
    extrwi  r0, r0, 8, 1
    subf    r0, r0, r9
    cmpwi   r0, 0x19
    ble     L_med_fin
    lfs     f0, RemPio2fPio2_3Const
    fmr     f9, f11
    lfs     f12, RemPio2fPio2_3tConst
    fmuls   f1, f8, f0
    fsubs   f11, f11, f1
    fsubs   f0, f9, f11
    fsubs   f0, f0, f1
    fmsubs  f1, f8, f12, f0
    fsubs   f13, f11, f1
    stfs    f13, 0(r31)
L_med_fin:
    lfs     f13, 0(r31)
    cmpwi   r29, 0
    fsubs   f0, f11, f13
    fsubs   f0, f0, f1
    stfs    f0, 4(r31)
    bge     L_end
    fneg    f13, f13
    neg     r3, r3
    b       L_negate
L_large:
    lis     r0, 0x7f7f
    ori     r0, r0, 0xffff
    cmpw    r30, r0
    ble     L_finite
    fsubs   f0, f1, f1
    li      r3, 0
    stfs    f0, 0(r31)
    b       L_ret_y1
L_finite:
    srawi   r9, r30, 23
    subi    r5, r9, 0x86
    slwi    r0, r5, 23
    subf    r30, r0, r30
    stw     r30, 0x18(r1)
    lfs     f1, 0x18(r1)
    cmpwi   r29, 0
    addi    r8, r1, 8
    lfd     f12, RemPio2fCvtConst
    lfs     f11, RemPio2fTwo8Const
    mfcr    r30
    lis     r7, 0x4330
    mr      r10, r8
    addi    r0, r1, 0xc
L_loop:
    fmr     f0, f1
    fctiwz  f13, f0
    mr      r11, r9
    stfd    f13, 0x28(r1)
    lwz     r9, 0x2c(r1)
    xoris   r9, r9, 0x8000
    stw     r9, 0x2c(r1)
    stw     r7, 0x28(r1)
    lfd     f0, 0x28(r1)
    fsub    f0, f0, f12
    frsp    f0, f0
    stfs    f0, 0(r10)
    fsubs   f0, f1, f0
    addi    r10, r10, 4
    fmuls   f1, f0, f11
    cmpw    r10, r0
    ble     L_loop
    stfs    f1, 0x10(r1)
    li      r6, 3
    lfs     f13, RemPio2fZeroConst.v
    lfs     f0, 8(r8)
    fcmpu   cr0, f0, f13
    bne     L_call
    addi    r9, r8, 8
L_skip:
    lfsu    f0, -4(r9)
    subi    r6, r6, 1
    fcmpu   cr0, f0, f13
    beq     L_skip
L_call:
    addi    r3, r1, 8
    mr      r4, r31
    li      r7, 2
    la      r8, RemPio2fTwoOverPi0
    bl      __kernel_rem_pio2f
    mtcrf   128, r30
    bge     L_end
    lfs     f13, 0(r31)
    neg     r3, r3
    lfs     f0, 4(r31)
    fneg    f13, f13
L_negate:
    fneg    f0, f0
    stfs    f13, 0(r31)
L_ret_y1:
    stfs    f0, 4(r31)
L_end:
    lwz     r0, 0x44(r1)
    mtlr    r0
    lmw     r29, 0x34(r1)
    addi    r1, r1, 0x40
    blr
    // clang-format on
}
