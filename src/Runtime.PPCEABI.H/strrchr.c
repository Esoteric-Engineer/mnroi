asm char* strrchr(const char* s, int c)
{
    // clang-format off
    nofralloc
    lbz     r0, 0(r3)
    extsb   r4, r4
    li      r9, 0
    cmpwi   r0, 0
    beq     tail
loop:
    extsb   r0, r0
    cmpw    r0, r4
    bne     next
    mr      r9, r3
next:
    lbzu    r0, 1(r3)
    cmpwi   r0, 0
    bne     loop
tail:
    lbz     r0, 0(r3)
    extsb   r0, r0
    cmpw    r0, r4
    bne     done
    mr      r9, r3
done:
    mr      r3, r9
    blr
    // clang-format on
}
