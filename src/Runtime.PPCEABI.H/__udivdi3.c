#pragma force_active on

const unsigned long long UdivdiClzTab0 = 0x0001020203030303ULL;
const unsigned long long UdivdiClzTab1 = 0x0404040404040404ULL;
const unsigned long long UdivdiClzTab2 = 0x0505050505050505ULL;
const unsigned long long UdivdiClzTab3 = 0x0505050505050505ULL;
const unsigned long long UdivdiClzTab4 = 0x0606060606060606ULL;
const unsigned long long UdivdiClzTab5 = 0x0606060606060606ULL;
const unsigned long long UdivdiClzTab6 = 0x0606060606060606ULL;
const unsigned long long UdivdiClzTab7 = 0x0606060606060606ULL;
const unsigned long long UdivdiClzTab8 = 0x0707070707070707ULL;
const unsigned long long UdivdiClzTab9 = 0x0707070707070707ULL;
const unsigned long long UdivdiClzTab10 = 0x0707070707070707ULL;
const unsigned long long UdivdiClzTab11 = 0x0707070707070707ULL;
const unsigned long long UdivdiClzTab12 = 0x0707070707070707ULL;
const unsigned long long UdivdiClzTab13 = 0x0707070707070707ULL;
const unsigned long long UdivdiClzTab14 = 0x0707070707070707ULL;
const unsigned long long UdivdiClzTab15 = 0x0707070707070707ULL;
const unsigned long long UdivdiClzTab16 = 0x0808080808080808ULL;
const unsigned long long UdivdiClzTab17 = 0x0808080808080808ULL;
const unsigned long long UdivdiClzTab18 = 0x0808080808080808ULL;
const unsigned long long UdivdiClzTab19 = 0x0808080808080808ULL;
const unsigned long long UdivdiClzTab20 = 0x0808080808080808ULL;
const unsigned long long UdivdiClzTab21 = 0x0808080808080808ULL;
const unsigned long long UdivdiClzTab22 = 0x0808080808080808ULL;
const unsigned long long UdivdiClzTab23 = 0x0808080808080808ULL;
const unsigned long long UdivdiClzTab24 = 0x0808080808080808ULL;
const unsigned long long UdivdiClzTab25 = 0x0808080808080808ULL;
const unsigned long long UdivdiClzTab26 = 0x0808080808080808ULL;
const unsigned long long UdivdiClzTab27 = 0x0808080808080808ULL;
const unsigned long long UdivdiClzTab28 = 0x0808080808080808ULL;
const unsigned long long UdivdiClzTab29 = 0x0808080808080808ULL;
const unsigned long long UdivdiClzTab30 = 0x0808080808080808ULL;
const unsigned long long UdivdiClzTab31 = 0x0808080808080808ULL;

asm unsigned long long __udivdi3(unsigned long long a, unsigned long long b)
{
    // clang-format off
    nofralloc
    stwu    r1, -0x18(r1)
    stmw    r28, 0x8(r1)
    mr      r31, r3
    mr      r8, r6
    mr      r30, r4
    mr.     r3, r5
    bne     L_80179F60
    cmplw   r8, r31
    ble     L_80179D88
    li      r0, 0x0
    mr      r11, r6
    ori     r0, r0, 0xffff
    cmplw   r8, r0
    bgt     L_80179C98
    subfic  r0, r8, 0xff
    subfe   r0, r0, r0
    rlwinm  r5, r0, 0, 28, 28
    b       L_80179CB0
L_80179C98:
    lis     r0, 0xff
    li      r5, 0x18
    ori     r0, r0, 0xffff
    cmplw   r8, r0
    bgt     L_80179CB0
    li      r5, 0x10
L_80179CB0:
    srw     r11, r11, r5
    la    r9, UdivdiClzTab0
    lbzx    r0, r9, r11
    add     r0, r0, r5
    subfic  r5, r0, 0x20
    cmpwi   r5, 0x0
    beq     L_80179CE4
    subfic  r0, r5, 0x20
    slw     r9, r31, r5
    srw     r0, r30, r0
    slw     r8, r8, r5
    or      r31, r9, r0
    slw     r30, r30, r5
L_80179CE4:
    srwi    r10, r8, 16
    clrlwi  r5, r8, 16
    divwu   r0, r31, r10
    srwi    r11, r30, 16
    mullw   r9, r0, r10
    mr      r6, r0
    mullw   r7, r6, r5
    subf    r3, r9, r31
    slwi    r0, r3, 16
    or      r3, r0, r11
    cmplw   r3, r7
    bge     L_80179D34
    add     r3, r3, r8
    subi    r6, r6, 0x1
    cmplw   r3, r8
    blt     L_80179D34
    cmplw   r3, r7
    bge     L_80179D34
    subi    r6, r6, 0x1
    add     r3, r3, r8
L_80179D34:
    subf    r3, r7, r3
    clrlwi  r11, r30, 16
    divwu   r0, r3, r10
    mullw   r9, r0, r10
    mr      r10, r0
    mullw   r7, r10, r5
    subf    r0, r9, r3
    slwi    r0, r0, 16
    or      r0, r0, r11
    cmplw   r0, r7
    bge     L_80179D7C
    add     r0, r0, r8
    subi    r10, r10, 0x1
    cmplw   r0, r8
    blt     L_80179D7C
    cmplw   r0, r7
    bge     L_80179D7C
    subi    r10, r10, 0x1
L_80179D7C:
    slwi    r0, r6, 16
    or      r6, r0, r10
    b       L_8017A114
L_80179D88:
    cmpwi   r8, 0x0
    bne     L_80179D98
    li      r0, 0x1
    divwu   r8, r0, r3
L_80179D98:
    li      r0, 0x0
    ori     r0, r0, 0xffff
    cmplw   r8, r0
    bgt     L_80179DB8
    subfic  r0, r8, 0xff
    subfe   r0, r0, r0
    rlwinm  r10, r0, 0, 28, 28
    b       L_80179DD0
L_80179DB8:
    lis     r0, 0xff
    li      r10, 0x18
    ori     r0, r0, 0xffff
    cmplw   r8, r0
    bgt     L_80179DD0
    li      r10, 0x10
L_80179DD0:
    srw     r11, r8, r10
    la    r9, UdivdiClzTab0
    lbzx    r0, r9, r11
    add     r0, r0, r10
    subfic  r5, r0, 0x20
    cmpwi   r5, 0x0
    bne     L_80179DF8
    subf    r31, r8, r31
    li      r4, 0x1
    b       L_80179EBC
L_80179DF8:
    subfic  r7, r5, 0x20
    slw     r9, r31, r5
    srw     r0, r30, r7
    srw     r12, r31, r7
    or      r31, r9, r0
    slw     r30, r30, r5
    slw     r8, r8, r5
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
    bge     L_80179E64
    add     r10, r10, r8
    subi    r5, r5, 0x1
    cmplw   r10, r8
    blt     L_80179E64
    cmplw   r10, r6
    bge     L_80179E64
    subi    r5, r5, 0x1
    add     r10, r10, r8
L_80179E64:
    subf    r10, r6, r10
    clrlwi  r11, r31, 16
    divwu   r0, r10, r7
    mullw   r9, r0, r7
    mr      r7, r0
    mullw   r6, r7, r4
    subf    r3, r9, r10
    slwi    r0, r3, 16
    or      r3, r0, r11
    cmplw   r3, r6
    bge     L_80179EB0
    add     r3, r3, r8
    subi    r7, r7, 0x1
    cmplw   r3, r8
    blt     L_80179EB0
    cmplw   r3, r6
    bge     L_80179EB0
    subi    r7, r7, 0x1
    add     r3, r3, r8
L_80179EB0:
    slwi    r0, r5, 16
    subf    r31, r6, r3
    or      r4, r0, r7
L_80179EBC:
    srwi    r10, r8, 16
    clrlwi  r5, r8, 16
    divwu   r0, r31, r10
    srwi    r11, r30, 16
    mullw   r9, r0, r10
    mr      r6, r0
    mullw   r7, r6, r5
    subf    r3, r9, r31
    slwi    r0, r3, 16
    or      r3, r0, r11
    cmplw   r3, r7
    bge     L_80179F0C
    add     r3, r3, r8
    subi    r6, r6, 0x1
    cmplw   r3, r8
    blt     L_80179F0C
    cmplw   r3, r7
    bge     L_80179F0C
    subi    r6, r6, 0x1
    add     r3, r3, r8
L_80179F0C:
    subf    r3, r7, r3
    clrlwi  r11, r30, 16
    divwu   r0, r3, r10
    mullw   r9, r0, r10
    mr      r10, r0
    mullw   r7, r10, r5
    subf    r0, r9, r3
    slwi    r0, r0, 16
    or      r0, r0, r11
    cmplw   r0, r7
    bge     L_80179F54
    add     r0, r0, r8
    subi    r10, r10, 0x1
    cmplw   r0, r8
    blt     L_80179F54
    cmplw   r0, r7
    bge     L_80179F54
    subi    r10, r10, 0x1
L_80179F54:
    slwi    r0, r6, 16
    or      r6, r0, r10
    b       L_8017A118
L_80179F60:
    cmplw   r3, r31
    ble     L_80179F70
L_80179F68:
    li      r6, 0x0
    b       L_8017A114
L_80179F70:
    li      r0, 0x0
    ori     r0, r0, 0xffff
    cmplw   r3, r0
    bgt     L_80179F90
    subfic  r0, r3, 0xff
    subfe   r0, r0, r0
    rlwinm  r7, r0, 0, 28, 28
    b       L_80179FA8
L_80179F90:
    lis     r0, 0xff
    li      r7, 0x18
    ori     r0, r0, 0xffff
    cmplw   r3, r0
    bgt     L_80179FA8
    li      r7, 0x10
L_80179FA8:
    srw     r11, r3, r7
    la    r9, UdivdiClzTab0
    lbzx    r0, r9, r11
    add     r0, r0, r7
    subfic  r5, r0, 0x20
    cmpwi   r5, 0x0
    bne     L_80179FDC
    cmplw   r31, r3
    bgt     L_80179FD4
    cmplw   r30, r8
    blt     L_80179F68
L_80179FD4:
    li      r6, 0x1
    b       L_8017A114
L_80179FDC:
    subfic  r7, r5, 0x20
    slw     r10, r3, r5
    srw     r11, r30, r7
    srw     r9, r8, r7
    srw     r12, r31, r7
    slw     r0, r31, r5
    or      r31, r0, r11
    or      r3, r10, r9
    slw     r30, r30, r5
    slw     r8, r8, r5
    srwi    r10, r3, 16
    divwu   r0, r12, r10
    clrlwi  r4, r3, 16
    srwi    r11, r31, 16
    mullw   r9, r0, r10
    mr      r5, r0
    mullw   r6, r5, r4
    subf    r7, r9, r12
    slwi    r0, r7, 16
    or      r7, r0, r11
    cmplw   r7, r6
    bge     L_8017A054
    add     r7, r7, r3
    subi    r5, r5, 0x1
    cmplw   r7, r3
    blt     L_8017A054
    cmplw   r7, r6
    bge     L_8017A054
    subi    r5, r5, 0x1
    add     r7, r7, r3
L_8017A054:
    subf    r7, r6, r7
    clrlwi  r11, r31, 16
    divwu   r0, r7, r10
    mullw   r9, r0, r10
    mr      r10, r0
    mullw   r6, r10, r4
    subf    r7, r9, r7
    slwi    r0, r7, 16
    or      r7, r0, r11
    cmplw   r7, r6
    bge     L_8017A0A0
    add     r7, r7, r3
    subi    r10, r10, 0x1
    cmplw   r7, r3
    blt     L_8017A0A0
    cmplw   r7, r6
    bge     L_8017A0A0
    add     r7, r7, r3
    subi    r10, r10, 0x1
L_8017A0A0:
    slwi    r0, r5, 16
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
    bge     L_8017A0E4
    addis   r3, r3, 0x1
L_8017A0E4:
    slwi    r0, r11, 16
    srwi    r9, r11, 16
    clrlwi  r11, r5, 16
    add     r3, r3, r9
    add     r0, r0, r11
    cmplw   r3, r7
    bgt     L_8017A110
    cmpw    r3, r7
    bne     L_8017A114
    cmplw   r0, r30
    ble     L_8017A114
L_8017A110:
    subi    r6, r6, 0x1
L_8017A114:
    li      r4, 0x0
L_8017A118:
    mr      r29, r6
    mr      r28, r4
    mr      r3, r28
    mr      r4, r29
    lmw     r28, 0x8(r1)
    addi    r1, r1, 0x18
    blr
    // clang-format on
}
