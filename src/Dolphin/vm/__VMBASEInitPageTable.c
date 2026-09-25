extern unsigned char* lbl_8066F980;
extern unsigned long OSGetArenaLo(void);
extern void OSSetArenaLo(void);
extern void fn_80401658(void);

// Aligns the arena low mark up to 0x10000, keeps it as the page table, reserves 0x10000 bytes, then runs its setup. GCC output, so asm.
asm void __VMBASEInitPageTable(void)
{
    // clang-format off
    nofralloc
    stwu    r1, -0x10(r1)
    mflr    r0
    stw     r0, 0x14(r1)
    bl      OSGetArenaLo
    clrlwi  r4, r3, 16
    addis   r0, r3, 0x1
    subf    r3, r4, r0
    stw     r3, lbl_8066F980
    addis   r3, r3, 0x1
    bl      OSSetArenaLo
    bl      fn_80401658
    lwz     r0, 0x14(r1)
    mtlr    r0
    addi    r1, r1, 0x10
    blr
    // clang-format on
}
