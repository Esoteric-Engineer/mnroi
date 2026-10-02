extern void* memcpy(void* dst, const void* src, unsigned long n);

/* Vendor-added: inserts ',' every 3 digits (printf "'" flag). */
asm char* __group_digits(char* buf, char* start, char* end, int* len)
{
    // clang-format off
    nofralloc
    stwu    r1, -0x18(r1)
    mflr    r0
    stmw    r28, 0x8(r1)
    stw     r0, 0x1c(r1)
    mr      r31, r1
    subf    r9, r4, r5
    lwz     r11, 0(r1)
    addi    r0, r9, 0x18
    addi    r30, r9, 0xa
    clrrwi  r0, r0, 3
    mr      r28, r6
    neg     r0, r0
    li      r12, 0
    stwux   r11, r1, r0
    mr.     r29, r3
    add     r9, r1, r30
    addi    r6, r9, 7
    beq     ret0
    cmpwi   r4, 0
    beq     ret0
    cmpwi   r5, 0
    bne     scan
ret0:
    li      r3, 0
    b       epilogue
scan:
    li      r7, 0
    mr      r10, r4
    mr      r8, r5
    cmplw   r10, r5
    bgt     scandone
scanloop:
    lbz     r0, 0(r10)
    extsb   r0, r0
    cmpwi   r0, 0x45
    beq     isexp
    bgt     chkE
    cmpwi   r0, 0x2e
    beq     isdot
    b       scannext
chkE:
    cmpwi   r0, 0x65
    beq     isexp
    b       scannext
isdot:
    mr      r8, r10
    cmpwi   r7, 0
    bne     scannext
    li      r7, 1
    b       scannext
isexp:
    li      r7, 2
scannext:
    addi    r10, r10, 1
    cmplw   r10, r5
    bgt     scandone
    cmpwi   r7, 2
    bne     scanloop
scandone:
    cmpwi   r7, 2
    bne     group
    mr      r3, r4
    b       epilogue
group:
    mr      r10, r5
    cmplw   r10, r4
    ble     last
    lis     r5, 0x5555
    li      r3, 0x2c
    ori     r5, r5, 0x5556
copyloop:
    lbz     r0, 0(r10)
    cmplw   r10, r8
    stb     r0, 0(r6)
    subi    r6, r6, 1
    bgt     copynext
    mulhw   r11, r12, r5
    srawi   r9, r12, 31
    subf    r11, r9, r11
    slwi    r0, r11, 1
    add     r0, r0, r11
    cmpw    r12, r0
    bne     inc
    cmpwi   r12, 0
    beq     inc
    stb     r3, 0(r6)
    addi    r30, r30, 1
    subi    r6, r6, 1
inc:
    addi    r12, r12, 1
copynext:
    subi    r10, r10, 1
    cmplw   r10, r4
    bgt     copyloop
last:
    lbz     r0, 0(r10)
    subi    r30, r30, 0xa
    mr      r4, r6
    mr      r3, r29
    stb     r0, 0(r6)
    mr      r5, r30
    crclr   6
    bl      memcpy
    stw     r30, 0(r28)
    mr      r3, r29
epilogue:
    lwz     r11, 0(r1)
    lwz     r0, 4(r11)
    mtlr    r0
    lmw     r28, -0x10(r11)
    mr      r1, r11
    blr
    // clang-format on
}
