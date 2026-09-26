extern unsigned char* lbl_8066F988;
extern void OSGetArenaLo(void);
extern void OSSetArenaLo(void);
extern void __VMBASEInvalidateLockedPageTable(void);

// Reserves 0x1000 bytes of arena for the locked-page table, then runs its setup. GCC output, so asm.
asm void __VMBASEInitLockedPageTable(void)
{
    // clang-format off
    nofralloc
    stwu    r1, -0x10(r1)
    mflr    r0
    stw     r0, 0x14(r1)
    bl      OSGetArenaLo
    stw     r3, lbl_8066F988
    addi    r3, r3, 0x1000
    bl      OSSetArenaLo
    bl      __VMBASEInvalidateLockedPageTable
    lwz     r0, 0x14(r1)
    mtlr    r0
    addi    r1, r1, 0x10
    blr
    // clang-format on
}
