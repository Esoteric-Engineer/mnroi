asm void* memchr(const void* s, int c, unsigned int n)
{
    // clang-format off
    nofralloc
    clrlwi  r4, r4, 24
    cmplwi  r5, 3
    ble     scalar_entry
    andi.   r0, r3, 3
    bne     scalar_entry
    li      r0, 4
    mr      r10, r3
    mtctr   r0
    li      r7, 0
pattern_loop:
    slwi    r0, r7, 8
    add     r7, r0, r4
    bdnz    pattern_loop
    cmplwi  r5, 3
    ble     finish_aligned
    lis     r8, 0x8080
    ori     r8, r8, 0x8080
word_loop:
    lwz     r11, 0(r10)
    xor     r11, r11, r7
    addis   r9, r11, -257
    addi    r9, r9, -257
    andc    r11, r9, r11
    and.    r0, r11, r8
    beq     word_next
    li      r0, 4
    mr      r3, r10
    mtctr   r0
byte_scan:
    lbz     r0, 0(r3)
    cmpw    r0, r4
    beqlr
    addi    r3, r3, 1
    bdnz    byte_scan
word_next:
    addi    r5, r5, -4
    addi    r10, r10, 4
    cmplwi  r5, 3
    bgt     word_loop
finish_aligned:
    mr      r3, r10
scalar_entry:
    cmpwi   r5, 0
    addi    r5, r5, -1
    beq     not_found
tail_loop:
    lbz     r0, 0(r3)
    cmpw    r0, r4
    beqlr
    cmpwi   r5, 0
    addi    r3, r3, 1
    addi    r5, r5, -1
    bne     tail_loop
not_found:
    li      r3, 0
    blr
    // clang-format on
}
