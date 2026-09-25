void fn_8016BD38(void);
void OSDisableInterrupts(void);
void __OSSetInterruptHandler(void);
void __OSUnmaskInterrupts(void);
void OSRestoreInterrupts(void);

asm void fn_8016BE74(void)
{
    // clang-format off
    nofralloc
    stwu    r1, -0x10(r1)
    mflr    r0
    stmw    r30, 8(r1)
    stw     r0, 0x14(r1)
    bl      OSDisableInterrupts
    mr      r30, r3
    lis     r4, fn_8016BD38@ha
    addi    r4, r4, fn_8016BD38@l
    li      r3, 0x10
    bl      __OSSetInterruptHandler
    li      r3, 0
    ori     r3, r3, 0x8000
    bl      __OSUnmaskInterrupts
    lis     r11, 0xcc00
    mr      r3, r30
    ori     r11, r11, 0x6828
    lwz     r0, 0(r11)
    ori     r0, r0, 8
    stw     r0, 0(r11)
    lwz     r9, 0(r11)
    rlwinm  r9, r9, 0, 30, 28
    stw     r9, 0(r11)
    bl      OSRestoreInterrupts
    lwz     r0, 0x14(r1)
    mtlr    r0
    lmw     r30, 8(r1)
    addi    r1, r1, 0x10
    blr
    // clang-format on
}
