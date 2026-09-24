// qsort(base, n, size, cmp): Newlib BSD qsort (swaptype from alignment, insertion sort for n < 7, median of 3/9 pivot, inlined swaps, recurses on the smaller partition).
asm void qsort(void* base, unsigned long n, unsigned long size, int (*cmp)(const void*, const void*))
{
    // clang-format off
    nofralloc
    stwu    r1, -0x48(r1)
    mflr    r0
    stmw    r17, 0xc(r1)
    stw     r0, 0x4c(r1)
    mr      r26, r3
    mr      r22, r4
    mr      r29, r5
    mr      r23, r6
L_80171620:
    andi.   r0, r26, 0x3
    bne     L_80171644
    andi.   r0, r29, 0x3
    bne     L_80171644
    li      r18, 0x1
    cmpwi   r29, 0x4
    bne     L_80171648
    li      r18, 0x0
    b       L_80171648
L_80171644:
    li      r18, 0x2
L_80171648:
    li      r19, 0x0
    cmplwi  r22, 0x6
    bgt     L_80171748
    mullw   r0, r22, r29
    add     r30, r26, r29
    add     r0, r26, r0
    cmplw   r30, r0
    bge     L_80171F78
    cmpwi   r18, 0x1
    mr      r24, r0
    cmpwi   cr7, r18, 0x0
    mfcr    r25
    mfcr    r27
    slwi    r27, r27, 28
L_80171680:
    mr      r31, r30
    add     r28, r30, r29
    b       L_80171710
L_8017168C:
    mtcrf   128, r27
    bne     L_801716A8
    lwz     r0, 0x0(r30)
    lwz     r9, 0x0(r31)
    stw     r0, 0x0(r31)
    stw     r9, 0x0(r30)
    b       L_8017170C
L_801716A8:
    mtcrf   128, r25
    bgt     L_801716E0
    mr      r3, r31
    srwi    r10, r29, 2
    mr      r11, r30
L_801716BC:
    lwz     r9, 0x0(r11)
    subic.  r10, r10, 0x1
    lwz     r0, 0x0(r3)
    stw     r9, 0x0(r3)
    stw     r0, 0x0(r11)
    addi    r3, r3, 0x4
    addi    r11, r11, 0x4
    bgt     L_801716BC
    b       L_8017170C
L_801716E0:
    mr      r3, r31
    mr      r10, r29
    mr      r11, r30
L_801716EC:
    lbz     r9, 0x0(r11)
    subic.  r10, r10, 0x1
    lbz     r0, 0x0(r3)
    stb     r9, 0x0(r3)
    stb     r0, 0x0(r11)
    addi    r3, r3, 0x1
    addi    r11, r11, 0x1
    bgt     L_801716EC
L_8017170C:
    mr      r31, r30
L_80171710:
    cmplw   r31, r26
    ble     L_80171738
    subf    r30, r29, r31
    mr      r4, r31
    mr      r3, r30
    mtlr    r23
    crclr   6
    blrl
    cmpwi   r3, 0x0
    bgt     L_8017168C
L_80171738:
    mr      r30, r28
    cmplw   r30, r24
    blt     L_80171680
    b       L_80171F78
L_80171748:
    srwi    r0, r22, 1
    cmplwi  r22, 0x7
    mullw   r0, r0, r29
    subi    r17, r22, 0x1
    add     r30, r26, r0
    ble     L_80171A4C
    mullw   r0, r17, r29
    mr      r31, r26
    cmplwi  r22, 0x28
    add     r25, r26, r0
    ble     L_801719A0
    srwi    r0, r22, 3
    mr      r3, r26
    mullw   r24, r0, r29
    mtlr    r23
    add     r28, r26, r24
    add     r31, r24, r24
    mr      r4, r28
    add     r31, r31, r26
    crclr   6
    blrl
    cmpwi   r3, 0x0
    bge     L_801717E8
    mr      r3, r28
    mr      r4, r31
    mtlr    r23
    crclr   6
    blrl
    cmpwi   r3, 0x0
    blt     L_8017182C
    mr      r3, r26
    mr      r4, r31
    mtlr    r23
    crclr   6
    blrl
    cmpwi   r3, 0x0
    mr      r0, r26
    bge     L_80171830
    mr      r0, r31
    b       L_80171830
L_801717E8:
    mr      r3, r28
    mr      r4, r31
    mtlr    r23
    crclr   6
    blrl
    cmpwi   r3, 0x0
    bgt     L_8017182C
    mr      r3, r26
    mr      r4, r31
    mtlr    r23
    crclr   6
    blrl
    cmpwi   r3, 0x0
    mr      r0, r31
    bge     L_80171830
    mr      r0, r26
    b       L_80171830
L_8017182C:
    mr      r0, r28
L_80171830:
    subf    r27, r24, r30
    mr      r4, r30
    mr      r3, r27
    mtlr    r23
    mr      r31, r0
    add     r28, r30, r24
    crclr   6
    blrl
    cmpwi   r3, 0x0
    bge     L_8017189C
    mr      r3, r30
    mr      r4, r28
    mtlr    r23
    crclr   6
    blrl
    cmpwi   r3, 0x0
    blt     L_801718E0
    mr      r3, r27
    mr      r4, r28
    mtlr    r23
    crclr   6
    blrl
    cmpwi   r3, 0x0
    mr      r9, r27
    bge     L_801718E4
    mr      r9, r28
    b       L_801718E4
L_8017189C:
    mr      r3, r30
    mr      r4, r28
    mtlr    r23
    crclr   6
    blrl
    cmpwi   r3, 0x0
    bgt     L_801718E0
    mr      r3, r27
    mr      r4, r28
    mtlr    r23
    crclr   6
    blrl
    cmpwi   r3, 0x0
    mr      r9, r28
    bge     L_801718E4
    mr      r9, r27
    b       L_801718E4
L_801718E0:
    mr      r9, r30
L_801718E4:
    add     r0, r24, r24
    subf    r28, r24, r25
    subf    r27, r0, r25
    mr      r4, r28
    mr      r3, r27
    mtlr    r23
    mr      r30, r9
    crclr   6
    blrl
    cmpwi   r3, 0x0
    bge     L_80171954
    mr      r3, r28
    mr      r4, r25
    mtlr    r23
    crclr   6
    blrl
    cmpwi   r3, 0x0
    blt     L_80171998
    mr      r3, r27
    mr      r4, r25
    mtlr    r23
    crclr   6
    blrl
    cmpwi   r3, 0x0
    mr      r3, r27
    bge     L_8017199C
    mr      r3, r25
    b       L_8017199C
L_80171954:
    mr      r3, r28
    mr      r4, r25
    mtlr    r23
    crclr   6
    blrl
    cmpwi   r3, 0x0
    bgt     L_80171998
    mr      r3, r27
    mr      r4, r25
    mtlr    r23
    crclr   6
    blrl
    cmpwi   r3, 0x0
    mr      r3, r25
    bge     L_8017199C
    mr      r3, r27
    b       L_8017199C
L_80171998:
    mr      r3, r28
L_8017199C:
    mr      r25, r3
L_801719A0:
    mr      r3, r31
    mr      r4, r30
    mtlr    r23
    crclr   6
    blrl
    cmpwi   r3, 0x0
    bge     L_80171A00
    mr      r3, r30
    mr      r4, r25
    mtlr    r23
    crclr   6
    blrl
    cmpwi   r3, 0x0
    blt     L_80171A44
    mr      r3, r31
    mr      r4, r25
    mtlr    r23
    crclr   6
    blrl
    cmpwi   r3, 0x0
    mr      r3, r31
    bge     L_80171A48
    mr      r3, r25
    b       L_80171A48
L_80171A00:
    mr      r3, r30
    mr      r4, r25
    mtlr    r23
    crclr   6
    blrl
    cmpwi   r3, 0x0
    bgt     L_80171A44
    mr      r3, r31
    mr      r4, r25
    mtlr    r23
    crclr   6
    blrl
    cmpwi   r3, 0x0
    mr      r3, r25
    bge     L_80171A48
    mr      r3, r31
    b       L_80171A48
L_80171A44:
    mr      r3, r30
L_80171A48:
    mr      r30, r3
L_80171A4C:
    cmpwi   r18, 0x0
    mfcr    r24
    bne     L_80171A74
    lwz     r9, 0x0(r30)
    mullw   r20, r22, r29
    lwz     r0, 0x0(r26)
    add     r21, r26, r29
    stw     r9, 0x0(r26)
    stw     r0, 0x0(r30)
    b       L_80171AE8
L_80171A74:
    cmpwi   r18, 0x1
    bgt     L_80171AB4
    mullw   r20, r22, r29
    mr      r3, r30
    srwi    r10, r29, 2
    mr      r11, r26
    add     r21, r26, r29
L_80171A90:
    lwz     r9, 0x0(r3)
    subic.  r10, r10, 0x1
    lwz     r0, 0x0(r11)
    stw     r9, 0x0(r11)
    stw     r0, 0x0(r3)
    addi    r11, r11, 0x4
    addi    r3, r3, 0x4
    bgt     L_80171A90
    b       L_80171AE8
L_80171AB4:
    mullw   r20, r22, r29
    mr      r3, r30
    mr      r10, r29
    mr      r11, r26
    add     r21, r26, r29
L_80171AC8:
    lbz     r9, 0x0(r3)
    subic.  r10, r10, 0x1
    lbz     r0, 0x0(r11)
    stb     r9, 0x0(r11)
    stb     r0, 0x0(r3)
    addi    r11, r11, 0x1
    addi    r3, r3, 0x1
    bgt     L_80171AC8
L_80171AE8:
    mullw   r0, r17, r29
    mr      r31, r21
    cmpwi   cr7, r18, 0x1
    mr      r28, r31
    mfcr    r22
    slwi    r22, r22, 28
    add     r27, r26, r0
    mr      r30, r27
    b       L_80171BAC
L_80171B0C:
    add     r6, r31, r29
    bne     L_80171BA8
    li      r19, 0x1
    mtcrf   128, r24
    bne     L_80171B38
    lwz     r9, 0x0(r31)
    add     r8, r28, r29
    lwz     r0, 0x0(r28)
    stw     r9, 0x0(r28)
    stw     r0, 0x0(r31)
    b       L_80171BA4
L_80171B38:
    mtcrf   128, r22
    bgt     L_80171B74
    mr      r11, r28
    mr      r3, r31
    srwi    r10, r29, 2
    add     r8, r11, r29
L_80171B50:
    lwz     r9, 0x0(r3)
    subic.  r10, r10, 0x1
    lwz     r0, 0x0(r11)
    stw     r9, 0x0(r11)
    stw     r0, 0x0(r3)
    addi    r11, r11, 0x4
    addi    r3, r3, 0x4
    bgt     L_80171B50
    b       L_80171BA4
L_80171B74:
    mr      r11, r28
    mr      r3, r31
    mr      r10, r29
    add     r8, r11, r29
L_80171B84:
    lbz     r9, 0x0(r3)
    subic.  r10, r10, 0x1
    lbz     r0, 0x0(r11)
    stb     r9, 0x0(r11)
    stb     r0, 0x0(r3)
    addi    r11, r11, 0x1
    addi    r3, r3, 0x1
    bgt     L_80171B84
L_80171BA4:
    mr      r28, r8
L_80171BA8:
    mr      r31, r6
L_80171BAC:
    cmplw   r31, r30
    bgt     L_80171BD0
    mr      r3, r31
    mr      r4, r26
    mtlr    r23
    crclr   6
    blrl
    cmpwi   r3, 0x0
    ble     L_80171B0C
L_80171BD0:
    cmpwi   r18, 0x1
    mfcr    r25
    b       L_80171C7C
L_80171BDC:
    subf    r7, r29, r30
    bne     L_80171C78
    li      r19, 0x1
    mtcrf   128, r24
    bne     L_80171C08
    lwz     r9, 0x0(r27)
    subf    r8, r29, r27
    lwz     r0, 0x0(r30)
    stw     r9, 0x0(r30)
    stw     r0, 0x0(r27)
    b       L_80171C74
L_80171C08:
    mtcrf   128, r25
    bgt     L_80171C44
    mr      r11, r27
    mr      r3, r30
    srwi    r10, r29, 2
    subf    r8, r29, r11
L_80171C20:
    lwz     r9, 0x0(r11)
    subic.  r10, r10, 0x1
    lwz     r0, 0x0(r3)
    stw     r9, 0x0(r3)
    stw     r0, 0x0(r11)
    addi    r3, r3, 0x4
    addi    r11, r11, 0x4
    bgt     L_80171C20
    b       L_80171C74
L_80171C44:
    mr      r11, r27
    mr      r3, r30
    mr      r10, r29
    subf    r8, r29, r11
L_80171C54:
    lbz     r9, 0x0(r11)
    subic.  r10, r10, 0x1
    lbz     r0, 0x0(r3)
    stb     r9, 0x0(r3)
    stb     r0, 0x0(r11)
    addi    r3, r3, 0x1
    addi    r11, r11, 0x1
    bgt     L_80171C54
L_80171C74:
    mr      r27, r8
L_80171C78:
    mr      r30, r7
L_80171C7C:
    cmplw   r31, r30
    bgt     L_80171D48
    mr      r3, r30
    mr      r4, r26
    mtlr    r23
    crclr   6
    blrl
    cmpwi   r3, 0x0
    bge     L_80171BDC
    mtcrf   128, r24
    bne     L_80171CC4
    lwz     r9, 0x0(r30)
    add     r6, r31, r29
    lwz     r0, 0x0(r31)
    subf    r7, r29, r30
    stw     r9, 0x0(r31)
    stw     r0, 0x0(r30)
    b       L_80171D38
L_80171CC4:
    mtcrf   128, r22
    bgt     L_80171D04
    mr      r11, r31
    mr      r3, r30
    srwi    r10, r29, 2
    add     r6, r11, r29
    subf    r7, r29, r3
L_80171CE0:
    lwz     r9, 0x0(r3)
    subic.  r10, r10, 0x1
    lwz     r0, 0x0(r11)
    stw     r9, 0x0(r11)
    stw     r0, 0x0(r3)
    addi    r11, r11, 0x4
    addi    r3, r3, 0x4
    bgt     L_80171CE0
    b       L_80171D38
L_80171D04:
    mr      r11, r31
    mr      r3, r30
    mr      r10, r29
    add     r6, r11, r29
    subf    r7, r29, r3
L_80171D18:
    lbz     r9, 0x0(r3)
    subic.  r10, r10, 0x1
    lbz     r0, 0x0(r11)
    stb     r9, 0x0(r11)
    stb     r0, 0x0(r3)
    addi    r11, r11, 0x1
    addi    r3, r3, 0x1
    bgt     L_80171D18
L_80171D38:
    mr      r31, r6
    mr      r30, r7
    li      r19, 0x1
    b       L_80171BAC
L_80171D48:
    cmpwi   r19, 0x0
    bne     L_80171E38
    mr      r30, r21
    add     r0, r26, r20
    cmplw   r30, r0
    bge     L_80171F78
    cmpwi   cr7, r18, 0x1
    mr      r25, r0
    mfcr    r27
    slwi    r27, r27, 28
L_80171D70:
    mr      r31, r30
    add     r28, r30, r29
    b       L_80171E00
L_80171D7C:
    mtcrf   128, r24
    bne     L_80171D98
    lwz     r0, 0x0(r30)
    lwz     r9, 0x0(r31)
    stw     r0, 0x0(r31)
    stw     r9, 0x0(r30)
    b       L_80171DFC
L_80171D98:
    mtcrf   128, r27
    bgt     L_80171DD0
    mr      r3, r31
    srwi    r10, r29, 2
    mr      r11, r30
L_80171DAC:
    lwz     r9, 0x0(r11)
    subic.  r10, r10, 0x1
    lwz     r0, 0x0(r3)
    stw     r9, 0x0(r3)
    stw     r0, 0x0(r11)
    addi    r3, r3, 0x4
    addi    r11, r11, 0x4
    bgt     L_80171DAC
    b       L_80171DFC
L_80171DD0:
    mr      r3, r31
    mr      r10, r29
    mr      r11, r30
L_80171DDC:
    lbz     r9, 0x0(r11)
    subic.  r10, r10, 0x1
    lbz     r0, 0x0(r3)
    stb     r9, 0x0(r3)
    stb     r0, 0x0(r11)
    addi    r3, r3, 0x1
    addi    r11, r11, 0x1
    bgt     L_80171DDC
L_80171DFC:
    mr      r31, r30
L_80171E00:
    cmplw   r31, r26
    ble     L_80171E28
    subf    r30, r29, r31
    mr      r4, r31
    mr      r3, r30
    mtlr    r23
    crclr   6
    blrl
    cmpwi   r3, 0x0
    bgt     L_80171D7C
L_80171E28:
    mr      r30, r28
    cmplw   r30, r25
    blt     L_80171D70
    b       L_80171F78
L_80171E38:
    subf    r4, r28, r31
    subf    r0, r26, r28
    mr      r7, r4
    add     r25, r26, r20
    cmpw    r4, r0
    ble     L_80171E54
    mr      r4, r0
L_80171E54:
    subf    r30, r30, r27
    subf    r8, r27, r25
    cmpwi   r4, 0x0
    ble     L_80171EC8
    subf    r9, r4, r31
    cmpwi   r18, 0x1
    bgt     L_80171EA0
    srwi    r4, r4, 2
    mr      r10, r9
    mr      r11, r26
L_80171E7C:
    lwz     r9, 0x0(r10)
    subic.  r4, r4, 0x1
    lwz     r0, 0x0(r11)
    stw     r9, 0x0(r11)
    stw     r0, 0x0(r10)
    addi    r11, r11, 0x4
    addi    r10, r10, 0x4
    bgt     L_80171E7C
    b       L_80171EC8
L_80171EA0:
    mr      r10, r9
    mr      r11, r26
L_80171EA8:
    lbz     r9, 0x0(r10)
    subic.  r4, r4, 0x1
    lbz     r0, 0x0(r11)
    stb     r9, 0x0(r11)
    stb     r0, 0x0(r10)
    addi    r11, r11, 0x1
    addi    r10, r10, 0x1
    bgt     L_80171EA8
L_80171EC8:
    subf    r4, r29, r8
    cmplw   r4, r30
    ble     L_80171ED8
    mr      r4, r30
L_80171ED8:
    cmpwi   r4, 0x0
    ble     L_80171F44
    cmpwi   r18, 0x1
    subf    r9, r4, r25
    bgt     L_80171F1C
    srwi    r4, r4, 2
    mr      r3, r31
    mr      r11, r9
L_80171EF8:
    lwz     r9, 0x0(r11)
    subic.  r4, r4, 0x1
    lwz     r0, 0x0(r3)
    stw     r9, 0x0(r3)
    stw     r0, 0x0(r11)
    addi    r3, r3, 0x4
    addi    r11, r11, 0x4
    bgt     L_80171EF8
    b       L_80171F44
L_80171F1C:
    mr      r3, r31
    mr      r11, r9
L_80171F24:
    lbz     r9, 0x0(r11)
    subic.  r4, r4, 0x1
    lbz     r0, 0x0(r3)
    stb     r9, 0x0(r3)
    stb     r0, 0x0(r11)
    addi    r3, r3, 0x1
    addi    r11, r11, 0x1
    bgt     L_80171F24
L_80171F44:
    mr      r4, r7
    cmplw   r4, r29
    ble     L_80171F64
    divwu   r4, r4, r29
    mr      r3, r26
    mr      r5, r29
    mr      r6, r23
    bl      qsort
L_80171F64:
    cmplw   r30, r29
    ble     L_80171F78
    subf    r26, r30, r25
    divwu   r22, r30, r29
    b       L_80171620
L_80171F78:
    lwz     r0, 0x4c(r1)
    mtlr    r0
    lmw     r17, 0xc(r1)
    addi    r1, r1, 0x48
    blr
    // clang-format on
}
