float FloorfHugeConst = 1.0e30f;
struct { float v; } FloorfZeroConst = {0.0f};

asm float floorf(float x)
{
    // clang-format off
    nofralloc
    stwu    r1, -0x10(r1)
    fmr     f0, f1
    stfs    f0, 0x8(r1)
    lwz     r0, 0x8(r1)
    mr      r11, r0
    extrwi  r9, r11, 8, 1
    subi    r9, r9, 0x7f
    cmpwi   r9, 0x16
    bgt     L_8016FE18
    cmpwi   r9, 0x0
    bge     L_8016FDD4
    lfs     f0, FloorfHugeConst
    lfs     f13, FloorfZeroConst.v
    fadds   f0, f1, f0
    fcmpu   cr0, f0, f13
    ble     L_8016FE28
    cmpwi   r11, 0x0
    blt     L_8016FDC4
    li      r11, 0x0
    b       L_8016FE28
L_8016FDC4:
    clrlwi. r0, r11, 1
    beq     L_8016FE28
    lis     r11, 0xbf80
    b       L_8016FE28
L_8016FDD4:
    lis     r0, 0x7f
    ori     r0, r0, 0xffff
    sraw    r10, r0, r9
    and.    r0, r11, r10
    beq     L_8016FE34
    lfs     f0, FloorfHugeConst
    lfs     f13, FloorfZeroConst.v
    fadds   f0, f1, f0
    fcmpu   cr0, f0, f13
    ble     L_8016FE28
    cmpwi   r11, 0x0
    bge     L_8016FE10
    lis     r0, 0x80
    sraw    r0, r0, r9
    add     r11, r11, r0
L_8016FE10:
    andc    r11, r11, r10
    b       L_8016FE28
L_8016FE18:
    cmpwi   r9, 0x80
    bne     L_8016FE34
    fadds   f1, f1, f1
    b       L_8016FE34
L_8016FE28:
    stw     r11, 0x8(r1)
    lfs     f0, 0x8(r1)
    fmr     f1, f0
L_8016FE34:
    addi    r1, r1, 0x10
    blr     
    // clang-format on
}
