asm char* strchr(const char* s, int c)
{
    // clang-format off
    nofralloc
    mr      r9, r3
    clrlwi  r4, r4, 24
    andi.   r0, r3, 0x3
    bne     tail
    li      r8, 4
    li      r0, 0
    mtctr   r8
mask:
    slwi    r0, r0, 8
    or      r0, r0, r4
    bdnz    mask
    mr      r3, r9
    lis     r10, 0x8080
    lwz     r11, 0(r3)
    ori     r10, r10, 0x8080
    b       check
wloop:
    lwzu    r11, 4(r3)
check:
    subis   r9, r11, 0x101
    subi    r9, r9, 0x101
    andc    r9, r9, r11
    and.    r8, r9, r10
    bne     tail
    xor     r11, r11, r0
    subis   r9, r11, 0x101
    subi    r9, r9, 0x101
    andc    r11, r9, r11
    and.    r9, r11, r10
    beq     wloop
tail:
    lbz     r0, 0(r3)
    b       test
bloop:
    lbzu    r0, 1(r3)
test:
    cmpwi   r0, 0
    beq     end
    cmpw    r0, r4
    bne     bloop
end:
    lbz     r0, 0(r3)
    cmpw    r0, r4
    beqlr
    li      r3, 0
    blr
    // clang-format on
}
