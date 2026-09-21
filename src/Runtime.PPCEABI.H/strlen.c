asm unsigned long strlen(const char* str)
{
    // clang-format off
    nofralloc
    mr      r10, r3
    andi.   r0, r3, 0x3
    bne     tail
    lwz     r11, 0(r3)
    lis     r0, 0x8080
    ori     r0, r0, 0x8080
    subis   r9, r11, 0x101
    subi    r9, r9, 0x101
    andc    r11, r9, r11
    and.    r9, r11, r0
    bne     tail
    lis     r0, 0x8080
    ori     r0, r0, 0x8080
wloop:
    lwzu    r11, 4(r3)
    subis   r9, r11, 0x101
    subi    r9, r9, 0x101
    andc    r11, r9, r11
    and.    r9, r11, r0
    beq     wloop
tail:
    lbz     r0, 0(r3)
    cmpwi   r0, 0
    beq     done
bloop:
    lbzu    r0, 1(r3)
    cmpwi   r0, 0
    bne     bloop
done:
    subf    r3, r10, r3
    blr
    // clang-format on
}
