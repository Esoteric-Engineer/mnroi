// The unit owns its .sdata2 literal pool.
// dtk's bake-sda rewrites the asm access into a fixed r13 offset and drops the relocation, which leaves the pool unreferenced and lets mwld dead-strip it. force_active keeps it linked.
#pragma force_active on

const unsigned long long DivdiClzTab0 = 0x0001020203030303ULL;
const unsigned long long DivdiClzTab1 = 0x0404040404040404ULL;
const unsigned long long DivdiClzTab2 = 0x0505050505050505ULL;
const unsigned long long DivdiClzTab3 = 0x0505050505050505ULL;
const unsigned long long DivdiClzTab4 = 0x0606060606060606ULL;
const unsigned long long DivdiClzTab5 = 0x0606060606060606ULL;
const unsigned long long DivdiClzTab6 = 0x0606060606060606ULL;
const unsigned long long DivdiClzTab7 = 0x0606060606060606ULL;
const unsigned long long DivdiClzTab8 = 0x0707070707070707ULL;
const unsigned long long DivdiClzTab9 = 0x0707070707070707ULL;
const unsigned long long DivdiClzTab10 = 0x0707070707070707ULL;
const unsigned long long DivdiClzTab11 = 0x0707070707070707ULL;
const unsigned long long DivdiClzTab12 = 0x0707070707070707ULL;
const unsigned long long DivdiClzTab13 = 0x0707070707070707ULL;
const unsigned long long DivdiClzTab14 = 0x0707070707070707ULL;
const unsigned long long DivdiClzTab15 = 0x0707070707070707ULL;
const unsigned long long DivdiClzTab16 = 0x0808080808080808ULL;
const unsigned long long DivdiClzTab17 = 0x0808080808080808ULL;
const unsigned long long DivdiClzTab18 = 0x0808080808080808ULL;
const unsigned long long DivdiClzTab19 = 0x0808080808080808ULL;
const unsigned long long DivdiClzTab20 = 0x0808080808080808ULL;
const unsigned long long DivdiClzTab21 = 0x0808080808080808ULL;
const unsigned long long DivdiClzTab22 = 0x0808080808080808ULL;
const unsigned long long DivdiClzTab23 = 0x0808080808080808ULL;
const unsigned long long DivdiClzTab24 = 0x0808080808080808ULL;
const unsigned long long DivdiClzTab25 = 0x0808080808080808ULL;
const unsigned long long DivdiClzTab26 = 0x0808080808080808ULL;
const unsigned long long DivdiClzTab27 = 0x0808080808080808ULL;
const unsigned long long DivdiClzTab28 = 0x0808080808080808ULL;
const unsigned long long DivdiClzTab29 = 0x0808080808080808ULL;
const unsigned long long DivdiClzTab30 = 0x0808080808080808ULL;
const unsigned long long DivdiClzTab31 = 0x0808080808080808ULL;

asm long long fn_80179138(long long a, long long b)
{
    // clang-format off
    nofralloc
    stwu    r1, -40(r1)
    stmw    r25, 12(r1)
    li      r25, 0
    mr      r11, r5
    mr      r12, r6
    cmpwi   r3, 0
    bge     L44
    neg     r10, r4
    neg     r3, r3
    li      r25, -1
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
    bge     L74
    neg     r8, r6
    neg     r5, r5
    not     r25, r25
    li      r0, 1
    cmpwi   r8, 0
    bne     L68
    li      r0, 0
L68:
    subf    r7, r0, r5
    mr      r11, r7
    mr      r12, r8
L74:
    mr      r31, r3
    mr      r8, r12
    mr      r30, r4
    mr.     r5, r11
    bne     L37c
    cmplw   r8, r31
    ble     L1a4
    li      r0, 0
    mr      r11, r12
    ori     r0, r0, 0xffff
    cmplw   r8, r0
    bgt     Lb4
    subfic  r0, r8, 255
    subfe   r0, r0, r0
    rlwinm  r10, r0, 0, 28, 28
    b       Lcc
Lb4:
    lis     r0, 255
    li      r10, 24
    ori     r0, r0, 0xffff
    cmplw   r8, r0
    bgt     Lcc
    li      r10, 16
Lcc:
    srw     r11, r11, r10
    addi    r9, r13, -12912
    lbzx    r0, r9, r11
    add     r0, r0, r10
    subfic  r7, r0, 32
    cmpwi   r7, 0
    beq     L100
    subfic  r0, r7, 32
    slw     r9, r31, r7
    srw     r0, r30, r0
    slw     r8, r8, r7
    or      r31, r9, r0
    slw     r30, r30, r7
L100:
    srwi    r10, r8, 16
    clrlwi  r12, r8, 16
    divwu   r0, r31, r10
    srwi    r11, r30, 16
    mullw   r9, r0, r10
    mr      r5, r0
    mullw   r6, r5, r12
    subf    r7, r9, r31
    slwi    r0, r7, 16
    or      r7, r0, r11
    cmplw   r7, r6
    bge     L150
    add     r7, r7, r8
    addi    r5, r5, -1
    cmplw   r7, r8
    blt     L150
    cmplw   r7, r6
    bge     L150
    addi    r5, r5, -1
    add     r7, r7, r8
L150:
    subf    r7, r6, r7
    clrlwi  r11, r30, 16
    divwu   r0, r7, r10
    mullw   r9, r0, r10
    mr      r10, r0
    mullw   r6, r10, r12
    subf    r0, r9, r7
    slwi    r0, r0, 16
    or      r0, r0, r11
    cmplw   r0, r6
    bge     L198
    add     r0, r0, r8
    addi    r10, r10, -1
    cmplw   r0, r8
    blt     L198
    cmplw   r0, r6
    bge     L198
    addi    r10, r10, -1
L198:
    slwi    r0, r5, 16
    or      r6, r0, r10
    b       L530
L1a4:
    cmpwi   r8, 0
    bne     L1b4
    li      r0, 1
    divwu   r8, r0, r5
L1b4:
    li      r0, 0
    ori     r0, r0, 0xffff
    cmplw   r8, r0
    bgt     L1d4
    subfic  r0, r8, 255
    subfe   r0, r0, r0
    rlwinm  r10, r0, 0, 28, 28
    b       L1ec
L1d4:
    lis     r0, 255
    li      r10, 24
    ori     r0, r0, 0xffff
    cmplw   r8, r0
    bgt     L1ec
    li      r10, 16
L1ec:
    srw     r11, r8, r10
    addi    r9, r13, -12912
    lbzx    r0, r9, r11
    add     r0, r0, r10
    subfic  r7, r0, 32
    cmpwi   r7, 0
    bne     L214
    subf    r31, r8, r31
    li      r4, 1
    b       L2d8
L214:
    subfic  r6, r7, 32
    slw     r9, r31, r7
    srw     r0, r30, r6
    srw     r12, r31, r6
    or      r31, r9, r0
    slw     r30, r30, r7
    slw     r8, r8, r7
    srwi    r7, r8, 16
    divwu   r0, r12, r7
    clrlwi  r4, r8, 16
    srwi    r11, r31, 16
    mullw   r9, r0, r7
    mr      r5, r0
    mullw   r6, r5, r4
    subf    r10, r9, r12
    slwi    r0, r10, 16
    or      r10, r0, r11
    cmplw   r10, r6
    bge     L280
    add     r10, r10, r8
    addi    r5, r5, -1
    cmplw   r10, r8
    blt     L280
    cmplw   r10, r6
    bge     L280
    addi    r5, r5, -1
    add     r10, r10, r8
L280:
    subf    r10, r6, r10
    clrlwi  r11, r31, 16
    divwu   r0, r10, r7
    mullw   r9, r0, r7
    mr      r7, r0
    mullw   r6, r7, r4
    subf    r9, r9, r10
    slwi    r0, r9, 16
    or      r9, r0, r11
    cmplw   r9, r6
    bge     L2cc
    add     r9, r9, r8
    addi    r7, r7, -1
    cmplw   r9, r8
    blt     L2cc
    cmplw   r9, r6
    bge     L2cc
    addi    r7, r7, -1
    add     r9, r9, r8
L2cc:
    slwi    r0, r5, 16
    subf    r31, r6, r9
    or      r4, r0, r7
L2d8:
    srwi    r10, r8, 16
    clrlwi  r12, r8, 16
    divwu   r0, r31, r10
    srwi    r11, r30, 16
    mullw   r9, r0, r10
    mr      r5, r0
    mullw   r6, r5, r12
    subf    r7, r9, r31
    slwi    r0, r7, 16
    or      r7, r0, r11
    cmplw   r7, r6
    bge     L328
    add     r7, r7, r8
    addi    r5, r5, -1
    cmplw   r7, r8
    blt     L328
    cmplw   r7, r6
    bge     L328
    addi    r5, r5, -1
    add     r7, r7, r8
L328:
    subf    r7, r6, r7
    clrlwi  r11, r30, 16
    divwu   r0, r7, r10
    mullw   r9, r0, r10
    mr      r10, r0
    mullw   r6, r10, r12
    subf    r0, r9, r7
    slwi    r0, r0, 16
    or      r0, r0, r11
    cmplw   r0, r6
    bge     L370
    add     r0, r0, r8
    addi    r10, r10, -1
    cmplw   r0, r8
    blt     L370
    cmplw   r0, r6
    bge     L370
    addi    r10, r10, -1
L370:
    slwi    r0, r5, 16
    or      r6, r0, r10
    b       L534
L37c:
    cmplw   r5, r31
    ble     L38c
L384:
    li      r6, 0
    b       L530
L38c:
    li      r0, 0
    ori     r0, r0, 0xffff
    cmplw   r5, r0
    bgt     L3ac
    subfic  r0, r5, 255
    subfe   r0, r0, r0
    rlwinm  r7, r0, 0, 28, 28
    b       L3c4
L3ac:
    lis     r0, 255
    li      r7, 24
    ori     r0, r0, 0xffff
    cmplw   r5, r0
    bgt     L3c4
    li      r7, 16
L3c4:
    srw     r11, r5, r7
    addi    r9, r13, -12912
    lbzx    r0, r9, r11
    add     r0, r0, r7
    subfic  r7, r0, 32
    cmpwi   r7, 0
    bne     L3f8
    cmplw   r31, r5
    bgt     L3f0
    cmplw   r30, r8
    blt     L384
L3f0:
    li      r6, 1
    b       L530
L3f8:
    subfic  r6, r7, 32
    slw     r10, r5, r7
    srw     r11, r30, r6
    srw     r9, r8, r6
    srw     r12, r31, r6
    slw     r0, r31, r7
    or      r31, r0, r11
    or      r5, r10, r9
    slw     r30, r30, r7
    slw     r8, r8, r7
    srwi    r10, r5, 16
    divwu   r0, r12, r10
    clrlwi  r3, r5, 16
    srwi    r11, r31, 16
    mullw   r9, r0, r10
    mr      r4, r0
    mullw   r6, r4, r3
    subf    r7, r9, r12
    slwi    r0, r7, 16
    or      r7, r0, r11
    cmplw   r7, r6
    bge     L470
    add     r7, r7, r5
    addi    r4, r4, -1
    cmplw   r7, r5
    blt     L470
    cmplw   r7, r6
    bge     L470
    addi    r4, r4, -1
    add     r7, r7, r5
L470:
    subf    r7, r6, r7
    clrlwi  r11, r31, 16
    divwu   r0, r7, r10
    mullw   r9, r0, r10
    mr      r10, r0
    mullw   r6, r10, r3
    subf    r7, r9, r7
    slwi    r0, r7, 16
    or      r7, r0, r11
    cmplw   r7, r6
    bge     L4bc
    add     r7, r7, r5
    addi    r10, r10, -1
    cmplw   r7, r5
    blt     L4bc
    cmplw   r7, r6
    bge     L4bc
    add     r7, r7, r5
    addi    r10, r10, -1
L4bc:
    slwi    r0, r4, 16
    subf    r7, r6, r7
    or      r6, r0, r10
    clrlwi  r11, r6, 16
    clrlwi  r9, r8, 16
    srwi    r10, r6, 16
    mullw   r5, r11, r9
    srwi    r8, r8, 16
    mullw   r11, r11, r8
    mullw   r9, r10, r9
    srwi    r0, r5, 16
    add     r11, r11, r0
    mullw   r3, r10, r8
    add     r11, r11, r9
    cmplw   r11, r9
    bge     L500
    addis   r3, r3, 1
L500:
    slwi    r0, r11, 16
    srwi    r9, r11, 16
    clrlwi  r11, r5, 16
    add     r3, r3, r9
    add     r0, r0, r11
    cmplw   r3, r7
    bgt     L52c
    cmpw    r3, r7
    bne     L530
    cmplw   r0, r30
    ble     L530
L52c:
    addi    r6, r6, -1
L530:
    li      r4, 0
L534:
    mr      r27, r6
    cmpwi   r25, 0
    mr      r26, r4
    mr      r3, r26
    mr      r4, r27
    beq     L570
    neg     r29, r4
    neg     r3, r3
    li      r0, 1
    cmpwi   r29, 0
    bne     L564
    li      r0, 0
L564:
    subf    r28, r0, r3
    mr      r3, r28
    mr      r4, r29
L570:
    lmw     r25, 12(r1)
    addi    r1, r1, 40
    blr
    // clang-format on
}
