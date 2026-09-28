/* libgcc's s64 -> float conversion. The three doubles are this object's own .rodata.1 constants. */
#pragma section R ".rodata.1"
__declspec(section ".rodata.1") const double FloatdisfHiMagicConst = 4503601774854144.0;
__declspec(section ".rodata.1") const double FloatdisfTwoTo16Const = 65536.0;
__declspec(section ".rodata.1") const double FloatdisfLoMagicConst = 4503599627370496.0;

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
    lis     r11, FloatdisfHiMagicConst@ha
    lis     r9, FloatdisfTwoTo16Const@ha
    stw     r6, 8(r1)
    lfd     f0, FloatdisfHiMagicConst@l(r11)
    lfd     f1, 8(r1)
    lis     r11, FloatdisfLoMagicConst@ha
    stw     r4, 0xc(r1)
    lfd     f12, FloatdisfTwoTo16Const@l(r9)
    fsub    f1, f1, f0
    stw     r6, 8(r1)
    lfd     f13, FloatdisfLoMagicConst@l(r11)
    fmul    f1, f1, f12
    lfd     f0, 8(r1)
    fsub    f0, f0, f13
    fmadd   f1, f1, f12, f0
    frsp    f1, f1
    addi    r1, r1, 0x10
    blr
    // clang-format on
}
