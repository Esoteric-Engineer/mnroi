asm float __ieee754_sqrtf(float x)
{
    // clang-format off
    nofralloc
    stwu    r1, -0x10(r1)
    fmr     f0, f1
    stfs    f0, 0x8(r1)
    lwz     r10, 0x8(r1)
    mr      r11, r10
    rlwinm  r9, r11, 0, 1, 8
    lis     r0, 0x7f80
    cmpw    r9, r0
    bne     L_finite
    fmadds  f1, f1, f1, f1
    b       L_end
L_finite:
    cmpwi   cr7, r11, 0
    bgt     cr7, L_pos
    clrlwi. r0, r11, 1
    beq     L_end
    bge     cr7, L_pos
    fsubs   f1, f1, f1
    fdivs   f1, f1, f1
    b       L_end
L_pos:
    srawi.  r9, r10, 23
    bne     L_norm
    li      r9, 0
    andis.  r0, r11, 0x80
    bne     L_subdone
L_sub:
    slwi    r11, r11, 1
    addi    r9, r9, 1
    andis.  r0, r11, 0x80
    beq     L_sub
L_subdone:
    subfic  r9, r9, 1
L_norm:
    clrlwi  r0, r11, 9
    subi    r9, r9, 0x7f
    oris    r11, r0, 0x80
    andi.   r0, r9, 1
    beq     L_even
    add     r11, r11, r11
L_even:
    srawi   r9, r9, 1
    add     r11, r11, r11
    li      r7, 0
    li      r8, 0
    lis     r10, 0x100
L_loop:
    add     r0, r7, r10
    cmpw    r0, r11
    bgt     L_skip
    subf    r11, r0, r11
    add     r7, r0, r10
    add     r8, r8, r10
L_skip:
    add     r11, r11, r11
    srwi.   r10, r10, 1
    bne     L_loop
    cmpwi   r11, 0
    beq     L_noround
    clrlwi  r0, r8, 31
    add     r8, r8, r0
L_noround:
    srawi   r11, r8, 1
    slwi    r9, r9, 23
    addis   r11, r11, 0x3f00
    add     r0, r11, r9
    stw     r0, 0x8(r1)
    lfs     f0, 0x8(r1)
    fmr     f1, f0
L_end:
    addi    r1, r1, 0x10
    blr
    // clang-format on
}
