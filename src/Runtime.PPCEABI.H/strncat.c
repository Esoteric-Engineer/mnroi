asm char* strncat(char* s1, const char* s2, unsigned long n)
{
    // clang-format off
    nofralloc
    mr      r10, r3
    andi.   r0, r10, 0x3
    bne     bytescan
    lwz     r9, 0(r10)
    lis     r0, 0x8080
    ori     r0, r0, 0x8080
    addis   r11, r9, -0x101
    addi    r11, r11, -0x101
    andc    r9, r11, r9
    and.    r11, r9, r0
    bne     bytescan
    lis     r0, 0x8080
    ori     r0, r0, 0x8080
wloop:
    lwzu    r11, 4(r3)
    addis   r9, r11, -0x101
    addi    r9, r9, -0x101
    andc    r11, r9, r11
    and.    r9, r11, r0
    beq     wloop
bytescan:
    lbz     r0, 0(r3)
    addi    r5, r5, -1
    cmpwi   r0, 0
    beq     scandone
bloop:
    lbzu    r0, 1(r3)
    cmpwi   r0, 0
    bne     bloop
scandone:
    cmpwi   r5, -1
    b       test
copyloop:
    cmpwi   r5, 0
    bne     nopad
    stb     r5, 0(r3)
nopad:
    cmpwi   r5, 0
    addi    r5, r5, -1
test:
    beq     done
    lbz     r0, 0(r4)
    addi    r4, r4, 1
    extsb   r9, r0
    stb     r0, 0(r3)
    cmpwi   r9, 0
    addi    r3, r3, 1
    bne     copyloop
done:
    mr      r3, r10
    blr
    // clang-format on
}
