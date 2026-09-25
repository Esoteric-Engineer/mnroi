void fn_8016BEE4(void);
void fn_8016BF04(void);

asm void fn_8016BF28(int arg)
{
    // clang-format off
    nofralloc
    stwu    r1, -0x10(r1)
    mflr    r0
    stmw    r30, 8(r1)
    stw     r0, 0x14(r1)
    mr      r30, r3
    bl      fn_8016BEE4
    lis     r9, 0xcc00
    lis     r0, 0x1200
    ori     r9, r9, 0x6008
    lis     r11, 0xcc00
    stw     r0, 0(r9)
    ori     r11, r11, 0x600c
    li      r0, 0
    lis     r10, 0xcc00
    stw     r0, 0(r11)
    li      r8, 0x20
    ori     r10, r10, 0x6010
    lis     r9, 0xcc00
    stw     r8, 0(r10)
    ori     r9, r9, 0x6018
    stw     r8, 0(r9)
    lis     r11, 0xcc00
    ori     r11, r11, 0x6014
    lis     r9, 0xcc00
    stw     r30, 0(r11)
    ori     r9, r9, 0x601c
    li      r0, 3
    stw     r0, 0(r9)
    bl      fn_8016BF04
    lwz     r0, 0x14(r1)
    mtlr    r0
    lmw     r30, 8(r1)
    addi    r1, r1, 0x10
    blr
    // clang-format on
}
