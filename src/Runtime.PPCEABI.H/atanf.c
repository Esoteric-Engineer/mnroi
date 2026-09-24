extern float lbl_8066C160;
extern float lbl_8066C164;
extern float lbl_8066C168;
extern float lbl_8066C16C;
extern float lbl_8066C170;
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
    lfs     f0, -0x389c(r13)
    lfs     f1, -0x388c(r13)
    fadds   f1, f0, f1
    b       L_DC6C
L_DAD0:
    lfs     f1, -0x389c(r13)
    lfs     f0, -0x388c(r13)
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
    lfs     f0, lbl_8066C160
    lfs     f13, lbl_8066C164
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
    lfs     f12, lbl_8066C164
    fadds   f13, f5, f5
    lfs     f0, lbl_8066C168
    li      r0, 0x0
    fsubs   f13, f13, f12
    fadds   f0, f5, f0
    fdivs   f5, f13, f0
    b       L_DBC4
L_DB74:
    lfs     f0, lbl_8066C164
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
    lfs     f0, lbl_8066C16C
    li      r0, 0x2
    lfs     f13, lbl_8066C164
    fsubs   f12, f5, f0
    fmadds  f0, f5, f0, f13
    fdivs   f5, f12, f0
    b       L_DBC4
L_DBB8:
    lfs     f0, lbl_8066C170
    li      r0, 0x3
    fdivs   f5, f0, f5
L_DBC4:
    fmuls   f6, f5, f5
    lfs     f10, -0x3868(r13)
    lfs     f13, -0x3860(r13)
    fmuls   f12, f6, f6
    lfs     f9, -0x3870(r13)
    cmpwi   r0, 0x0
    fmadds  f13, f12, f13, f10
    lfs     f11, -0x386c(r13)
    fmadds  f13, f12, f13, f9
    lfs     f10, -0x3878(r13)
    lfs     f0, -0x3864(r13)
    lfs     f9, -0x3874(r13)
    fmadds  f13, f12, f13, f10
    fmadds  f0, f12, f0, f11
    lfs     f8, -0x3880(r13)
    lfs     f7, -0x387c(r13)
    fmadds  f0, f12, f0, f9
    lfs     f10, -0x3888(r13)
    fmadds  f13, f12, f13, f8
    lfs     f11, -0x3884(r13)
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
    subi    r9, r13, 0x3898
    lfsx    f12, r9, r0
    fadds   f0, f1, f0
    subi    r9, r13, 0x38a8
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
