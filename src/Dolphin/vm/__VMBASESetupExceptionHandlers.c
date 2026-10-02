extern void __VMBASEDSIExceptionHandler(void);
extern void __VMBASEISIExceptionHandler(void);
extern void lbl_80401C4C(void);
extern void lbl_80401C50(void);
extern void lbl_80401DF4(void);
extern void lbl_80401DF8(void);
extern void DCFlushRangeNoSync(void* addr, unsigned long nBytes);

// Installs the DSI (0x300) and ISI (0x400) vectors: each is replaced by a branch to the VM handler, and the original first word is stashed in the handler's first nop slot, with the second slot patched to branch back to vector+4. Every patched word is DCFlushRangeNoSync'd, sync/isync'd and icbi'd. GCC output, so asm.
asm void __VMBASESetupExceptionHandlers(void)
{
    // clang-format off
    nofralloc
    stwu    r1, -0x10(r1)
    mflr    r0
    lis     r3, __VMBASEDSIExceptionHandler@ha
    lis     r5, 0x8000
    stw     r0, 0x14(r1)
    addi    r3, r3, __VMBASEDSIExceptionHandler@l
    addis   r6, r3, 0x8000
    li      r4, 4
    stw     r31, 0xc(r1)
    subi    r6, r6, 0x300
    oris    r0, r6, 0x4800
    addi    r3, r5, 0x300
    stw     r30, 8(r1)
    lwz     r30, 0x300(r5)
    stw     r0, 0x300(r5)
    bl      DCFlushRangeNoSync
    sync
    lis     r3, 0x8000
    addi    r3, r3, 0x300
    li      r0, 0
    isync
    icbi    r3, r0
    lis     r3, lbl_80401C4C@ha
    li      r4, 4
    addi    r31, r3, lbl_80401C4C@l
    stw     r30, 0(r31)
    mr      r3, r31
    bl      DCFlushRangeNoSync
    sync
    li      r0, 0
    isync
    icbi    r31, r0
    lis     r3, lbl_80401C50@ha
    li      r4, 4
    addi    r31, r3, lbl_80401C50@l
    addis   r5, r31, 0x8000
    subi    r5, r5, 0x304
    mr      r3, r31
    neg     r0, r5
    clrlwi  r0, r0, 6
    oris    r0, r0, 0x4800
    stw     r0, 0(r31)
    bl      DCFlushRangeNoSync
    sync
    li      r0, 0
    isync
    icbi    r31, r0
    lis     r3, __VMBASEISIExceptionHandler@ha
    lis     r5, 0x8000
    addi    r3, r3, __VMBASEISIExceptionHandler@l
    lwz     r30, 0x400(r5)
    addis   r6, r3, 0x8000
    li      r4, 4
    subi    r6, r6, 0x400
    addi    r3, r5, 0x400
    oris    r0, r6, 0x4800
    stw     r0, 0x400(r5)
    bl      DCFlushRangeNoSync
    sync
    lis     r3, 0x8000
    addi    r3, r3, 0x400
    li      r0, 0
    isync
    icbi    r3, r0
    lis     r3, lbl_80401DF4@ha
    li      r4, 4
    addi    r31, r3, lbl_80401DF4@l
    stw     r30, 0(r31)
    mr      r3, r31
    bl      DCFlushRangeNoSync
    sync
    li      r0, 0
    isync
    icbi    r31, r0
    lis     r3, lbl_80401DF8@ha
    li      r4, 4
    addi    r31, r3, lbl_80401DF8@l
    addis   r5, r31, 0x8000
    subi    r5, r5, 0x404
    mr      r3, r31
    neg     r0, r5
    clrlwi  r0, r0, 6
    oris    r0, r0, 0x4800
    stw     r0, 0(r31)
    bl      DCFlushRangeNoSync
    sync
    li      r0, 0
    isync
    icbi    r31, r0
    lwz     r0, 0x14(r1)
    lwz     r31, 0xc(r1)
    lwz     r30, 8(r1)
    mtlr    r0
    addi    r1, r1, 0x10
    blr
    // clang-format on
}
