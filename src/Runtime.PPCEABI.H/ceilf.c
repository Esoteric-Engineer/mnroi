float CeilfHugeConst = 1.0e30f;
struct { float v; } CeilfZeroConst = {0.0f};

asm float ceilf(float x)
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
    bgt     L_80400520
    cmpwi   r9, 0x0
    bge     L_804004DC
    lfs     f0, CeilfHugeConst
    lfs     f13, CeilfZeroConst.v
    fadds   f0, f1, f0
    fcmpu   cr0, f0, f13
    ble     L_80400530
    cmpwi   r11, 0x0
    bge     L_804004D0
    lis     r11, 0x8000
    b       L_80400530
L_804004D0:
    beq     L_80400530
    lis     r11, 0x3f80
    b       L_80400530
L_804004DC:
    lis     r0, 0x7f
    ori     r0, r0, 0xffff
    sraw    r10, r0, r9
    and.    r0, r11, r10
    beq     L_8040053C
    lfs     f0, CeilfHugeConst
    lfs     f13, CeilfZeroConst.v
    fadds   f0, f1, f0
    fcmpu   cr0, f0, f13
    ble     L_80400530
    cmpwi   r11, 0x0
    ble     L_80400518
    lis     r0, 0x80
    sraw    r0, r0, r9
    add     r11, r11, r0
L_80400518:
    andc    r11, r11, r10
    b       L_80400530
L_80400520:
    cmpwi   r9, 0x80
    bne     L_8040053C
    fadds   f1, f1, f1
    b       L_8040053C
L_80400530:
    stw     r11, 0x8(r1)
    lfs     f0, 0x8(r1)
    fmr     f1, f0
L_8040053C:
    addi    r1, r1, 0x10
    blr
    // clang-format on
}
