extern unsigned long lbl_8066F948;
extern unsigned long lbl_8066F94C;

extern unsigned long OSGetArenaLo(void);
extern void OSSetArenaLo(unsigned long addr);

// Reserves lbl_8066F948 bytes of MRAM swap space from the arena low end. GCC output, so asm.
asm void __VMAllocMRAMSwapSpace(void)
{
    // clang-format off
    nofralloc
    stwu    r1, -0x10(r1)
    mflr    r0
    stw     r0, 0x14(r1)
    bl      OSGetArenaLo
    lwz     r0, lbl_8066F948
    stw     r3, lbl_8066F94C
    add     r3, r3, r0
    bl      OSSetArenaLo
    lwz     r0, 0x14(r1)
    mtlr    r0
    addi    r1, r1, 0x10
    blr
    // clang-format on
}
