extern unsigned long* lbl_8066F984;
extern void OSGetArenaLo(void);
extern void OSSetArenaLo(void);
extern void fn_8040186C(void);

// Reserves 0x4000 bytes of arena for the reverse page table, then runs its setup. GCC output, so asm.
asm void __VMBASEInitReversePageTable(void)
{
    // clang-format off
    nofralloc
    stwu    r1, -0x10(r1)
    mflr    r0
    stw     r0, 0x14(r1)
    bl      OSGetArenaLo
    stw     r3, lbl_8066F984
    addi    r3, r3, 0x4000
    bl      OSSetArenaLo
    bl      fn_8040186C
    lwz     r0, 0x14(r1)
    mtlr    r0
    addi    r1, r1, 0x10
    blr
    // clang-format on
}
