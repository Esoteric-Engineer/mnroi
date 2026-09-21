/*
 * Transliterated from asm, not the byte-loop memcmp from ac-decomp's mem.c: this one compares aligned words first.
 */
asm int memcmp(const void* a, const void* b, unsigned long n)
{
    // clang-format off
    nofralloc
    mr      r9, r3
    cmplwi  r5, 3
    ble     tail
    or      r0, r9, r4
    andi.   r11, r0, 3
    bne     tail
    lwz     r0, 0(r4)
    lwz     r9, 0(r3)
    cmpw    r9, r0
    bne     words_done
words:
    subi    r5, r5, 4
    addi    r3, r3, 4
    addi    r4, r4, 4
    cmplwi  r5, 3
    ble     words_done
    lwz     r9, 0(r3)
    lwz     r0, 0(r4)
    cmpw    r9, r0
    beq     words
words_done:
    mr      r9, r3
tail:
    cmpwi   r5, 0
    subi    r5, r5, 1
    beq     equal
bytes:
    lbz     r3, 0(r9)
    lbz     r0, 0(r4)
    cmpw    r3, r0
    beq     next
    subf    r3, r0, r3
    blr
next:
    cmpwi   r5, 0
    addi    r9, r9, 1
    addi    r4, r4, 1
    subi    r5, r5, 1
    bne     bytes
equal:
    li      r3, 0
    blr
    // clang-format on
}
