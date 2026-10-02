void __OSMaskInterrupts(void);
void __OSSetInterruptHandler(void);
void __OSUnmaskInterrupts(void);
void SNHandler(void);

asm void SNInitInterrupts(void)
{
    // clang-format off
    nofralloc
    mflr    r0
    stw     r0, 0x4(r1)
    stwu    r1, -0x8(r1)
    lis     r3, 0x1
    ori     r3, r3, 0x8000
    bl      __OSMaskInterrupts
    li      r3, 0x40
    bl      __OSMaskInterrupts
    lis     r4, SNHandler@h
    ori     r4, r4, SNHandler@l
    li      r3, 0x19
    bl      __OSSetInterruptHandler
    li      r3, 0x40
    bl      __OSUnmaskInterrupts
    lwz     r0, 0xc(r1)
    addi    r1, r1, 0x8
    mtlr    r0
    blr
    // clang-format on
}
