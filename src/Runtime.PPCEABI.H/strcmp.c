asm int strcmp(const char* s1, const char* s2)
{
    // clang-format off
    nofralloc
    or      r0, r3, r4
    andi.   r9, r0, 0x3
    bne     tail
    lwz     r9, 0(r3)
    lwz     r0, 0(r4)
    cmpw    r9, r0
    bne     tail
    lis     r10, 0x8080
    ori     r10, r10, 0x8080
wloop:
    lwz     r11, 0(r3)
    subis   r9, r11, 0x101
    subi    r9, r9, 0x101
    andc    r11, r9, r11
    and.    r0, r11, r10
    beq     wnext
    li      r3, 0
    blr
wnext:
    lwzu    r9, 4(r3)
    lwzu    r0, 4(r4)
    cmpw    r9, r0
    beq     wloop
tail:
    lbz     r0, 0(r3)
    extsb   r9, r0
    cmpwi   r9, 0
    beq     end
    lbz     r0, 0(r4)
    extsb   r0, r0
    cmpw    r9, r0
    bne     end
bloop:
    lbzu    r0, 1(r3)
    addi    r4, r4, 1
    extsb   r10, r0
    cmpwi   r10, 0
    beq     end
    lbz     r0, 0(r4)
    extsb   r0, r0
    cmpw    r10, r0
    beq     bloop
end:
    lbz     r0, 0(r3)
    lbz     r3, 0(r4)
    subf    r3, r3, r0
    blr
    // clang-format on
}
