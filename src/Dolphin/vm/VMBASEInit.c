extern unsigned long lbl_8066F990;

extern void __VMBASESetSwapPageCallback(void* callback);
extern unsigned long OSGetArenaLo(void);
extern void __VMBASEInitLockedPageTable(void);
extern void __VMBASEInitReversePageTable(void);
extern void __VMBASEInitPageTable(void);
extern void __VMBASESetupExceptionHandlers(void);
extern void __VMBASESetupVMRegisters(void);
extern void __VMBASEInvalidateEntireTLB(void);

// Runs the VM subsystem's one-time init: installs the swap-page callback, then
// reserves the locked/reverse/page tables in whichever order leaves no gap
// before the next 0x10000-aligned boundary. GCC output, so asm.
asm void VMBASEInit(void* callback)
{
    // clang-format off
    nofralloc
    stwu    r1, -0x10(r1)
    mflr    r0
    stw     r0, 0x14(r1)
    lwz     r0, lbl_8066F990
    cmpwi   r0, 0
    bne     L_done
    li      r0, 1
    stw     r0, lbl_8066F990
    bl      __VMBASESetSwapPageCallback
    bl      OSGetArenaLo
    clrlwi  r3, r3, 16
    lis     r0, 0x1
    subf    r0, r3, r0
    cmplwi  r0, 0x5000
    blt     L_slack_lt_5000
    bl      __VMBASEInitLockedPageTable
    bl      __VMBASEInitReversePageTable
    bl      __VMBASEInitPageTable
    b       L_tables_done
L_slack_lt_5000:
    cmplwi  r0, 0x4000
    blt     L_slack_lt_4000
    bl      __VMBASEInitReversePageTable
    bl      __VMBASEInitPageTable
    bl      __VMBASEInitLockedPageTable
    b       L_tables_done
L_slack_lt_4000:
    cmplwi  r0, 0x1000
    blt     L_slack_lt_1000
    bl      __VMBASEInitLockedPageTable
    bl      __VMBASEInitPageTable
    bl      __VMBASEInitReversePageTable
    b       L_tables_done
L_slack_lt_1000:
    bl      __VMBASEInitPageTable
    bl      __VMBASEInitLockedPageTable
    bl      __VMBASEInitReversePageTable
L_tables_done:
    bl      __VMBASESetupExceptionHandlers
    bl      __VMBASESetupVMRegisters
    bl      __VMBASEInvalidateEntireTLB
L_done:
    lwz     r0, 0x14(r1)
    mtlr    r0
    addi    r1, r1, 0x10
    blr
    // clang-format on
}
