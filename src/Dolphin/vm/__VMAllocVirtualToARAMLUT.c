extern unsigned long* g_baseVMtoARAM;

extern void* OSGetArenaLo(void);
extern void OSSetArenaLo(void*);

// Takes 0x8000 bytes from the arena and zeroes them (virtual page -> ARAM address LUT). GCC output, so asm.
asm void __VMAllocVirtualToARAMLUT(void)
{
    // clang-format off
    nofralloc
    stwu    r1, -0x10(r1)
    mflr    r0
    stw     r0, 0x14(r1)
    bl      OSGetArenaLo
    mr      r4, r3
    addis   r3, r4, 1
    stw     r4, g_baseVMtoARAM
    addi    r3, r3, -0x8000
    bl      OSSetArenaLo
    li      r0, 0x400
    li      r5, 0
    li      r4, 0
    mtctr   r0
L_loop:
    lwz     r3, g_baseVMtoARAM
    stwx    r4, r3, r5
    addi    r5, r5, 4
    lwz     r3, g_baseVMtoARAM
    stwx    r4, r3, r5
    addi    r5, r5, 4
    lwz     r3, g_baseVMtoARAM
    stwx    r4, r3, r5
    addi    r5, r5, 4
    lwz     r3, g_baseVMtoARAM
    stwx    r4, r3, r5
    addi    r5, r5, 4
    lwz     r3, g_baseVMtoARAM
    stwx    r4, r3, r5
    addi    r5, r5, 4
    lwz     r3, g_baseVMtoARAM
    stwx    r4, r3, r5
    addi    r5, r5, 4
    lwz     r3, g_baseVMtoARAM
    stwx    r4, r3, r5
    addi    r5, r5, 4
    lwz     r3, g_baseVMtoARAM
    stwx    r4, r3, r5
    addi    r5, r5, 4
    bdnz    L_loop
    lwz     r0, 0x14(r1)
    mtlr    r0
    addi    r1, r1, 0x10
    blr
    // clang-format on
}
