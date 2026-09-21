extern void OSDisableInterrupts(void);
extern void ICFlashInvalidate(void);
extern void fn_8017E894(void);

asm void __OSDoHotReset(void)
{
    // clang-format off
    nofralloc
    mflr    r0
    stw     r0, 4(r1)
    stwu    r1, -0x18(r1)
    stw     r31, 0x14(r1)
    mr      r31, r3
    bl      OSDisableInterrupts
    lis     r3, 0xCC00
    addi    r3, r3, 0x2000
    li      r0, 0
    sth     r0, 2(r3)
    bl      ICFlashInvalidate
    slwi    r3, r31, 3
    bl      fn_8017E894
    lwz     r0, 0x1c(r1)
    lwz     r31, 0x14(r1)
    addi    r1, r1, 0x18
    mtlr    r0
    blr
    // clang-format on
}
