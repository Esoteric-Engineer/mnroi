asm double __ieee754_sqrt(double x)
{
    // clang-format off
    nofralloc
    stwu    r1, -0x20(r1)
    stmw    r29, 0x14(r1)
    lis     r31, 0x8000
    fmr     f0, f1
    stfd    f0, 0x8(r1)
    lwz     r9, 0x8(r1)
    lwz     r10, 0xc(r1)
    mr      r8, r10
    rlwinm  r11, r9, 0, 1, 11
    lis     r0, 0x7ff0
    cmpw    r11, r0
    bne     L_8016C7C8
    fmadd   f1, f1, f1, f1
    b       L_8016C998
L_8016C7C8:
    cmpwi   cr7, r9, 0x0
    bgt     cr7, L_8016C7EC
    clrlwi  r0, r9, 1
    or.     r11, r0, r8
    beq     L_8016C998
    bge     cr7, L_8016C7EC
    fsub    f1, f1, f1
    fdiv    f1, f1, f1
    b       L_8016C998
L_8016C7EC:
    cmpwi   cr6, r31, 0x0
    srawi.  r10, r9, 20
    bne     L_8016C844
    bne     cr7, L_8016C810
L_8016C7FC:
    srwi    r0, r8, 11
    subi    r10, r10, 0x15
    slwi    r8, r8, 21
    or.     r9, r9, r0
    beq     L_8016C7FC
L_8016C810:
    addi    r10, r10, 0x1
    li      r11, 0x0
    andis.  r0, r9, 0x10
    bne     L_8016C830
L_8016C820:
    slwi    r9, r9, 1
    addi    r11, r11, 0x1
    andis.  r0, r9, 0x10
    beq     L_8016C820
L_8016C830:
    subfic  r0, r11, 0x20
    subf    r10, r11, r10
    srw     r0, r8, r0
    or      r9, r9, r0
    slw     r8, r8, r11
L_8016C844:
    subi    r10, r10, 0x3ff
    clrlwi  r0, r9, 12
    oris    r9, r0, 0x10
    andi.   r11, r10, 0x1
    beq     L_8016C86C
    and     r0, r8, r31
    srwi    r0, r0, 31
    add     r8, r8, r8
    add     r0, r9, r0
    add     r9, r9, r0
L_8016C86C:
    and     r0, r8, r31
    srawi   r10, r10, 1
    srwi    r0, r0, 31
    add     r8, r8, r8
    add     r0, r9, r0
    li      r30, 0x0
    add     r9, r9, r0
    li      r4, 0x0
    li      r3, 0x0
    li      r12, 0x0
    lis     r7, 0x20
L_8016C898:
    add     r11, r4, r7
    cmpw    r11, r9
    bgt     L_8016C8B0
    subf    r9, r11, r9
    add     r4, r11, r7
    add     r12, r12, r7
L_8016C8B0:
    and     r0, r8, r31
    srwi.   r7, r7, 1
    srwi    r0, r0, 31
    add     r8, r8, r8
    add     r0, r9, r0
    add     r9, r9, r0
    bne     L_8016C898
    slwi    r29, r10, 20
    lis     r7, 0x8000
    beq     cr6, L_8016C944
L_8016C8D8:
    mr      r11, r4
    add     r10, r30, r7
    cmpw    r11, r9
    blt     L_8016C8F4
    bne     L_8016C928
    cmplw   r10, r8
    bgt     L_8016C928
L_8016C8F4:
    and     r0, r10, r31
    add     r30, r10, r7
    cmpw    r0, r31
    bne     L_8016C910
    and.    r0, r30, r31
    bne     L_8016C910
    addi    r4, r11, 0x1
L_8016C910:
    subf    r9, r11, r9
    cmplw   r8, r10
    bge     L_8016C920
    subi    r9, r9, 0x1
L_8016C920:
    subf    r8, r10, r8
    add     r3, r3, r7
L_8016C928:
    and     r0, r8, r31
    srwi.   r7, r7, 1
    srwi    r0, r0, 31
    add     r8, r8, r8
    add     r0, r9, r0
    add     r9, r9, r0
    bne     L_8016C8D8
L_8016C944:
    or.     r11, r9, r8
    beq     L_8016C968
    cmpwi   r3, -0x1
    bne     L_8016C960
    li      r3, 0x0
    addi    r12, r12, 0x1
    b       L_8016C968
L_8016C960:
    clrlwi  r0, r3, 31
    add     r3, r3, r0
L_8016C968:
    srawi   r9, r12, 1
    srwi    r8, r3, 1
    addis   r9, r9, 0x3fe0
    andi.   r0, r12, 0x1
    beq     L_8016C980
    oris    r8, r8, 0x8000
L_8016C980:
    add     r5, r9, r29
    mr      r6, r8
    stw     r5, 0x8(r1)
    stw     r6, 0xc(r1)
    lfd     f0, 0x8(r1)
    fmr     f1, f0
L_8016C998:
    lmw     r29, 0x14(r1)
    addi    r1, r1, 0x20
    blr
    // clang-format on
}
