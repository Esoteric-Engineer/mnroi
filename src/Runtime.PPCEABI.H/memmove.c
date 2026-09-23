/* Transliterated from asm: Newlib memmove (non-size-optimised).
 The backward copy is bytes only, and the forward copy is memcpy's aligned 16-byte / word / byte loops. */
asm void* memmove(void* dst, const void* src, unsigned long n)
{
    // clang-format off
    nofralloc
    mr      r9, r4
    mr      r11, r3
    mr      r10, r5
    cmplw   r4, r3
    bge     forward
    add     r0, r4, r10
    cmplw   r3, r0
    bge     forward
    add     r11, r3, r10
    cmpwi   r10, 0
    mr      r4, r0
    subi    r10, r10, 1
    beqlr
back:
    lbzu    r0, -1(r4)
    cmpwi   r10, 0
    subi    r10, r10, 1
    stbu    r0, -1(r11)
    bne     back
    blr
forward:
    cmplwi  r5, 15
    ble     tail
    or      r0, r9, r3
    andi.   r8, r0, 3
    bne     tail
    mr      r4, r9
    mr      r11, r3
loop16:
    lwz     r9, 0(r4)
    subi    r10, r10, 16
    cmplwi  r10, 15
    stw     r9, 0(r11)
    lwzu    r0, 4(r4)
    stwu    r0, 4(r11)
    lwzu    r9, 4(r4)
    stwu    r9, 4(r11)
    lwzu    r0, 4(r4)
    stwu    r0, 4(r11)
    addi    r4, r4, 4
    addi    r11, r11, 4
    bgt     loop16
    cmplwi  r10, 3
    ble     tail
words:
    lwz     r0, 0(r4)
    subi    r10, r10, 4
    addi    r4, r4, 4
    cmplwi  r10, 3
    stw     r0, 0(r11)
    addi    r11, r11, 4
    bgt     words
tail:
    cmpwi   r10, 0
    subi    r10, r10, 1
    beqlr
bytes:
    lbz     r0, 0(r4)
    cmpwi   r10, 0
    addi    r4, r4, 1
    subi    r10, r10, 1
    stb     r0, 0(r11)
    addi    r11, r11, 1
    bne     bytes
    blr
    // clang-format on
}
