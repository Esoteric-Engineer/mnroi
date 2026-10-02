asm void strrev(char* s)
{
    // clang-format off
    nofralloc
    li      r11, 0
    b       check
inc:
    addi    r11, r11, 1
check:
    lbzx    r0, r3, r11
    cmpwi   r0, 0
    bne     inc
    li      r10, 0
    subi    r11, r11, 1
    cmpw    r10, r11
    bgelr
swap:
    lbzx    r0, r3, r11
    lbzx    r9, r3, r10
    stbx    r0, r3, r10
    stbx    r9, r3, r11
    addi    r10, r10, 1
    subi    r11, r11, 1
    cmpw    r10, r11
    blt     swap
    blr
    // clang-format on
}
