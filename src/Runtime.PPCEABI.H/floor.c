extern char lbl_8049C7F8[];
extern char lbl_8049C800[];

asm double floor(double x)
{
    // clang-format off
    nofralloc
    stwu    r1, -0x10(r1)
    fmr     f0, f1
    stfd    f0, 0x8(r1)
    lwz     r9, 0x8(r1)
    lwz     r10, 0xc(r1)
    mr      r6, r10
    mr      r10, r9
    extrwi  r9, r10, 11, 1
    subi    r5, r9, 0x3ff
    cmpwi   r5, 0x13
    bgt     L_801774B4
    cmpwi   r5, 0x0
    bge     L_80177460
    lis     r9, lbl_8049C7F8@ha
    lis     r11, lbl_8049C800@ha
    lfd     f0, lbl_8049C7F8@l(r9)
    lfd     f13, lbl_8049C800@l(r11)
    fadd    f0, f1, f0
    fcmpu   cr0, f0, f13
    ble     L_80177538
    cmpwi   r10, 0x0
    blt     L_80177448
    li      r6, 0x0
    li      r10, 0x0
    b       L_80177538
L_80177448:
    clrlwi  r0, r10, 1
    or.     r9, r0, r6
    beq     L_80177538
    lis     r10, 0xbff0
    li      r6, 0x0
    b       L_80177538
L_80177460:
    lis     r0, 0xf
    ori     r0, r0, 0xffff
    sraw    r4, r0, r5
    and     r9, r10, r4
    or.     r0, r9, r6
    beq     L_80177550
    lis     r9, lbl_8049C7F8@ha
    lis     r11, lbl_8049C800@ha
    lfd     f0, lbl_8049C7F8@l(r9)
    lfd     f13, lbl_8049C800@l(r11)
    fadd    f0, f1, f0
    fcmpu   cr0, f0, f13
    ble     L_80177538
    cmpwi   r10, 0x0
    bge     L_801774A8
    lis     r0, 0x10
    sraw    r0, r0, r5
    add     r10, r10, r0
L_801774A8:
    andc    r10, r10, r4
    li      r6, 0x0
    b       L_80177538
L_801774B4:
    cmpwi   r5, 0x33
    ble     L_801774CC
    cmpwi   r5, 0x400
    bne     L_80177550
    fadd    f1, f1, f1
    b       L_80177550
L_801774CC:
    subi    r9, r9, 0x413
    li      r0, -0x1
    srw     r4, r0, r9
    and.    r9, r6, r4
    beq     L_80177550
    lis     r9, lbl_8049C7F8@ha
    lis     r11, lbl_8049C800@ha
    lfd     f0, lbl_8049C7F8@l(r9)
    lfd     f13, lbl_8049C800@l(r11)
    fadd    f0, f1, f0
    fcmpu   cr0, f0, f13
    ble     L_80177538
    cmpwi   r10, 0x0
    bge     L_80177534
    cmpwi   r5, 0x14
    bne     L_80177514
    addi    r10, r10, 0x1
    b       L_80177534
L_80177514:
    subfic  r9, r5, 0x34
    li      r0, 0x1
    slw     r0, r0, r9
    add     r0, r6, r0
    cmplw   r0, r6
    bge     L_80177530
    addi    r10, r10, 0x1
L_80177530:
    mr      r6, r0
L_80177534:
    andc    r6, r6, r4
L_80177538:
    mr      r7, r10
    mr      r8, r6
    stw     r7, 0x8(r1)
    stw     r8, 0xc(r1)
    lfd     f0, 0x8(r1)
    fmr     f1, f0
L_80177550:
    addi    r1, r1, 0x10
    blr
    // clang-format on
}
