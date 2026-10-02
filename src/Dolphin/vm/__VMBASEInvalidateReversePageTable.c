extern unsigned long* lbl_8066F984;

// Zeroes the 0x4000-byte reverse page table. GCC output (loop unrolled 8x), so asm.
asm void __VMBASEInvalidateReversePageTable(void)
{
    // clang-format off
    nofralloc
    li      r0, 0x200
    li      r5, 0
    li      r4, 0
    mtctr   r0
L_loop:
    lwz     r3, lbl_8066F984
    stwx    r4, r3, r5
    addi    r5, r5, 4
    lwz     r3, lbl_8066F984
    stwx    r4, r3, r5
    addi    r5, r5, 4
    lwz     r3, lbl_8066F984
    stwx    r4, r3, r5
    addi    r5, r5, 4
    lwz     r3, lbl_8066F984
    stwx    r4, r3, r5
    addi    r5, r5, 4
    lwz     r3, lbl_8066F984
    stwx    r4, r3, r5
    addi    r5, r5, 4
    lwz     r3, lbl_8066F984
    stwx    r4, r3, r5
    addi    r5, r5, 4
    lwz     r3, lbl_8066F984
    stwx    r4, r3, r5
    addi    r5, r5, 4
    lwz     r3, lbl_8066F984
    stwx    r4, r3, r5
    addi    r5, r5, 4
    bdnz    L_loop
    blr
    // clang-format on
}
