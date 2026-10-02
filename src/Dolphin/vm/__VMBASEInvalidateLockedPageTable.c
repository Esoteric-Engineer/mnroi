extern unsigned char* lbl_8066F988;

// Zeroes the 0x1000-byte locked-page table. GCC output (loop unrolled 8x), so asm.
asm void __VMBASEInvalidateLockedPageTable(void)
{
    // clang-format off
    nofralloc
    li      r0, 0x100
    li      r5, 0
    mtctr   r0
L_loop:
    lwz     r3, lbl_8066F988
    li      r4, 0
    stbx    r4, r3, r5
    lwz     r0, lbl_8066F988
    add     r3, r5, r0
    stb     r4, 1(r3)
    lwz     r0, lbl_8066F988
    add     r3, r5, r0
    stb     r4, 2(r3)
    lwz     r0, lbl_8066F988
    add     r3, r5, r0
    stb     r4, 3(r3)
    lwz     r0, lbl_8066F988
    add     r3, r5, r0
    stb     r4, 4(r3)
    lwz     r0, lbl_8066F988
    add     r3, r5, r0
    stb     r4, 5(r3)
    lwz     r0, lbl_8066F988
    add     r3, r5, r0
    stb     r4, 6(r3)
    lwz     r0, lbl_8066F988
    add     r3, r5, r0
    addi    r5, r5, 8
    stb     r4, 7(r3)
    lwz     r3, lbl_8066F988
    stbx    r4, r3, r5
    lwz     r0, lbl_8066F988
    add     r3, r5, r0
    stb     r4, 1(r3)
    lwz     r0, lbl_8066F988
    add     r3, r5, r0
    stb     r4, 2(r3)
    lwz     r0, lbl_8066F988
    add     r3, r5, r0
    stb     r4, 3(r3)
    lwz     r0, lbl_8066F988
    add     r3, r5, r0
    stb     r4, 4(r3)
    lwz     r0, lbl_8066F988
    add     r3, r5, r0
    stb     r4, 5(r3)
    lwz     r0, lbl_8066F988
    add     r3, r5, r0
    stb     r4, 6(r3)
    lwz     r0, lbl_8066F988
    add     r3, r5, r0
    addi    r5, r5, 8
    stb     r4, 7(r3)
    bdnz    L_loop
    blr
    // clang-format on
}
