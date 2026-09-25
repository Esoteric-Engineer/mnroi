extern void fn_80168770(void);

asm void fn_801694DC(void)
{
    // clang-format off
    nofralloc
    addi    r3, r31, 0x708
    mr      r28, r5
    mflr    r29
    bl      fn_80168770
    mr      r4, r28
    addi    r3, r31, 0x700
    li      r6, 0xd
    stb     r6, 0(r3)
    li      r6, 2
    sthbrx  r4, r6, r3
    addi    r4, r4, 8
    lwz     r0, 0x6A4(r31)
    mtlr    r0
    blrl
    mtlr    r29
    blr
    // clang-format on
}
