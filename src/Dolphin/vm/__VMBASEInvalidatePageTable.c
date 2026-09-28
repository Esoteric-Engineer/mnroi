extern unsigned long* lbl_8066F980;
extern void DCStoreRange(void* addr, unsigned long nBytes);

// Zeroes the 0x10000-byte page table, then flushes it. GCC output (loop unrolled 8x), so asm.
asm void __VMBASEInvalidatePageTable(void)
{
    // clang-format off
    nofralloc
    stwu    r1, -0x10(r1)
    mflr    r0
    lis     r3, 0x1
    li      r6, 0x0
    cmplwi  r3, 0x0
    stw     r0, 0x14(r1)
    addi    r3, r3, 0x7
    li      r5, 0x0
    srwi    r3, r3, 3
    ble     L_80401778
    srwi.   r0, r3, 3
    mtctr   r0
    beq     L_80401758
L_8040168C:
    lwz     r4, lbl_8066F980
    addi    r0, r6, 0x4
    stwx    r5, r4, r6
    lwz     r4, lbl_8066F980
    stwx    r5, r4, r0
    addi    r0, r6, 0xc
    addi    r6, r6, 0x8
    lwz     r4, lbl_8066F980
    stwx    r5, r4, r6
    lwz     r4, lbl_8066F980
    stwx    r5, r4, r0
    addi    r0, r6, 0xc
    addi    r6, r6, 0x8
    lwz     r4, lbl_8066F980
    stwx    r5, r4, r6
    lwz     r4, lbl_8066F980
    stwx    r5, r4, r0
    addi    r0, r6, 0xc
    addi    r6, r6, 0x8
    lwz     r4, lbl_8066F980
    stwx    r5, r4, r6
    lwz     r4, lbl_8066F980
    stwx    r5, r4, r0
    addi    r0, r6, 0xc
    addi    r6, r6, 0x8
    lwz     r4, lbl_8066F980
    stwx    r5, r4, r6
    lwz     r4, lbl_8066F980
    stwx    r5, r4, r0
    addi    r0, r6, 0xc
    addi    r6, r6, 0x8
    lwz     r4, lbl_8066F980
    stwx    r5, r4, r6
    lwz     r4, lbl_8066F980
    stwx    r5, r4, r0
    addi    r0, r6, 0xc
    addi    r6, r6, 0x8
    lwz     r4, lbl_8066F980
    stwx    r5, r4, r6
    lwz     r4, lbl_8066F980
    stwx    r5, r4, r0
    addi    r0, r6, 0xc
    addi    r6, r6, 0x8
    lwz     r4, lbl_8066F980
    stwx    r5, r4, r6
    addi    r6, r6, 0x8
    lwz     r4, lbl_8066F980
    stwx    r5, r4, r0
    bdnz    L_8040168C
    andi.   r3, r3, 0x7
    beq     L_80401778
L_80401758:
    mtctr   r3
L_8040175C:
    lwz     r4, lbl_8066F980
    addi    r0, r6, 0x4
    stwx    r5, r4, r6
    addi    r6, r6, 0x8
    lwz     r4, lbl_8066F980
    stwx    r5, r4, r0
    bdnz    L_8040175C
L_80401778:
    lwz     r3, lbl_8066F980
    lis     r4, 0x1
    bl      DCStoreRange
    lwz     r0, 0x14(r1)
    mtlr    r0
    addi    r1, r1, 0x10
    blr     
    // clang-format on
}
