extern unsigned long* lbl_8066F970;

extern void* OSGetArenaLo(void);
extern void OSSetArenaLo(void*);

// Takes 0x4000 bytes from the arena and zeroes them (ARAM page -> virtual address LUT). GCC output, so asm.
asm void __VMAllocARAMToVirtualLUT(void)
{
    // clang-format off
    nofralloc
    stwu    r1, -0x10(r1)
    mflr    r0
    stw     r0, 0x14(r1)
    bl      OSGetArenaLo
    stw     r3, lbl_8066F970
    addi    r3, r3, 0x4000
    bl      OSSetArenaLo
    li      r0, 0x200
    li      r5, 0
    li      r4, 0
    mtctr   r0
L_loop:
    lwz     r3, lbl_8066F970
    stwx    r4, r3, r5
    addi    r5, r5, 4
    lwz     r3, lbl_8066F970
    stwx    r4, r3, r5
    addi    r5, r5, 4
    lwz     r3, lbl_8066F970
    stwx    r4, r3, r5
    addi    r5, r5, 4
    lwz     r3, lbl_8066F970
    stwx    r4, r3, r5
    addi    r5, r5, 4
    lwz     r3, lbl_8066F970
    stwx    r4, r3, r5
    addi    r5, r5, 4
    lwz     r3, lbl_8066F970
    stwx    r4, r3, r5
    addi    r5, r5, 4
    lwz     r3, lbl_8066F970
    stwx    r4, r3, r5
    addi    r5, r5, 4
    lwz     r3, lbl_8066F970
    stwx    r4, r3, r5
    addi    r5, r5, 4
    bdnz    L_loop
    lwz     r0, 0x14(r1)
    mtlr    r0
    addi    r1, r1, 0x10
    blr
    // clang-format on
}
