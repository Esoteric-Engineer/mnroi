unsigned long* g_baseARAMtoVM = 0;
unsigned long* g_baseVMtoARAM = 0;
static unsigned long g_totalAllocatedVM;
static unsigned long g_nextARAMPageToCheck;

extern unsigned long VMGetARAMBase(void);
extern unsigned long VMGetARAMSize(void);

// Maps size bytes at addr onto free ARAM pages; 0 if over budget. GCC output, so asm.
asm int VMAlloc(unsigned long addr, unsigned long size)
{
    // clang-format off
    nofralloc
    stwu    r1, -0x20(r1)
    mflr    r0
    stw     r0, 0x24(r1)
    stw     r31, 0x1c(r1)
    stw     r30, 0x18(r1)
    stw     r29, 0x14(r1)
    mr      r29, r3
    stw     r28, 0x10(r1)
    mr      r28, r4
    bl      VMGetARAMBase
    srwi    r31, r3, 12
    bl      VMGetARAMSize
    lwz     r0, g_nextARAMPageToCheck
    srwi    r3, r3, 12
    add     r30, r31, r3
    cmplw   r0, r31
    bge     L_skip
    stw     r31, g_nextARAMPageToCheck
L_skip:
    bl      VMGetARAMSize
    lwz     r0, g_totalAllocatedVM
    add     r0, r0, r28
    cmplw   r0, r3
    ble     L_ok
    li      r3, 0
    b       L_end
L_ok:
    addi    r0, r28, 0xfff
    li      r5, 0
    srwi    r0, r0, 12
    mtctr   r0
    cmplwi  r28, 0
    ble     L_done
L_outer:
    add     r6, r29, r5
    lwz     r4, g_baseARAMtoVM
L_inner:
    lwz     r3, g_nextARAMPageToCheck
    addi    r0, r3, 1
    cmplw   r0, r30
    stw     r0, g_nextARAMPageToCheck
    blt     L_nowrap
    stw     r31, g_nextARAMPageToCheck
L_nowrap:
    lwz     r0, g_nextARAMPageToCheck
    slwi    r3, r0, 2
    lwzx    r0, r4, r3
    cmplwi  r0, 0
    bne     L_inner
    stwx    r6, r4, r3
    rlwinm  r0, r6, 22, 17, 29
    addi    r5, r5, 0x1000
    lwz     r4, g_nextARAMPageToCheck
    lwz     r3, g_baseVMtoARAM
    slwi    r4, r4, 12
    stwx    r4, r3, r0
    lwz     r3, g_totalAllocatedVM
    addi    r0, r3, 0x1000
    stw     r0, g_totalAllocatedVM
    bdnz    L_outer
L_done:
    li      r3, 1
L_end:
    lwz     r0, 0x24(r1)
    lwz     r31, 0x1c(r1)
    lwz     r30, 0x18(r1)
    lwz     r29, 0x14(r1)
    lwz     r28, 0x10(r1)
    mtlr    r0
    addi    r1, r1, 0x20
    blr
    // clang-format on
}
