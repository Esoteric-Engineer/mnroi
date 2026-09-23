extern float lbl_8066C28C;
extern float lbl_8066C290;
extern float lbl_8066C294;
extern float lbl_8066C298;
extern float lbl_8066C29C;
extern float lbl_8066C2A0;
extern float lbl_8066C2A4;

asm float __kernel_sinf(float x, float y, int iy)
{
    // clang-format off
    nofralloc
    stwu    r1, -0x18(r1)
    fmr     f9, f1
    fmr     f0, f9
    stfs    f0, 8(r1)
    lwz     r9, 8(r1)
    clrlwi  r9, r9, 1
    lis     r0, 0x31ff
    ori     r0, r0, 0xffff
    cmpw    r9, r0
    bgt     L_big
    fmr     f0, f9
    fctiwz  f13, f0
    stfd    f13, 0x10(r1)
    lwz     r9, 0x14(r1)
    cmpwi   r9, 0
    beq     L_end
L_big:
    lfs     f13, lbl_8066C290
    fmuls   f10, f9, f9
    lfs     f0, lbl_8066C28C
    fmuls   f8, f10, f9
    lfs     f11, lbl_8066C294
    cmpwi   r3, 0
    fmadds  f0, f10, f0, f13
    lfs     f12, lbl_8066C298
    fmadds  f0, f10, f0, f11
    lfs     f13, lbl_8066C29C
    fmadds  f0, f10, f0, f12
    fmadds  f0, f10, f0, f13
    beq     L_iy0
    fmuls   f13, f8, f0
    lfs     f1, lbl_8066C2A4
    lfs     f0, lbl_8066C2A0
    fmsubs  f1, f2, f1, f13
    fmsubs  f1, f10, f1, f2
    fmuls   f0, f8, f0
    fsubs   f1, f1, f0
    fsubs   f1, f9, f1
    b       L_end
L_iy0:
    lfs     f1, lbl_8066C2A0
    fmadds  f1, f10, f0, f1
    fmadds  f1, f8, f1, f9
L_end:
    addi    r1, r1, 0x18
    blr
    // clang-format on
}
