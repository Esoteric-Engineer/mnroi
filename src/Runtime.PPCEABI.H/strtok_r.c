asm char* strtok_r(char* str, const char* delim, char** save)
{
    // clang-format off
    nofralloc
    mr.     r3, r3
    bne     start
    lwz     r3, 0(r5)
    cmpwi   r3, 0
    bne     start
    li      r3, 0
    blr
start:
    lbz     r0, 0(r3)
    mr      r11, r4
    lbz     r9, 0(r11)
    addi    r3, r3, 1
    extsb   r10, r0
    addi    r11, r11, 1
    extsb   r0, r9
    cmpwi   r0, 0
    beq     skipdone
skipscan:
    cmpw    r10, r0
    beq     start
    lbz     r0, 0(r11)
    addi    r11, r11, 1
    extsb   r0, r0
    cmpwi   r0, 0
    bne     skipscan
skipdone:
    cmpwi   r10, 0
    bne     tokstart
    stw     r10, 0(r5)
    li      r3, 0
    blr
tokstart:
    subi    r8, r3, 1
tokloop:
    lbz     r0, 0(r3)
    mr      r11, r4
    addi    r3, r3, 1
    li      r9, 0
    extsb   r10, r0
delimscan:
    lbz     r0, 0(r11)
    addi    r11, r11, 1
    extsb   r0, r0
    cmpw    r0, r10
    bne     nomatch
    cmpwi   r0, 0
    bne     terminate
    li      r3, 0
    b       store
terminate:
    stb     r9, -1(r3)
store:
    stw     r3, 0(r5)
    mr      r3, r8
    blr
nomatch:
    cmpwi   r0, 0
    bne     delimscan
    b       tokloop
    // clang-format on
}
