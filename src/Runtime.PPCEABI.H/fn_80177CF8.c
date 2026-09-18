asm void fn_80177CF8(unsigned char* dst, unsigned char* src, int n)
{
    // clang-format off
    nofralloc
    addi   r9, r5, -1
    cmpwi  r5, 0
    beqlr
loop:
    lbz    r0, 0(r4)
    cmpwi  r9, 0
    addi   r4, r4, 1
    addi   r9, r9, -1
    stb    r0, 0(r3)
    addi   r3, r3, 1
    bne    loop
    blr
    // clang-format on
}
