extern float KernelCosfOneConst;
extern float KernelCosfC6Const;
extern float KernelCosfC5Const;
extern float KernelCosfC4Const;
extern float KernelCosfC3Const;
extern float KernelCosfC2Const;
extern float KernelCosfC1Const;
extern float KernelCosfHalfConst;
extern float KernelCosfQxConst;

asm float __kernel_cosf(float x, float y)
{
    // clang-format off
    nofralloc
    stwu    r1, -0x18(r1)
    fmr     f9, f1
    fmr     f0, f9
    stfs    f0, 8(r1)
    lwz     r9, 8(r1)
    clrlwi  r11, r9, 1
    lis     r0, 0x31ff
    ori     r0, r0, 0xffff
    cmpw    r11, r0
    bgt     L_big
    fmr     f0, f9
    fctiwz  f13, f0
    stfd    f13, 0x10(r1)
    lwz     r9, 0x14(r1)
    cmpwi   r9, 0
    bne     L_big
    lfs     f1, KernelCosfOneConst
    b       L_end
L_big:
    lfs     f12, KernelCosfC5Const
    fmuls   f10, f9, f9
    lfs     f0, KernelCosfC6Const
    lis     r0, 0x3e99
    lfs     f11, KernelCosfC4Const
    ori     r0, r0, 0x9999
    fmadds  f0, f10, f0, f12
    lfs     f13, KernelCosfC3Const
    fmadds  f0, f10, f0, f11
    lfs     f12, KernelCosfC2Const
    fmadds  f0, f10, f0, f13
    lfs     f11, KernelCosfC1Const
    fmadds  f0, f10, f0, f12
    cmpw    r11, r0
    fmadds  f0, f10, f0, f11
    fmuls   f12, f10, f0
    bgt     L_ge
    fmuls   f0, f9, f2
    lfs     f1, KernelCosfHalfConst
    fmsubs  f0, f10, f12, f0
    lfs     f13, KernelCosfOneConst
    fmsubs  f1, f10, f1, f0
    b       L_fin
L_ge:
    lis     r0, 0x3f48
    cmpw    r11, r0
    ble     L_sub
    lwz     r0, KernelCosfQxConst
    b       L_st
L_sub:
    subis   r0, r11, 0x100
L_st:
    fmuls   f0, f9, f2
    stw     r0, 8(r1)
    fmsubs  f0, f10, f12, f0
    lfs     f1, KernelCosfHalfConst
    lfs     f12, 8(r1)
    lfs     f13, KernelCosfOneConst
    fmsubs  f1, f10, f1, f12
    fsubs   f13, f13, f12
    fsubs   f1, f1, f0
L_fin:
    fsubs   f1, f13, f1
L_end:
    addi    r1, r1, 0x18
    blr
    // clang-format on
}
