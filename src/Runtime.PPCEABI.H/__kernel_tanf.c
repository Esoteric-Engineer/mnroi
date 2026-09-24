extern float lbl_8066C2A8;
extern float lbl_8066C2AC;
extern float lbl_8066C2B0;
extern float lbl_8066C2B4;
extern float lbl_8066C2B8;
extern double lbl_8066C2C0;
extern float fabsf(float x);

asm float __kernel_tanf(float x, float y, int iy)
{
    // clang-format off
    nofralloc
    stwu    r1, -0x18(r1)
    mflr    r0
    stw     r0, 0x1c(r1)
    fmr     f6, f1
    fmr     f0, f6
    stfs    f0, 8(r1)
    lwz     r8, 8(r1)
    clrlwi  r11, r8, 1
    lis     r0, 0x317f
    ori     r0, r0, 0xffff
    cmpw    r11, r0
    bgt     L_big
    fmr     f0, f6
    fctiwz  f13, f0
    stfd    f13, 0x10(r1)
    lwz     r9, 0x14(r1)
    cmpwi   r9, 0
    bne     L_big
    addi    r0, r3, 1
    or.     r9, r11, r0
    bne     L_nz
    bl      fabsf
    lfs     f0, lbl_8066C2A8
    fdivs   f1, f0, f1
    b       L_end
L_nz:
    cmpwi   r3, 1
    beq     L_iy1
    lfs     f0, lbl_8066C2AC
    fdivs   f1, f0, f6
    b       L_end
L_iy1:
    fmr     f1, f6
    b       L_end
L_big:
    lis     r0, 0x3f2c
    ori     r0, r0, 0xa13f
    cmpw    r11, r0
    ble     L_poly
    cmpwi   r8, 0
    bge     L_pos
    fneg    f6, f6
    fneg    f2, f2
L_pos:
    lfs     f0, lbl_8066C2B4
    lfs     f13, lbl_8066C2B0
    fsubs   f1, f0, f2
    fsubs   f7, f13, f6
    lfs     f2, lbl_8066C2B8
    fadds   f6, f7, f1
L_poly:
    fmuls   f7, f6, f6
    lfs     f12, -0x36ac(r13)
    lfs     f13, -0x36a4(r13)
    fmuls   f1, f7, f7
    lfs     f11, -0x36a8(r13)
    fmuls   f5, f7, f6
    lfs     f0, -0x36a0(r13)
    fmadds  f13, f1, f13, f12
    lfs     f10, -0x36b4(r13)
    lis     r0, 0x3f2c
    fmadds  f0, f1, f0, f11
    lfs     f12, -0x36b0(r13)
    lfs     f11, -0x36b8(r13)
    fmadds  f13, f1, f13, f10
    fmadds  f0, f1, f0, f12
    lfs     f9, -0x36bc(r13)
    fmadds  f0, f1, f0, f11
    lfs     f10, -0x36c4(r13)
    lfs     f8, -0x36c0(r13)
    fmadds  f13, f1, f13, f9
    lfs     f12, -0x36cc(r13)
    fmadds  f13, f1, f13, f10
    lfs     f11, -0x36c8(r13)
    fmadds  f0, f1, f0, f8
    fmadds  f9, f1, f13, f12
    lfs     f10, -0x36d0(r13)
    fmadds  f0, f1, f0, f11
    ori     r0, r0, 0xa13f
    fmadds  f0, f7, f0, f9
    cmpw    r11, r0
    fmadds  f0, f5, f0, f2
    fmadds  f9, f7, f0, f2
    fmadds  f9, f10, f5, f9
    fadds   f1, f6, f9
    ble     L_le
    xoris   r0, r3, 0x8000
    stw     r0, 0x14(r1)
    lis     r10, 0x4330
    lfd     f12, lbl_8066C2C0
    fmuls   f13, f1, f1
    stw     r10, 0x10(r1)
    rlwinm  r0, r8, 2, 30, 30
    subfic  r0, r0, 1
    mr      r11, r9
    lfd     f0, 0x10(r1)
    xoris   r0, r0, 0x8000
    stw     r0, 0x14(r1)
    fsub    f0, f0, f12
    frsp    f11, f0
    stw     r10, 0x10(r1)
    fadds   f0, f1, f11
    fdivs   f13, f13, f0
    lfd     f1, 0x10(r1)
    fsubs   f13, f13, f9
    fsubs   f13, f6, f13
    fsub    f1, f1, f12
    fadds   f13, f13, f13
    fsubs   f13, f11, f13
    frsp    f1, f1
    fmuls   f1, f1, f13
    b       L_end
L_le:
    cmpwi   r3, 1
    beq     L_end
    lfs     f13, lbl_8066C2AC
    fmr     f0, f1
    stfs    f0, 8(r1)
    fdivs   f13, f13, f1
    lfs     f12, lbl_8066C2A8
    lwz     r0, 8(r1)
    clrrwi  r9, r0, 12
    stw     r9, 8(r1)
    lfs     f7, 8(r1)
    fmr     f0, f13
    stfs    f0, 8(r1)
    fsubs   f0, f7, f6
    lwz     r0, 8(r1)
    fsubs   f11, f9, f0
    clrrwi  r9, r0, 12
    stw     r9, 8(r1)
    lfs     f1, 8(r1)
    fmadds  f5, f1, f7, f12
    fmadds  f0, f1, f11, f5
    fmadds  f1, f13, f0, f1
L_end:
    lwz     r0, 0x1c(r1)
    mtlr    r0
    addi    r1, r1, 0x18
    blr
    // clang-format on
}
