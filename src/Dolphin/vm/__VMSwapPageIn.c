extern unsigned long lbl_8066F94C;
extern unsigned long lbl_8066F958;

extern long long OSGetTime(void);
extern int OSDisableInterrupts(void);
extern void OSRestoreInterrupts(int level);
extern void DCFlushRange(void* addr, unsigned long nBytes);
extern void DCInvalidateRange(void* addr, unsigned long nBytes);
extern unsigned long ARGetDMAStatus(void);
extern void ARStartDMA(unsigned long type, unsigned long mainmem, unsigned long aram, unsigned long length);
extern unsigned short __ARGetInterruptStatus(void);
extern void __ARClearInterrupt(void);
extern unsigned long __VMGetPageToReplace(void);
extern unsigned long VMBASEGetVirtualAddrFromPageInMRAM(unsigned long page);
extern unsigned long VMBASEIsPageDirty(unsigned long addr);
extern void VMBASEClearPageTableEntry(unsigned long addr, unsigned long page);
extern void VMBASESetPageTableEntry(unsigned long addr, unsigned long real, unsigned long page);
extern void __VMSetARAMPageAsDirty(unsigned long addr);
extern unsigned long __VMIsARAMPageDirty(unsigned long addr);
extern unsigned long __VMTranslateVMPageToARAMPage(unsigned long addr);
extern unsigned long __VMDoesMappingExist(unsigned long addr);
extern void __VMMappingErrorAlert(unsigned long addr);
void _savegpr_23(void);
void _restgpr_23(void);
void __div2i(void);

// VMBASE's swap-page callback (installed by VMInit): picks a victim page, writes it back to ARAM if
// dirty, pulls the faulting page in, and reports the elapsed microseconds to the log-stats callback
// (lbl_8066F958). GCC output, so asm.
asm void __VMSwapPageIn(unsigned long addr)
{
    // clang-format off
    nofralloc
    stwu    r1, -0x30(r1)
    mflr    r0
    stw     r0, 0x34(r1)
    addi    r11, r1, 0x30
    bl      _savegpr_23
    mr      r27, r3
    bl      OSGetTime
    lis     r6, 0x8000
    lis     r5, 0x431c
    lwz     r0, 0xf8(r6)
    slwi    r3, r3, 3
    rlwimi  r3, r4, 3, 29, 31
    subi    r5, r5, 0x217d
    srwi    r0, r0, 2
    slwi    r4, r4, 3
    mulhwu  r0, r5, r0
    li      r5, 0x0
    srwi    r6, r0, 15
    bl      __div2i
    mr      r31, r4
    clrrwi  r26, r27, 12
    li      r29, 0x0
    bl      __VMGetPageToReplace
    lwz     r4, lbl_8066F94C
    slwi    r0, r3, 12
    mr      r28, r3
    add     r30, r4, r0
    bl      VMBASEGetVirtualAddrFromPageInMRAM
    mr      r23, r3
    bl      OSDisableInterrupts
    mr      r24, r3
L_80400B78:
    bl      ARGetDMAStatus
    cmplwi  r3, 0x0
    bne     L_80400B78
    bl      __ARGetInterruptStatus
    cmplwi  r23, 0x0
    clrlwi  r25, r3, 16
    beq     L_80400BF0
    mr      r3, r23
    bl      VMBASEIsPageDirty
    cmpwi   r3, 0x0
    beq     L_80400BE4
    mr      r3, r23
    bl      __VMSetARAMPageAsDirty
    mr      r3, r30
    li      r29, 0x1
    li      r4, 0x1000
    bl      DCFlushRange
    mr      r3, r23
    bl      __VMTranslateVMPageToARAMPage
    mr      r5, r3
    mr      r4, r30
    li      r3, 0x0
    li      r6, 0x1000
    bl      ARStartDMA
L_80400BD8:
    bl      ARGetDMAStatus
    cmplwi  r3, 0x0
    bne     L_80400BD8
L_80400BE4:
    mr      r3, r23
    mr      r4, r28
    bl      VMBASEClearPageTableEntry
L_80400BF0:
    mr      r3, r30
    li      r4, 0x1000
    bl      DCInvalidateRange
    mr      r3, r26
    bl      __VMIsARAMPageDirty
    cmpwi   r3, 0x0
    beq     L_80400C38
    mr      r3, r26
    bl      __VMTranslateVMPageToARAMPage
    mr      r5, r3
    mr      r4, r30
    li      r3, 0x1
    li      r6, 0x1000
    bl      ARStartDMA
L_80400C28:
    bl      ARGetDMAStatus
    cmplwi  r3, 0x0
    bne     L_80400C28
    b       L_80400C50
L_80400C38:
    mr      r3, r26
    bl      __VMDoesMappingExist
    cmpwi   r3, 0x0
    bne     L_80400C50
    mr      r3, r26
    bl      __VMMappingErrorAlert
L_80400C50:
    cmpwi   r25, 0x0
    bne     L_80400C5C
    bl      __ARClearInterrupt
L_80400C5C:
    mr      r3, r26
    mr      r4, r30
    mr      r5, r28
    bl      VMBASESetPageTableEntry
    mr      r3, r24
    bl      OSRestoreInterrupts
    lwz     r0, lbl_8066F958
    cmplwi  r0, 0x0
    beq     L_80400CD4
    bl      OSGetTime
    lis     r6, 0x8000
    lis     r5, 0x431c
    lwz     r0, 0xf8(r6)
    slwi    r3, r3, 3
    rlwimi  r3, r4, 3, 29, 31
    subi    r5, r5, 0x217d
    srwi    r0, r0, 2
    slwi    r4, r4, 3
    mulhwu  r0, r5, r0
    li      r5, 0x0
    srwi    r6, r0, 15
    bl      __div2i
    lwz     r12, lbl_8066F958
    subf    r6, r31, r4
    mr      r3, r27
    mr      r4, r30
    mr      r5, r28
    mr      r7, r29
    mtctr   r12
    bctrl
L_80400CD4:
    addi    r11, r1, 0x30
    bl      _restgpr_23
    lwz     r0, 0x34(r1)
    mtlr    r0
    addi    r1, r1, 0x30
    blr
    // clang-format on
}
