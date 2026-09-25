// Invalidates the whole TLB: 8 passes of 8 tlbie, stepping one 4 KiB page each. GCC output, so asm.
asm void __VMBASEInvalidateEntireTLB(void)
{
    // clang-format off
    nofralloc
    li      r3, 0
    tlbsync
    li      r0, 8
    mtctr   r0
loop:
    tlbie   r3
    addi    r3, r3, 0x1000
    tlbie   r3
    addi    r3, r3, 0x1000
    tlbie   r3
    addi    r3, r3, 0x1000
    tlbie   r3
    addi    r3, r3, 0x1000
    tlbie   r3
    addi    r3, r3, 0x1000
    tlbie   r3
    addi    r3, r3, 0x1000
    tlbie   r3
    addi    r3, r3, 0x1000
    tlbie   r3
    addi    r3, r3, 0x1000
    bdnz    loop
    blr
    // clang-format on
}
