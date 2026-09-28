extern double lbl_8066C040;

asm double fn_8016CBDC(double x)
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
    bgt     L_8016CC9C
    cmpwi   r10, 0x0
    bge     L_8016CC50
    lfd     f0, lbl_8066C040
    lfd     f13, lbl_8066C040+0x8
    fadd    f0, f1, f0
    fcmpu   cr0, f0, f13
    ble     L_8016CD18
    cmpwi   r11, 0x0
    blt     L_8016CC38
    li      r6, 0x0
    li      r11, 0x0
    b       L_8016CD18
L_8016CC38:
    clrlwi  r0, r11, 1
    or.     r9, r0, r6
    beq     L_8016CD18
    lis     r11, 0xbff0
    li      r6, 0x0
    b       L_8016CD18
L_8016CC50:
    lis     r0, 0xf
    ori     r0, r0, 0xffff
    sraw    r5, r0, r10
    and     r9, r11, r5
    or.     r0, r9, r6
    beq     L_8016CD30
    lfd     f0, lbl_8066C040
    lfd     f13, lbl_8066C040+0x8
    fadd    f0, f1, f0
    fcmpu   cr0, f0, f13
    ble     L_8016CD18
    cmpwi   r11, 0x0
    bge     L_8016CC90
    lis     r0, 0x10
    sraw    r0, r0, r10
    add     r11, r11, r0
L_8016CC90:
    andc    r11, r11, r5
    li      r6, 0x0
    b       L_8016CD18
L_8016CC9C:
    cmpwi   r10, 0x33
    ble     L_8016CCB4
    cmpwi   r10, 0x400
    bne     L_8016CD30
    fadd    f1, f1, f1
    b       L_8016CD30
L_8016CCB4:
    subi    r9, r9, 0x413
    li      r0, -0x1
    srw     r5, r0, r9
    and.    r9, r6, r5
    beq     L_8016CD30
    lfd     f0, lbl_8066C040
    lfd     f13, lbl_8066C040+0x8
    fadd    f0, f1, f0
    fcmpu   cr0, f0, f13
    ble     L_8016CD18
    cmpwi   r11, 0x0
    bge     L_8016CD14
    cmpwi   r10, 0x14
    bne     L_8016CCF4
    addi    r11, r11, 0x1
    b       L_8016CD14
L_8016CCF4:
    subfic  r9, r10, 0x34
    li      r0, 0x1
    slw     r0, r0, r9
    add     r0, r6, r0
    cmplw   r0, r6
    bge     L_8016CD10
    addi    r11, r11, 0x1
L_8016CD10:
    mr      r6, r0
L_8016CD14:
    andc    r6, r6, r5
L_8016CD18:
    mr      r7, r11
    mr      r8, r6
    stw     r7, 0x8(r1)
    stw     r8, 0xc(r1)
    lfd     f0, 0x8(r1)
    fmr     f1, f0
L_8016CD30:
    addi    r1, r1, 0x10
    blr
    // clang-format on
}
