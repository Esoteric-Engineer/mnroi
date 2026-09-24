asm unsigned long long __umoddi3(unsigned long long a, unsigned long long b)
{
    // clang-format off
    nofralloc
    stwu    r1, -0x28(r1)
    stmw    r26, 0x10(r1)
    addi    r26, r1, 0x8
    mr      r12, r6
    mr      r29, r4
    mr      r30, r3
    mr.     r31, r5
    bne     L_8017A37C
    cmplw   r12, r30
    ble     L_8017A1D0
    li      r0, 0x0
    mr      r11, r6
    ori     r0, r0, 0xffff
    cmplw   r12, r0
    bgt     L_8017A180
    subfic  r0, r12, 0xff
    subfe   r0, r0, r0
    rlwinm  r5, r0, 0, 28, 28
    b       L_8017A198
L_8017A180:
    lis     r0, 0xff
    li      r5, 0x18
    ori     r0, r0, 0xffff
    cmplw   r12, r0
    bgt     L_8017A198
    li      r5, 0x10
L_8017A198:
    srw     r11, r11, r5
    addi    r9, r13, -12144
    lbzx    r0, r9, r11
    add     r0, r0, r5
    subfic  r5, r0, 0x20
    cmpwi   r5, 0x0
    beq     L_8017A2E0
    subfic  r0, r5, 0x20
    slw     r9, r30, r5
    srw     r0, r29, r0
    slw     r12, r12, r5
    or      r30, r9, r0
    slw     r29, r29, r5
    b       L_8017A2E0
L_8017A1D0:
    cmpwi   r12, 0x0
    bne     L_8017A1E0
    li      r0, 0x1
    divwu   r12, r0, r31
L_8017A1E0:
    li      r0, 0x0
    ori     r0, r0, 0xffff
    cmplw   r12, r0
    bgt     L_8017A200
    subfic  r0, r12, 0xff
    subfe   r0, r0, r0
    rlwinm  r10, r0, 0, 28, 28
    b       L_8017A218
L_8017A200:
    lis     r0, 0xff
    li      r10, 0x18
    ori     r0, r0, 0xffff
    cmplw   r12, r0
    bgt     L_8017A218
    li      r10, 0x10
L_8017A218:
    srw     r11, r12, r10
    addi    r9, r13, -12144
    lbzx    r0, r9, r11
    add     r0, r0, r10
    subfic  r5, r0, 0x20
    cmpwi   r5, 0x0
    bne     L_8017A23C
    subf    r30, r12, r30
    b       L_8017A2E0
L_8017A23C:
    subfic  r6, r5, 0x20
    slw     r9, r30, r5
    srw     r0, r29, r6
    srw     r8, r30, r6
    or      r30, r9, r0
    slw     r12, r12, r5
    slw     r29, r29, r5
    srwi    r4, r12, 16
    divwu   r0, r8, r4
    clrlwi  r10, r12, 16
    srwi    r11, r30, 16
    mullw   r9, r0, r4
    mullw   r7, r0, r10
    subf    r8, r9, r8
    slwi    r0, r8, 16
    or      r8, r0, r11
    cmplw   r8, r7
    bge     L_8017A29C
    add     r8, r8, r12
    cmplw   r8, r12
    blt     L_8017A29C
    cmplw   r8, r7
    bge     L_8017A29C
    add     r8, r8, r12
L_8017A29C:
    subf    r8, r7, r8
    clrlwi  r11, r30, 16
    divwu   r0, r8, r4
    mullw   r9, r0, r4
    mullw   r7, r0, r10
    subf    r0, r9, r8
    slwi    r0, r0, 16
    or      r0, r0, r11
    cmplw   r0, r7
    bge     L_8017A2DC
    add     r0, r0, r12
    cmplw   r0, r12
    blt     L_8017A2DC
    cmplw   r0, r7
    bge     L_8017A2DC
    add     r0, r0, r12
L_8017A2DC:
    subf    r30, r7, r0
L_8017A2E0:
    srwi    r7, r12, 16
    clrlwi  r4, r12, 16
    divwu   r0, r30, r7
    srwi    r11, r29, 16
    mullw   r9, r0, r7
    mullw   r8, r0, r4
    subf    r10, r9, r30
    slwi    r0, r10, 16
    or      r10, r0, r11
    cmplw   r10, r8
    bge     L_8017A324
    add     r10, r10, r12
    cmplw   r10, r12
    blt     L_8017A324
    cmplw   r10, r8
    bge     L_8017A324
    add     r10, r10, r12
L_8017A324:
    subf    r10, r8, r10
    clrlwi  r11, r29, 16
    divwu   r0, r10, r7
    mullw   r9, r0, r7
    mullw   r8, r0, r4
    subf    r0, r9, r10
    slwi    r0, r0, 16
    or      r0, r0, r11
    cmplw   r0, r8
    bge     L_8017A364
    add     r0, r0, r12
    cmplw   r0, r12
    blt     L_8017A364
    cmplw   r0, r8
    bge     L_8017A364
    add     r0, r0, r12
L_8017A364:
    subf    r29, r8, r0
    cmpwi   r26, 0x0
    beq     L_8017A5B8
    srw     r28, r29, r5
    li      r27, 0x0
    b       L_8017A5B0
L_8017A37C:
    cmplw   r31, r30
    ble     L_8017A398
    mr      r28, r4
    mr      r27, r30
    stw     r27, 0x8(r1)
    stw     r28, 0xc(r1)
    b       L_8017A5B8
L_8017A398:
    li      r0, 0x0
    ori     r0, r0, 0xffff
    cmplw   r31, r0
    bgt     L_8017A3B8
    subfic  r0, r31, 0xff
    subfe   r0, r0, r0
    rlwinm  r10, r0, 0, 28, 28
    b       L_8017A3D0
L_8017A3B8:
    lis     r0, 0xff
    li      r10, 0x18
    ori     r0, r0, 0xffff
    cmplw   r31, r0
    bgt     L_8017A3D0
    li      r10, 0x10
L_8017A3D0:
    srw     r11, r31, r10
    addi    r9, r13, -12144
    lbzx    r0, r9, r11
    add     r0, r0, r10
    subfic  r5, r0, 0x20
    cmpwi   r5, 0x0
    bne     L_8017A42C
    cmplw   r30, r31
    bgt     L_8017A3FC
    cmplw   r29, r12
    blt     L_8017A418
L_8017A3FC:
    subf    r11, r12, r29
    subf    r9, r31, r30
    subfc   r0, r11, r29
    subfe   r0, r0, r0
    neg     r0, r0
    subf    r30, r0, r9
    mr      r29, r11
L_8017A418:
    cmpwi   r26, 0x0
    beq     L_8017A5B8
    mr      r28, r29
    mr      r27, r30
    b       L_8017A5B0
L_8017A42C:
    subfic  r6, r5, 0x20
    slw     r10, r31, r5
    srw     r11, r12, r6
    srw     r8, r30, r6
    srw     r0, r29, r6
    slw     r9, r30, r5
    or      r30, r9, r0
    or      r31, r10, r11
    slw     r12, r12, r5
    slw     r29, r29, r5
    srwi    r7, r31, 16
    divwu   r0, r8, r7
    clrlwi  r4, r31, 16
    srwi    r11, r30, 16
    mullw   r9, r0, r7
    mr      r10, r0
    mullw   r3, r10, r4
    subf    r8, r9, r8
    slwi    r0, r8, 16
    or      r8, r0, r11
    cmplw   r8, r3
    bge     L_8017A4A4
    add     r8, r8, r31
    subi    r10, r10, 0x1
    cmplw   r8, r31
    blt     L_8017A4A4
    cmplw   r8, r3
    bge     L_8017A4A4
    subi    r10, r10, 0x1
    add     r8, r8, r31
L_8017A4A4:
    subf    r8, r3, r8
    clrlwi  r11, r30, 16
    divwu   r0, r8, r7
    mullw   r9, r0, r7
    mr      r7, r0
    mullw   r3, r7, r4
    subf    r4, r9, r8
    slwi    r0, r4, 16
    or      r4, r0, r11
    cmplw   r4, r3
    bge     L_8017A4F0
    add     r4, r4, r31
    subi    r7, r7, 0x1
    cmplw   r4, r31
    blt     L_8017A4F0
    cmplw   r4, r3
    bge     L_8017A4F0
    subi    r7, r7, 0x1
    add     r4, r4, r31
L_8017A4F0:
    subf    r4, r3, r4
    slwi    r9, r10, 16
    or      r9, r9, r7
    mr      r30, r4
    clrlwi  r0, r9, 16
    clrlwi  r11, r12, 16
    srwi    r10, r12, 16
    mullw   r7, r0, r11
    srwi    r9, r9, 16
    mullw   r8, r0, r10
    mullw   r11, r9, r11
    srwi    r0, r7, 16
    add     r8, r8, r0
    mullw   r10, r9, r10
    add     r8, r8, r11
    cmplw   r8, r11
    bge     L_8017A538
    addis   r10, r10, 0x1
L_8017A538:
    slwi    r0, r8, 16
    srwi    r9, r8, 16
    clrlwi  r11, r7, 16
    add     r9, r10, r9
    add     r0, r0, r11
    cmplw   r9, r30
    bgt     L_8017A564
    cmpw    r9, r30
    bne     L_8017A580
    cmplw   r0, r29
    ble     L_8017A580
L_8017A564:
    subf    r11, r12, r0
    subf    r9, r31, r9
    subfc   r0, r11, r0
    subfe   r0, r0, r0
    neg     r0, r0
    subf    r9, r0, r9
    mr      r0, r11
L_8017A580:
    cmpwi   r26, 0x0
    beq     L_8017A5B8
    subf    r11, r0, r29
    subf    r9, r9, r4
    subfc   r0, r11, r29
    subfe   r0, r0, r0
    neg     r0, r0
    subf    r30, r0, r9
    slw     r10, r30, r6
    srw     r11, r11, r5
    or      r28, r10, r11
    srw     r27, r30, r5
L_8017A5B0:
    stw     r27, 0x0(r26)
    stw     r28, 0x4(r26)
L_8017A5B8:
    lwz     r3, 0x8(r1)
    lwz     r4, 0xc(r1)
    lmw     r26, 0x10(r1)
    addi    r1, r1, 0x28
    blr
    // clang-format on
}
