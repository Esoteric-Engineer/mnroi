/* fdlibm e_fmod.c's `static const double Zero[] = {0.0, -0.0};`, returned as Zero[sx>>31] for an exact-zero result. */
#pragma section R ".rodata.1"
__declspec(section ".rodata.1") const double FmodZeroConst[2] = {0.0, -0.0};

asm double __ieee754_fmod(double x, double y)
{
    // clang-format off
    nofralloc
    stwu    r1, -0x20(r1)
    stmw    r28, 0x10(r1)
    fmr     f0, f1
    stfd    f0, 0x8(r1)
    lwz     r11, 0x8(r1)
    lwz     r12, 0xc(r1)
    mr      r7, r12
    fmr     f0, f2
    stfd    f0, 0x8(r1)
    lwz     r9, 0x8(r1)
    lwz     r10, 0xc(r1)
    mr      r6, r10
    clrrwi  r3, r11, 31
    clrlwi  r5, r9, 1
    clrlwi  r8, r11, 1
    or.     r0, r5, r6
    beq     L_801775C8
    lis     r0, 0x7fef
    ori     r0, r0, 0xffff
    cmpw    r8, r0
    bgt     L_801775C8
    neg     r0, r6
    lis     r9, 0x7ff0
    or      r0, r6, r0
    srwi    r0, r0, 31
    or      r0, r5, r0
    cmplw   r0, r9
    ble     L_801775D4
L_801775C8:
    fmul    f1, f1, f2
    fdiv    f1, f1, f1
    b       L_801778A8
L_801775D4:
    cmpw    r8, r5
    bgt     L_801775F0
    blt     L_801778A8
    cmplw   r7, r6
    blt     L_801778A8
    cmpw    r7, r6
    beq     L_8017786C
L_801775F0:
    lis     r0, 0xf
    ori     r0, r0, 0xffff
    cmpw    r8, r0
    bgt     L_80177644
    cmpwi   r8, 0x0
    bne     L_80177628
    li      r10, -0x413
    mr      r0, r7
    cmpwi   r7, 0x0
    ble     L_8017764C
L_80177618:
    subi    r10, r10, 0x1
    slwi.   r0, r0, 1
    bgt     L_80177618
    b       L_8017764C
L_80177628:
    li      r10, -0x3fe
    slwi.   r0, r8, 11
    ble     L_8017764C
L_80177634:
    subi    r10, r10, 0x1
    slwi.   r0, r0, 1
    bgt     L_80177634
    b       L_8017764C
L_80177644:
    srawi   r9, r8, 20
    subi    r10, r9, 0x3ff
L_8017764C:
    lis     r0, 0xf
    ori     r0, r0, 0xffff
    cmpw    r5, r0
    bgt     L_801776A8
    cmpwi   r5, 0x0
    bne     L_80177688
    li      r4, -0x413
    mr      r0, r6
    cmpwi   r6, 0x0
    cmpwi   cr7, r10, -0x3fe
    ble     L_801776B4
L_80177678:
    subi    r4, r4, 0x1
    slwi.   r0, r0, 1
    bgt     L_80177678
    b       L_801776B4
L_80177688:
    li      r4, -0x3fe
    cmpwi   cr7, r10, -0x3fe
    slwi.   r0, r5, 11
    ble     L_801776B4
L_80177698:
    subi    r4, r4, 0x1
    slwi.   r0, r0, 1
    bgt     L_80177698
    b       L_801776B4
L_801776A8:
    srawi   r9, r5, 20
    cmpwi   cr7, r10, -0x3fe
    subi    r4, r9, 0x3ff
L_801776B4:
    blt     cr7, L_801776C4
    clrlwi  r0, r8, 12
    oris    r8, r0, 0x10
    b       L_801776F4
L_801776C4:
    subfic  r11, r10, -0x3fe
    cmpwi   r11, 0x1f
    bgt     L_801776E8
    subfic  r0, r11, 0x20
    slw     r9, r8, r11
    srw     r0, r7, r0
    or      r8, r9, r0
    slw     r7, r7, r11
    b       L_801776F4
L_801776E8:
    subi    r0, r11, 0x20
    slw     r8, r7, r0
    li      r7, 0x0
L_801776F4:
    cmpwi   r4, -0x3fe
    blt     L_80177708
    clrlwi  r0, r5, 12
    oris    r5, r0, 0x10
    b       L_80177738
L_80177708:
    subfic  r11, r4, -0x3fe
    cmpwi   r11, 0x1f
    bgt     L_8017772C
    subfic  r0, r11, 0x20
    slw     r9, r5, r11
    srw     r0, r6, r0
    or      r5, r9, r0
    slw     r6, r6, r11
    b       L_80177738
L_8017772C:
    subi    r0, r11, 0x20
    slw     r5, r6, r0
    li      r6, 0x0
L_80177738:
    subf    r11, r4, r10
    b       L_80177788
L_80177740:
    subf    r9, r5, r8
    subf    r10, r6, r7
    cmplw   r7, r6
    bge     L_80177754
    subi    r9, r9, 0x1
L_80177754:
    cmpwi   r9, 0x0
    bge     L_80177770
    srwi    r0, r7, 31
    add     r9, r8, r8
    add     r8, r9, r0
    add     r7, r7, r7
    b       L_80177788
L_80177770:
    or.     r0, r9, r10
    beq     L_8017786C
    add     r9, r9, r9
    srwi    r0, r10, 31
    add     r8, r9, r0
    add     r7, r10, r10
L_80177788:
    mr      r0, r11
    cmpwi   r0, 0x0
    subi    r11, r11, 0x1
    bne     L_80177740
    subf    r9, r5, r8
    cmplw   r7, r6
    subf    r10, r6, r7
    bge     L_801777AC
    subi    r9, r9, 0x1
L_801777AC:
    cmpwi   r9, 0x0
    blt     L_801777BC
    mr      r8, r9
    mr      r7, r10
L_801777BC:
    or.     r0, r8, r7
    beq     L_8017786C
    lis     r0, 0xf
    ori     r0, r0, 0xffff
    cmpw    r8, r0
    bgt     L_801777F8
    lis     r11, 0xf
    ori     r11, r11, 0xffff
L_801777DC:
    srwi    r0, r7, 31
    add     r9, r8, r8
    add     r8, r9, r0
    add     r7, r7, r7
    subi    r4, r4, 0x1
    cmpw    r8, r11
    ble     L_801777DC
L_801777F8:
    cmpwi   r4, -0x3fe
    blt     L_8017782C
    addi    r0, r4, 0x3ff
    subis   r9, r8, 0x10
    slwi    r0, r0, 20
    or      r8, r9, r0
    or      r30, r8, r3
    mr      r31, r7
    stw     r30, 0x8(r1)
    stw     r31, 0xc(r1)
    lfd     f0, 0x8(r1)
    fmr     f1, f0
    b       L_801778A8
L_8017782C:
    subfic  r11, r4, -0x3fe
    cmpwi   r11, 0x14
    bgt     L_80177850
    subfic  r0, r11, 0x20
    srw     r9, r7, r11
    slw     r0, r8, r0
    or      r7, r9, r0
    sraw    r8, r8, r11
    b       L_80177890
L_80177850:
    cmpwi   r11, 0x1f
    bgt     L_80177884
    subfic  r0, r11, 0x20
    srw     r9, r7, r11
    slw     r0, r8, r0
    or      r7, r0, r9
    b       L_8017788C
L_8017786C:
    srwi    r0, r3, 31
    lis     r9, FmodZeroConst@ha
    addi    r9, r9, FmodZeroConst@l
    slwi    r0, r0, 3
    lfdx    f1, r9, r0
    b       L_801778A8
L_80177884:
    subi    r0, r11, 0x20
    sraw    r7, r8, r0
L_8017788C:
    mr      r8, r3
L_80177890:
    or      r28, r8, r3
    mr      r29, r7
    stw     r28, 0x8(r1)
    stw     r29, 0xc(r1)
    lfd     f0, 0x8(r1)
    fmr     f1, f0
L_801778A8:
    lmw     r28, 0x10(r1)
    addi    r1, r1, 0x20
    blr     
    // clang-format on
}
