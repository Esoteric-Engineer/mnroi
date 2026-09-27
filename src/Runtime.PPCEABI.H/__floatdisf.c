extern double lbl_804BF448[1];
extern double lbl_804BF450[1];
extern double lbl_804BF458[1];

asm float __floatdisf(long long u)
{
    // clang-format off
    nofralloc
    stwu    r1, -0x10(r1)
    lis     r9, 0x1f
    lis     r0, 0x3f
    ori     r9, r9, 0xffff
    ori     r0, r0, 0xffff
    li      r10, -1
    addc    r10, r10, r4
    adde    r9, r9, r3
    cmplw   r9, r0
    bgt     L_shift
    cmpw    r9, r0
    bne     L_round
    li      r0, -2
    cmplw   r10, r0
    ble     L_round
L_shift:
    andi.   r0, r4, 0x7ff
    beq     L_round
    mr      r9, r3
    ori     r10, r4, 0x800
    mr      r3, r9
    mr      r4, r10
L_round:
    mr      r10, r3
    xoris   r0, r10, 0x8000
    lis     r6, 0x4330
    stw     r0, 0xc(r1)
    mr      r7, r8
    lis     r11, lbl_804BF448@ha
    lis     r9, lbl_804BF450@ha
    stw     r6, 8(r1)
    lfd     f0, lbl_804BF448@l(r11)
    lfd     f1, 8(r1)
    lis     r11, lbl_804BF458@ha
    stw     r4, 0xc(r1)
    lfd     f12, lbl_804BF450@l(r9)
    fsub    f1, f1, f0
    stw     r6, 8(r1)
    lfd     f13, lbl_804BF458@l(r11)
    fmul    f1, f1, f12
    lfd     f0, 8(r1)
    fsub    f0, f0, f13
    fmadd   f1, f1, f12, f0
    frsp    f1, f1
    addi    r1, r1, 0x10
    blr
    // clang-format on
}
