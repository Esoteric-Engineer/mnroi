/*
 * Transliterated from asm, not the byte-loop memcpy from ac-decomp's mem.c: this one copies aligned words first.
 */
asm void* memcpy(void* dst, const void* src, unsigned long n)
{
    // clang-format off
    nofralloc
    mr      r9, r3
    cmplwi  r5, 15
    ble     tail
    or      r0, r4, r3
    andi.   r11, r0, 3
    bne     tail
    mr      r11, r3
loop16:
    lwz     r9, 0(r4)
    subi    r5, r5, 16
    cmplwi  r5, 15
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
    cmplwi  r5, 3
    ble     words_done
words:
    lwz     r0, 0(r4)
    subi    r5, r5, 4
    addi    r4, r4, 4
    cmplwi  r5, 3
    stw     r0, 0(r11)
    addi    r11, r11, 4
    bgt     words
words_done:
    mr      r9, r11
tail:
    cmpwi   r5, 0
    subi    r5, r5, 1
    beqlr
bytes:
    lbz     r0, 0(r4)
    cmpwi   r5, 0
    addi    r4, r4, 1
    subi    r5, r5, 1
    stb     r0, 0(r9)
    addi    r9, r9, 1
    bne     bytes
    blr
    // clang-format on
}
