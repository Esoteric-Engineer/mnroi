float ScalbnfTwo25Const = 3.355443200e+07f;
float ScalbnfTinyConst = 1.0e-30f;
float ScalbnfHugeConst = 1.0e30f;
float ScalbnfTwom25Const = 2.9802322388e-08f;
extern float copysignf(float x, float y);

asm float scalbnf(float x, int n)
{
    // clang-format off
    nofralloc
    stwu    r1, -0x10(r1)
    mflr    r0
    stw     r0, 0x14(r1)
    fmr     f2, f1
    fmr     f0, f2
    stfs    f0, 8(r1)
    lwz     r0, 8(r1)
    mr      r11, r0
    extrwi  r9, r11, 8, 1
    cmpwi   r9, 0
    bne     L_norm
    clrlwi. r0, r11, 1
    beq     L_end
    lfs     f0, ScalbnfTwo25Const
    fmuls   f2, f2, f0
    fmr     f0, f2
    stfs    f0, 8(r1)
    lwz     r0, 8(r1)
    mr      r11, r0
    extrwi  r9, r11, 8, 1
    lis     r0, 0xffff
    subi    r9, r9, 0x19
    ori     r0, r0, 0x3cb0
    cmpw    r3, r0
    bge     L_norm
    lfs     f1, ScalbnfTinyConst
    b       L_mul
L_norm:
    cmpwi   r9, 0xff
    bne     L_fin
    fadds   f1, f2, f2
    b       L_end
L_fin:
    add     r9, r9, r3
    cmpwi   r9, 0xfe
    bgt     L_huge
    cmpwi   r9, 0
    ble     L_sub
    slwi    r9, r9, 23
    rlwinm  r0, r11, 0, 9, 0
    or      r0, r0, r9
    stw     r0, 8(r1)
    lfs     f2, 8(r1)
    fmr     f1, f2
    b       L_end
L_sub:
    cmpwi   r9, -0x19
    bgt     L_subn
    li      r0, 0
    ori     r0, r0, 0xc350
    cmpw    r3, r0
    ble     L_tiny
L_huge:
    lfs     f1, ScalbnfHugeConst
    bl      copysignf
    lfs     f0, ScalbnfHugeConst
    fmuls   f1, f1, f0
    b       L_end
L_tiny:
    lfs     f1, ScalbnfTinyConst
    bl      copysignf
    lfs     f0, ScalbnfTinyConst
    fmuls   f1, f1, f0
    b       L_end
L_subn:
    addi    r9, r9, 0x19
    rlwinm  r0, r11, 0, 9, 0
    slwi    r9, r9, 23
    or      r0, r0, r9
    stw     r0, 8(r1)
    lfs     f2, 8(r1)
    lfs     f1, ScalbnfTwom25Const
L_mul:
    fmuls   f1, f2, f1
L_end:
    lwz     r0, 0x14(r1)
    mtlr    r0
    addi    r1, r1, 0x10
    blr
    // clang-format on
}
