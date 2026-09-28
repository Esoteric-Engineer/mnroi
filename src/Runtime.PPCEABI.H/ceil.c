struct { double v; } CeilHugeConst = {1.0e300};
struct { double v; } CeilZeroConst = {0.0};

asm double ceil(double x)
{
    // clang-format off
    nofralloc
    stwu    r1, -0x10(r1)
    fmr     f0, f1
    stfd    f0, 0x8(r1)
    lwz     r9, 0x8(r1)
    lwz     r10, 0xc(r1)
    mr      r6, r10
    mr      r11, r9
    extrwi  r9, r11, 11, 1
    subi    r10, r9, 0x3ff
    cmpwi   r10, 0x13
    bgt     L_8016CA60
    cmpwi   r10, 0x0
    bge     L_8016CA14
    lfd     f0, CeilHugeConst.v
    lfd     f13, CeilZeroConst.v
    fadd    f0, f1, f0
    fcmpu   cr0, f0, f13
    ble     L_8016CADC
    cmpwi   r11, 0x0
    bge     L_8016CA00
    lis     r11, 0x8000
    li      r6, 0x0
    b       L_8016CADC
L_8016CA00:
    or.     r0, r11, r6
    beq     L_8016CADC
    lis     r11, 0x3ff0
    li      r6, 0x0
    b       L_8016CADC
L_8016CA14:
    lis     r0, 0xf
    ori     r0, r0, 0xffff
    sraw    r5, r0, r10
    and     r9, r11, r5
    or.     r0, r9, r6
    beq     L_8016CAF4
    lfd     f0, CeilHugeConst.v
    lfd     f13, CeilZeroConst.v
    fadd    f0, f1, f0
    fcmpu   cr0, f0, f13
    ble     L_8016CADC
    cmpwi   r11, 0x0
    ble     L_8016CA54
    lis     r0, 0x10
    sraw    r0, r0, r10
    add     r11, r11, r0
L_8016CA54:
    andc    r11, r11, r5
    li      r6, 0x0
    b       L_8016CADC
L_8016CA60:
    cmpwi   r10, 0x33
    ble     L_8016CA78
    cmpwi   r10, 0x400
    bne     L_8016CAF4
    fadd    f1, f1, f1
    b       L_8016CAF4
L_8016CA78:
    li      r0, -0x1
    subi    r9, r9, 0x413
    srw     r5, r0, r9
    and.    r0, r6, r5
    beq     L_8016CAF4
    lfd     f0, CeilHugeConst.v
    lfd     f13, CeilZeroConst.v
    fadd    f0, f1, f0
    fcmpu   cr0, f0, f13
    ble     L_8016CADC
    cmpwi   r11, 0x0
    ble     L_8016CAD8
    cmpwi   r10, 0x14
    bne     L_8016CAB8
    addi    r11, r11, 0x1
    b       L_8016CAD8
L_8016CAB8:
    subfic  r9, r10, 0x34
    li      r0, 0x1
    slw     r0, r0, r9
    add     r0, r6, r0
    cmplw   r0, r6
    bge     L_8016CAD4
    addi    r11, r11, 0x1
L_8016CAD4:
    mr      r6, r0
L_8016CAD8:
    andc    r6, r6, r5
L_8016CADC:
    mr      r7, r11
    mr      r8, r6
    stw     r7, 0x8(r1)
    stw     r8, 0xc(r1)
    lfd     f0, 0x8(r1)
    fmr     f1, f0
L_8016CAF4:
    addi    r1, r1, 0x10
    blr
    // clang-format on
}
