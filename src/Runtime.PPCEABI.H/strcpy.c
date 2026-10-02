asm char* strcpy(char* dst, const char* src)
{
    // clang-format off
    nofralloc
    or      r0, r4, r3
    mr      r11, r3
    andi.   r9, r0, 0x3
    bne     tail
    lwz     r11, 0(r4)
    lis     r0, 0x8080
    ori     r0, r0, 0x8080
    mr      r10, r3
    subis   r9, r11, 0x101
    subi    r9, r9, 0x101
    andc    r11, r9, r11
    and.    r9, r11, r0
    bne     wdone
    lis     r8, 0x8080
    ori     r8, r8, 0x8080
wloop:
    lwz     r0, 0(r4)
    stw     r0, 0(r10)
    addi    r10, r10, 4
    lwzu    r11, 4(r4)
    subis   r9, r11, 0x101
    subi    r9, r9, 0x101
    andc    r11, r9, r11
    and.    r0, r11, r8
    beq     wloop
wdone:
    mr      r11, r10
tail:
    lbz     r0, 0(r4)
    addi    r4, r4, 1
    extsb   r9, r0
    stb     r0, 0(r11)
    cmpwi   r9, 0
    addi    r11, r11, 1
    bne     tail
    blr
    // clang-format on
}
