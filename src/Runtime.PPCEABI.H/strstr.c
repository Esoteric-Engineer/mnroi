asm char* strstr(const char* str, const char* pat)
{
    // clang-format off
    nofralloc
    mr      r10, r3
    lbz     r0, 0(r10)
    cmpwi   r0, 0
    bne     scan
    lbz     r0, 0(r4)
    li      r3, 0
    cmpwi   r0, 0
    bnelr
retstr:
    mr      r3, r10
    blr
scan:
    li      r11, 0
    b       cmp
next:
    addi    r11, r11, 1
cmp:
    lbzx    r0, r4, r11
    extsb   r9, r0
    cmpwi   r9, 0
    beq     retstr
    lbzx    r0, r10, r11
    extsb   r0, r0
    cmpw    r9, r0
    beq     next
    lbzu    r0, 1(r10)
    cmpwi   r0, 0
    bne     scan
    li      r3, 0
    blr
    // clang-format on
}
