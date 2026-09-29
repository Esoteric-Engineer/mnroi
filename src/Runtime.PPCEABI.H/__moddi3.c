#pragma force_active on

const unsigned long long ModdiClzTab0 = 0x0001020203030303ULL;
const unsigned long long ModdiClzTab1 = 0x0404040404040404ULL;
const unsigned long long ModdiClzTab2 = 0x0505050505050505ULL;
const unsigned long long ModdiClzTab3 = 0x0505050505050505ULL;
const unsigned long long ModdiClzTab4 = 0x0606060606060606ULL;
const unsigned long long ModdiClzTab5 = 0x0606060606060606ULL;
const unsigned long long ModdiClzTab6 = 0x0606060606060606ULL;
const unsigned long long ModdiClzTab7 = 0x0606060606060606ULL;
const unsigned long long ModdiClzTab8 = 0x0707070707070707ULL;
const unsigned long long ModdiClzTab9 = 0x0707070707070707ULL;
const unsigned long long ModdiClzTab10 = 0x0707070707070707ULL;
const unsigned long long ModdiClzTab11 = 0x0707070707070707ULL;
const unsigned long long ModdiClzTab12 = 0x0707070707070707ULL;
const unsigned long long ModdiClzTab13 = 0x0707070707070707ULL;
const unsigned long long ModdiClzTab14 = 0x0707070707070707ULL;
const unsigned long long ModdiClzTab15 = 0x0707070707070707ULL;
const unsigned long long ModdiClzTab16 = 0x0808080808080808ULL;
const unsigned long long ModdiClzTab17 = 0x0808080808080808ULL;
const unsigned long long ModdiClzTab18 = 0x0808080808080808ULL;
const unsigned long long ModdiClzTab19 = 0x0808080808080808ULL;
const unsigned long long ModdiClzTab20 = 0x0808080808080808ULL;
const unsigned long long ModdiClzTab21 = 0x0808080808080808ULL;
const unsigned long long ModdiClzTab22 = 0x0808080808080808ULL;
const unsigned long long ModdiClzTab23 = 0x0808080808080808ULL;
const unsigned long long ModdiClzTab24 = 0x0808080808080808ULL;
const unsigned long long ModdiClzTab25 = 0x0808080808080808ULL;
const unsigned long long ModdiClzTab26 = 0x0808080808080808ULL;
const unsigned long long ModdiClzTab27 = 0x0808080808080808ULL;
const unsigned long long ModdiClzTab28 = 0x0808080808080808ULL;
const unsigned long long ModdiClzTab29 = 0x0808080808080808ULL;
const unsigned long long ModdiClzTab30 = 0x0808080808080808ULL;
const unsigned long long ModdiClzTab31 = 0x0808080808080808ULL;

asm long long __moddi3(long long a, long long b)
{
    // clang-format off
    nofralloc
    stwu    r1, -56(r1)
    stmw    r22, 16(r1)
    li      r22, 0
    mr      r7, r5
    mr      r8, r6
    cmpwi   r3, 0
    bge     L44
    neg     r10, r4
    neg     r3, r3
    li      r22, -1
    li      r0, 1
    cmpwi   r10, 0
    bne     L38
    li      r0, 0
L38:
    subf    r9, r0, r3
    mr      r3, r9
    mr      r4, r10
L44:
    cmpwi   r5, 0
    bge     L70
    neg     r12, r6
    neg     r5, r5
    li      r0, 1
    cmpwi   r12, 0
    bne     L64
    li      r0, 0
L64:
    subf    r11, r0, r5
    mr      r7, r11
    mr      r8, r12
L70:
    addi    r23, r1, 8
    mr      r12, r8
    mr      r29, r4
    mr      r30, r3
    mr.     r31, r7
    bne     L2b0
    cmplw   r12, r30
    ble     L104
    li      r0, 0
    mr      r11, r8
    ori     r0, r0, 0xffff
    cmplw   r12, r0
    bgt     Lb4
    subfic  r0, r12, 255
    subfe   r0, r0, r0
    rlwinm  r10, r0, 0, 28, 28
    b       Lcc
Lb4:
    lis     r0, 255
    li      r10, 24
    ori     r0, r0, 0xffff
    cmplw   r12, r0
    bgt     Lcc
    li      r10, 16
Lcc:
    srw     r11, r11, r10
    addi    r9, r13, -12656
    lbzx    r0, r9, r11
    add     r0, r0, r10
    subfic  r3, r0, 32
    cmpwi   r3, 0
    beq     L214
    subfic  r0, r3, 32
    slw     r9, r30, r3
    srw     r0, r29, r0
    slw     r12, r12, r3
    or      r30, r9, r0
    slw     r29, r29, r3
    b       L214
L104:
    cmpwi   r12, 0
    bne     L114
    li      r0, 1
    divwu   r12, r0, r31
L114:
    li      r0, 0
    ori     r0, r0, 0xffff
    cmplw   r12, r0
    bgt     L134
    subfic  r0, r12, 255
    subfe   r0, r0, r0
    rlwinm  r10, r0, 0, 28, 28
    b       L14c
L134:
    lis     r0, 255
    li      r10, 24
    ori     r0, r0, 0xffff
    cmplw   r12, r0
    bgt     L14c
    li      r10, 16
L14c:
    srw     r11, r12, r10
    addi    r9, r13, -12656
    lbzx    r0, r9, r11
    add     r0, r0, r10
    subfic  r3, r0, 32
    cmpwi   r3, 0
    bne     L170
    subf    r30, r12, r30
    b       L214
L170:
    subfic  r26, r3, 32
    slw     r9, r30, r3
    srw     r0, r29, r26
    srw     r8, r30, r26
    or      r30, r9, r0
    slw     r12, r12, r3
    slw     r29, r29, r3
    srwi    r6, r12, 16
    divwu   r0, r8, r6
    clrlwi  r10, r12, 16
    srwi    r11, r30, 16
    mullw   r9, r0, r6
    mullw   r7, r0, r10
    subf    r8, r9, r8
    slwi    r0, r8, 16
    or      r8, r0, r11
    cmplw   r8, r7
    bge     L1d0
    add     r8, r8, r12
    cmplw   r8, r12
    blt     L1d0
    cmplw   r8, r7
    bge     L1d0
    add     r8, r8, r12
L1d0:
    subf    r8, r7, r8
    clrlwi  r11, r30, 16
    divwu   r0, r8, r6
    mullw   r9, r0, r6
    mullw   r7, r0, r10
    subf    r0, r9, r8
    slwi    r0, r0, 16
    or      r0, r0, r11
    cmplw   r0, r7
    bge     L210
    add     r0, r0, r12
    cmplw   r0, r12
    blt     L210
    cmplw   r0, r7
    bge     L210
    add     r0, r0, r12
L210:
    subf    r30, r7, r0
L214:
    srwi    r7, r12, 16
    clrlwi  r6, r12, 16
    divwu   r0, r30, r7
    srwi    r11, r29, 16
    mullw   r9, r0, r7
    mullw   r8, r0, r6
    subf    r10, r9, r30
    slwi    r0, r10, 16
    or      r10, r0, r11
    cmplw   r10, r8
    bge     L258
    add     r10, r10, r12
    cmplw   r10, r12
    blt     L258
    cmplw   r10, r8
    bge     L258
    add     r10, r10, r12
L258:
    subf    r10, r8, r10
    clrlwi  r11, r29, 16
    divwu   r0, r10, r7
    mullw   r9, r0, r7
    mullw   r8, r0, r6
    subf    r0, r9, r10
    slwi    r0, r0, 16
    or      r0, r0, r11
    cmplw   r0, r8
    bge     L298
    add     r0, r0, r12
    cmplw   r0, r12
    blt     L298
    cmplw   r0, r8
    bge     L298
    add     r0, r0, r12
L298:
    subf    r29, r8, r0
    cmpwi   r23, 0
    beq     L4ec
    srw     r28, r29, r3
    li      r27, 0
    b       L4e4
L2b0:
    cmplw   r31, r30
    ble     L2cc
    mr      r28, r4
    mr      r27, r30
    stw     r27, 8(r1)
    stw     r28, 12(r1)
    b       L4ec
L2cc:
    li      r0, 0
    ori     r0, r0, 0xffff
    cmplw   r31, r0
    bgt     L2ec
    subfic  r0, r31, 255
    subfe   r0, r0, r0
    rlwinm  r10, r0, 0, 28, 28
    b       L304
L2ec:
    lis     r0, 255
    li      r10, 24
    ori     r0, r0, 0xffff
    cmplw   r31, r0
    bgt     L304
    li      r10, 16
L304:
    srw     r11, r31, r10
    addi    r9, r13, -12656
    lbzx    r0, r9, r11
    add     r0, r0, r10
    subfic  r3, r0, 32
    cmpwi   r3, 0
    bne     L360
    cmplw   r30, r31
    bgt     L330
    cmplw   r29, r12
    blt     L34c
L330:
    subf    r11, r12, r29
    subf    r9, r31, r30
    subfc   r0, r11, r29
    subfe   r0, r0, r0
    neg     r0, r0
    subf    r30, r0, r9
    mr      r29, r11
L34c:
    cmpwi   r23, 0
    beq     L4ec
    mr      r28, r29
    mr      r27, r30
    b       L4e4
L360:
    subfic  r26, r3, 32
    slw     r10, r31, r3
    srw     r11, r12, r26
    srw     r8, r30, r26
    srw     r0, r29, r26
    slw     r9, r30, r3
    or      r30, r9, r0
    or      r31, r10, r11
    slw     r12, r12, r3
    slw     r29, r29, r3
    srwi    r7, r31, 16
    divwu   r0, r8, r7
    clrlwi  r10, r31, 16
    srwi    r11, r30, 16
    mullw   r9, r0, r7
    mr      r4, r0
    mullw   r5, r4, r10
    subf    r8, r9, r8
    slwi    r0, r8, 16
    or      r8, r0, r11
    cmplw   r8, r5
    bge     L3d8
    add     r8, r8, r31
    addi    r4, r4, -1
    cmplw   r8, r31
    blt     L3d8
    cmplw   r8, r5
    bge     L3d8
    addi    r4, r4, -1
    add     r8, r8, r31
L3d8:
    subf    r8, r5, r8
    clrlwi  r11, r30, 16
    divwu   r0, r8, r7
    mullw   r9, r0, r7
    mr      r7, r0
    mullw   r5, r7, r10
    subf    r6, r9, r8
    slwi    r0, r6, 16
    or      r6, r0, r11
    cmplw   r6, r5
    bge     L424
    add     r6, r6, r31
    addi    r7, r7, -1
    cmplw   r6, r31
    blt     L424
    cmplw   r6, r5
    bge     L424
    addi    r7, r7, -1
    add     r6, r6, r31
L424:
    subf    r6, r5, r6
    slwi    r9, r4, 16
    or      r9, r9, r7
    mr      r30, r6
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
    bge     L46c
    addis   r10, r10, 1
L46c:
    slwi    r0, r8, 16
    srwi    r9, r8, 16
    clrlwi  r11, r7, 16
    add     r9, r10, r9
    add     r0, r0, r11
    cmplw   r9, r30
    bgt     L498
    cmpw    r9, r30
    bne     L4b4
    cmplw   r0, r29
    ble     L4b4
L498:
    subf    r11, r12, r0
    subf    r9, r31, r9
    subfc   r0, r11, r0
    subfe   r0, r0, r0
    neg     r0, r0
    subf    r9, r0, r9
    mr      r0, r11
L4b4:
    cmpwi   r23, 0
    beq     L4ec
    subf    r11, r0, r29
    subf    r9, r9, r6
    subfc   r0, r11, r29
    subfe   r0, r0, r0
    neg     r0, r0
    subf    r30, r0, r9
    slw     r10, r30, r26
    srw     r11, r11, r3
    or      r28, r10, r11
    srw     r27, r30, r3
L4e4:
    stw     r27, 0(r23)
    stw     r28, 4(r23)
L4ec:
    cmpwi   r22, 0
    beq     L520
    lwz     r9, 8(r1)
    lwz     r10, 12(r1)
    li      r11, 1
    neg     r25, r10
    neg     r0, r9
    cmpwi   r25, 0
    bne     L514
    li      r11, 0
L514:
    subf    r24, r11, r0
    stw     r24, 8(r1)
    stw     r25, 12(r1)
L520:
    lwz     r3, 8(r1)
    lwz     r4, 12(r1)
    lmw     r22, 16(r1)
    addi    r1, r1, 56
    blr
    // clang-format on
}
