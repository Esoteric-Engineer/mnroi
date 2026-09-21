asm unsigned long strspn(const char* str, const char* set)
{
    // clang-format off
    nofralloc
    lbz     r11, 0(r3)
    mr      r8, r3
    cmpwi   r11, 0
    beq     done
outer:
    mr      r10, r4
    lbz     r0, 0(r10)
    extsb   r9, r0
    cmpwi   r9, 0
    beq     done
    extsb   r0, r11
    cmpw    r0, r9
    beq     found
inner:
    lbzu    r0, 1(r10)
    extsb   r9, r0
    cmpwi   r9, 0
    beq     done
    lbz     r0, 0(r3)
    extsb   r0, r0
    cmpw    r0, r9
    bne     inner
found:
    lbz     r0, 0(r10)
    cmpwi   r0, 0
    beq     done
    lbzu    r11, 1(r3)
    cmpwi   r11, 0
    bne     outer
done:
    subf    r3, r8, r3
    blr
    // clang-format on
}
