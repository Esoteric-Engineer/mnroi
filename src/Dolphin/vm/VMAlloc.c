extern unsigned long* lbl_8066F970;
extern unsigned long* lbl_8066F974;
extern unsigned long lbl_8066F978;
extern unsigned long lbl_8066F97C;

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
    lwz     r0, lbl_8066F97C
    srwi    r3, r3, 12
    add     r30, r31, r3
    cmplw   r0, r31
    bge     L_skip
    stw     r31, lbl_8066F97C
L_skip:
    bl      VMGetARAMSize
    lwz     r0, lbl_8066F978
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
    lwz     r4, lbl_8066F970
L_inner:
    lwz     r3, lbl_8066F97C
    addi    r0, r3, 1
    cmplw   r0, r30
    stw     r0, lbl_8066F97C
    blt     L_nowrap
    stw     r31, lbl_8066F97C
L_nowrap:
    lwz     r0, lbl_8066F97C
    slwi    r3, r0, 2
    lwzx    r0, r4, r3
    cmplwi  r0, 0
    bne     L_inner
    stwx    r6, r4, r3
    rlwinm  r0, r6, 22, 17, 29
    addi    r5, r5, 0x1000
    lwz     r4, lbl_8066F97C
    lwz     r3, lbl_8066F974
    slwi    r4, r4, 12
    stwx    r4, r3, r0
    lwz     r3, lbl_8066F978
    addi    r0, r3, 0x1000
    stw     r0, lbl_8066F978
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
