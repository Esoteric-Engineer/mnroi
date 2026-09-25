void fn_8016BEE4(void);
void fn_8016BF04(void);

asm void fn_8016BFB0(void)
{
    // clang-format off
    nofralloc
    stwu    r1, -8(r1)
    mflr    r0
    stw     r0, 0xC(r1)
    bl      fn_8016BEE4
    lis     r9, 0xCC00
    li      r0, 0
    ori     r9, r9, 0x6008
    lis     r11, 0xCC00
    stw     r0, 0(r9)
    ori     r11, r11, 0x601C
    li      r0, 1
    stw     r0, 0(r11)
    bl      fn_8016BF04
    lwz     r0, 0xC(r1)
    mtlr    r0
    addi    r1, r1, 8
    blr
    // clang-format on
}
