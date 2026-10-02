asm char* strncpy(char* dst, const char* src, unsigned long n)
{
    // clang-format off
    nofralloc
    or      r0, r4, r3
    mr      r10, r3
    andi.   r9, r0, 0x3
    bne     bytes
    cmplwi  r5, 0x3
    ble     bytes
    lwz     r11, 0(r4)
    lis     r0, 0x8080
    ori     r0, r0, 0x8080
    subis   r9, r11, 0x101
    subi    r9, r9, 0x101
    andc    r11, r9, r11
    and.    r9, r11, r0
    bne     bytes
    lis     r8, 0x8080
    ori     r8, r8, 0x8080
wloop:
    lwz     r0, 0(r4)
    subi    r5, r5, 4
    addi    r4, r4, 4
    cmplwi  r5, 0x3
    stw     r0, 0(r10)
    addi    r10, r10, 4
    ble     bytes
    lwz     r11, 0(r4)
    subis   r9, r11, 0x101
    subi    r9, r9, 0x101
    andc    r11, r9, r11
    and.    r0, r11, r8
    beq     wloop
bytes:
    cmpwi   r5, 0
    beq     pad
    lbz     r9, 0(r4)
    subi    r5, r5, 1
    addi    r4, r4, 1
    extsb   r0, r9
    stb     r9, 0(r10)
    cmpwi   r0, 0
    addi    r10, r10, 1
    bne     bytes
pad:
    mr      r0, r5
    cmpwi   r0, 0
    subi    r5, r5, 1
    beqlr
    li      r9, 0
ploop:
    mr      r0, r5
    stb     r9, 0(r10)
    cmpwi   r0, 0
    addi    r10, r10, 1
    subi    r5, r5, 1
    bne     ploop
    blr
    // clang-format on
}
