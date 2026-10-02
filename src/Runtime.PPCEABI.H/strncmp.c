asm int strncmp(const char* s1, const char* s2, unsigned long n)
{
    // clang-format off
    nofralloc
    mr.     r5, r5
    bne     nonzero
retzero:
    li      r3, 0
    blr
nonzero:
    or      r0, r3, r4
    andi.   r9, r0, 0x3
    bne     bytes
    mr      r10, r3
    mr      r8, r4
    cmplwi  r5, 3
    ble     wdone
    lwz     r9, 0(r3)
    lwz     r0, 0(r4)
    cmpw    r9, r0
    bne     wdone
    lis     r7, 0x8080
    ori     r7, r7, 0x8080
wloop:
    subic.  r5, r5, 4
    beq     retzero
    lwz     r11, 0(r10)
    subis   r9, r11, 0x101
    subi    r9, r9, 0x101
    andc    r11, r9, r11
    and.    r0, r11, r7
    bne     retzero
    addi    r10, r10, 4
    addi    r8, r8, 4
    cmplwi  r5, 3
    ble     wdone
    lwz     r9, 0(r10)
    lwz     r0, 0(r8)
    cmpw    r9, r0
    beq     wloop
wdone:
    mr      r3, r10
    mr      r4, r8
bytes:
    mr      r0, r5
    cmpwi   r0, 0
    subi    r5, r5, 1
    beq     diff
    lbz     r11, 0(r3)
    lbz     r0, 0(r4)
    cmpw    r11, r0
    bne     diff
bloop:
    cmpwi   r5, 0
    beq     retzero
    cmpwi   r11, 0
    beq     retzero
    lbzu    r11, 1(r3)
    subi    r5, r5, 1
    lbzu    r0, 1(r4)
    cmpw    r11, r0
    beq     bloop
diff:
    lbz     r0, 0(r3)
    lbz     r3, 0(r4)
    subf    r3, r3, r0
    blr
    // clang-format on
}
