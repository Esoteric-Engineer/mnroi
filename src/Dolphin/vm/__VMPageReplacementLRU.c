extern unsigned long lbl_8066F968;
extern unsigned long lbl_8066CEA0;

extern unsigned long __VMGetNumPagesInMRAM(void);
extern unsigned long VMBASEGetVirtualAddrFromPageInMRAM(unsigned long page);
extern unsigned long VMBASEIsPageLocked(unsigned long page);
extern unsigned long VMBASEIsPageValid(unsigned long addr);
extern unsigned long VMBASEIsPageReferenced(unsigned long addr);
extern unsigned long VMBASEIsPageDirty(unsigned long addr);
extern void fn_80401500(unsigned long addr, unsigned long set);
void _savegpr_24(void);
void _restgpr_24(void);

// Scans the wrapping page cursor for the best replacement victim, ranked by the referenced and
// dirty bits: (R=0,C=0) wins outright, then (R=0,C=1), (R=1,C=0), (R=1,C=1); the R bit is cleared
// as it goes. GCC output, so asm.
asm unsigned long __VMPageReplacementLRU(void)
{
    // clang-format off
    nofralloc
    stwu    r1, -0x30(r1)
    mflr    r0
    stw     r0, 0x34(r1)
    addi    r11, r1, 0x30
    bl      _savegpr_24
    lwz     r0, lbl_8066CEA0
    li      r28, 0
    lwz     r29, lbl_8066F968
    li      r27, -1
    cmpwi   r0, 0
    li      r26, -1
    li      r25, -1
    bne     L_80400EB8
L_80400D64:
    lwz     r3, lbl_8066F968
    bl      VMBASEGetVirtualAddrFromPageInMRAM
    mr.     r24, r3
    beq     L_80400EB0
    bl      VMBASEIsPageValid
    cmpwi   r3, 0
    beq     L_80400EB0
    mr      r3, r24
    bl      VMBASEIsPageReferenced
    mr      r30, r3
    mr      r3, r24
    bl      VMBASEIsPageDirty
    cmpwi   r30, 0
    mr      r31, r3
    bne     L_80400DC0
    cmpwi   r31, 0
    bne     L_80400DC0
    lwz     r3, lbl_8066F968
    bl      VMBASEIsPageLocked
    cmpwi   r3, 0
    bne     L_80400DC0
    lwz     r28, lbl_8066F968
    b       L_80400EBC
L_80400DC0:
    cmpwi   r30, 0
    bne     L_80400DF0
    cmpwi   r31, 0
    beq     L_80400DF0
    cmpwi   r27, 0
    bge     L_80400E3C
    lwz     r3, lbl_8066F968
    bl      VMBASEIsPageLocked
    cmpwi   r3, 0
    bne     L_80400E3C
    lwz     r27, lbl_8066F968
    b       L_80400E3C
L_80400DF0:
    cmpwi   r30, 0
    beq     L_80400E20
    cmpwi   r31, 0
    bne     L_80400E20
    cmpwi   r26, 0
    bge     L_80400E3C
    lwz     r3, lbl_8066F968
    bl      VMBASEIsPageLocked
    cmpwi   r3, 0
    bne     L_80400E3C
    lwz     r26, lbl_8066F968
    b       L_80400E3C
L_80400E20:
    cmpwi   r25, 0
    bge     L_80400E3C
    lwz     r3, lbl_8066F968
    bl      VMBASEIsPageLocked
    cmpwi   r3, 0
    bne     L_80400E3C
    lwz     r25, lbl_8066F968
L_80400E3C:
    cmpwi   r30, 0
    beq     L_80400E50
    mr      r3, r24
    li      r4, 0
    bl      fn_80401500
L_80400E50:
    lwz     r3, lbl_8066F968
    cmplw   r29, r3
    bne     L_80400E8C
    cmpwi   r27, 0
    blt     L_80400E6C
    mr      r28, r27
    b       L_80400EBC
L_80400E6C:
    cmpwi   r26, 0
    blt     L_80400E7C
    mr      r28, r26
    b       L_80400EBC
L_80400E7C:
    cmpwi   r25, 0
    blt     L_80400EBC
    mr      r28, r25
    b       L_80400EBC
L_80400E8C:
    addi    r0, r3, 1
    stw     r0, lbl_8066F968
    bl      __VMGetNumPagesInMRAM
    lwz     r0, lbl_8066F968
    cmplw   r0, r3
    blt     L_80400D64
    li      r0, 0
    stw     r0, lbl_8066F968
    b       L_80400D64
L_80400EB0:
    lwz     r28, lbl_8066F968
    b       L_80400EBC
L_80400EB8:
    mr      r28, r29
L_80400EBC:
    lwz     r3, lbl_8066F968
    addi    r0, r3, 1
    stw     r0, lbl_8066F968
    bl      __VMGetNumPagesInMRAM
    lwz     r0, lbl_8066F968
    cmplw   r0, r3
    blt     L_80400EE4
    li      r0, 0
    stw     r0, lbl_8066CEA0
    stw     r0, lbl_8066F968
L_80400EE4:
    mr      r3, r28
    addi    r11, r1, 0x30
    bl      _restgpr_24
    lwz     r0, 0x34(r1)
    mtlr    r0
    addi    r1, r1, 0x30
    blr
    // clang-format on
}
