extern double lbl_8049C8A0[1];
extern double lbl_8049C8A8[1];
extern double lbl_8049C8B0[1];
extern double lbl_8049C8B8[1];
extern double lbl_8049C8C0[1];
extern double lbl_8049C8C8[1];
extern double lbl_8049C8D0[1];
extern double __ieee754_log(double x);

asm double __ieee754_log10(double x)
{
    // clang-format off
    nofralloc
    stwu    r1, -0x20(r1)
    mflr    r0
    stfd    f31, 0x18(r1)
    stw     r0, 0x24(r1)
    fmr     f0, f1
    stfd    f0, 8(r1)
    lwz     r9, 8(r1)
    lwz     r10, 0xc(r1)
    mr      r5, r9
    mr      r11, r10
    li      r8, 0
    lis     r0, 0xf
    ori     r0, r0, 0xffff
    cmpw    r5, r0
    bgt     L_pos
    clrlwi  r0, r5, 1
    or.     r9, r0, r11
    bne     L_nz
    lis     r9, lbl_8049C8A0@ha
    lfd     f1, lbl_8049C8A0@l(r9)
    b       L_end
L_nz:
    cmpwi   r5, 0
    bge     L_sub
    fsub    f0, f1, f1
    lis     r9, lbl_8049C8A8@ha
    lfd     f1, lbl_8049C8A8@l(r9)
    fdiv    f1, f0, f1
    b       L_end
L_sub:
    lis     r9, lbl_8049C8B0@ha
    li      r8, -0x36
    lfd     f0, lbl_8049C8B0@l(r9)
    fmul    f1, f1, f0
    fmr     f0, f1
    stfd    f0, 8(r1)
    lwz     r9, 8(r1)
    lwz     r10, 0xc(r1)
    mr      r5, r9
L_pos:
    lis     r0, 0x7fef
    ori     r0, r0, 0xffff
    cmpw    r5, r0
    bgt     L_inf
    srawi   r0, r5, 20
    subi    r9, r8, 0x3ff
    add     r8, r9, r0
    stfd    f1, 8(r1)
    srwi    r11, r8, 31
    add     r0, r8, r11
    lwz     r9, 8(r1)
    lwz     r10, 0xc(r1)
    subfic  r11, r11, 0x3ff
    xoris   r0, r0, 0x8000
    slwi    r11, r11, 20
    stw     r0, 0x14(r1)
    rlwimi  r5, r11, 0, 0, 11
    lis     r6, 0x4330
    mr      r9, r5
    stw     r6, 0x10(r1)
    stw     r9, 8(r1)
    stw     r10, 0xc(r1)
    lis     r8, lbl_8049C8B8@ha
    lfd     f0, lbl_8049C8B8@l(r8)
    lfd     f13, 8(r1)
    lfd     f31, 0x10(r1)
    fmr     f1, f13
    fsub    f31, f31, f0
    bl      __ieee754_log
    lis     r9, lbl_8049C8C8@ha
    lis     r11, lbl_8049C8C0@ha
    lfd     f12, lbl_8049C8C8@l(r9)
    lis     r10, lbl_8049C8D0@ha
    lfd     f0, lbl_8049C8C0@l(r11)
    fmul    f1, f1, f12
    lfd     f13, lbl_8049C8D0@l(r10)
    fmadd   f0, f31, f0, f1
    fmadd   f1, f31, f13, f0
    b       L_end
L_inf:
    fadd    f1, f1, f1
L_end:
    lwz     r0, 0x24(r1)
    mtlr    r0
    lfd     f31, 0x18(r1)
    addi    r1, r1, 0x20
    blr
    // clang-format on
}
