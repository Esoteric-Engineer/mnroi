asm char* __sccl(char* tab, char* fmt)
{
    // clang-format off
    nofralloc
    lbz     r0, 0(r4)
    addi    r4, r4, 1
    extsb   r11, r0
    cmpwi   r11, 0x5e
    bne     notneg
    lbz     r0, 0(r4)
    li      r10, 1
    addi    r4, r4, 1
    extsb   r11, r0
    b       clear
notneg:
    li      r10, 0
clear:
    li      r0, 0x100
    cmpwi   r11, 0
    mtctr   r0
    addi    r9, r3, 0xff
cloop:
    stb     r10, 0(r9)
    subi    r9, r9, 1
    bdnz    cloop
    bne     scan
ret_fmt1:
    subi    r3, r4, 1
    blr
scan:
    subfic  r10, r10, 1
store:
    stbx    r10, r3, r11
next:
    lbz     r0, 0(r4)
    addi    r4, r4, 1
    extsb   r0, r0
    cmpwi   r0, 0x2d
    beq     dash
    bgt     above
    cmpwi   r0, 0
    beq     ret_fmt1
    b       other
above:
    cmpwi   r0, 0x5d
    beq     close
    b       other
dash:
    lbz     r0, 0(r4)
    extsb   r0, r0
    cmpwi   r0, 0x5d
    beq     lit
    cmpw    r0, r11
    bge     range
lit:
    li      r11, 0x2d
    b       store
range:
    addi    r4, r4, 1
rloop:
    addi    r11, r11, 1
    stbx    r10, r3, r11
    cmpw    r11, r0
    blt     rloop
    b       next
close:
    mr      r3, r4
    blr
other:
    mr      r11, r0
    b       store
    // clang-format on
}
