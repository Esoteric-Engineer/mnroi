/*
 * Transliterated from asm, not reconstructed C. This isn't the __fill_mem-based memset from ac-decomp's __mem.c.
 * Plain C at -O4,p unrolls the loops into mtctr forms (~0%), and optimization_level 1/2 only reaches ~55%.
 */
asm void* memset(void* dst, int val, unsigned long n)
{
    // clang-format off
    nofralloc
    mr      r9, r3
    cmplwi  r5, 3
    ble     tail
    andi.   r0, r3, 3
    bne     tail
    clrlwi  r4, r4, 24
    mr      r11, r3
    slwi    r0, r4, 8
    or      r0, r0, r4
    slwi    r9, r0, 16
    or      r0, r0, r9
    cmplwi  r5, 15
    ble     words
loop16:
    stw     r0, 0(r11)
    subi    r5, r5, 16
    stwu    r0, 4(r11)
    cmplwi  r5, 15
    stwu    r0, 4(r11)
    stwu    r0, 4(r11)
    addi    r11, r11, 4
    bgt     loop16
    b       words
loop4:
    stw     r0, 0(r11)
    subi    r5, r5, 4
    addi    r11, r11, 4
words:
    cmplwi  r5, 3
    bgt     loop4
    mr      r9, r11
tail:
    cmpwi   r5, 0
    subi    r5, r5, 1
    beqlr
loop1:
    stb     r4, 0(r9)
    cmpwi   r5, 0
    addi    r9, r9, 1
    subi    r5, r5, 1
    bne     loop1
    blr
    // clang-format on
}
