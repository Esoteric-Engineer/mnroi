extern void* lbl_8066F98C;
extern void OSClearContext(void);
extern void OSSetCurrentContext(void);
extern void OSLoadContext(void);

// Runs the swap-page callback on the faulting address (r4) in a fresh stack OSContext, then resumes the interrupted context (r3). GCC output, so asm.
asm void __VMBASEDSIServiceException(void)
{
    // clang-format off
    nofralloc
    stwu    r1, -0x2e0(r1)
    mflr    r0
    stw     r0, 0x2e4(r1)
    stw     r31, 0x2dc(r1)
    mr      r31, r4
    stw     r30, 0x2d8(r1)
    mr      r30, r3
    addi    r3, r1, 0x8
    bl      OSClearContext
    addi    r3, r1, 0x8
    bl      OSSetCurrentContext
    lwz     r12, lbl_8066F98C
    mr      r3, r31
    mtctr   r12
    bctrl
    mr      r3, r30
    bl      OSSetCurrentContext
    mr      r3, r30
    bl      OSLoadContext
    lwz     r0, 0x2e4(r1)
    lwz     r31, 0x2dc(r1)
    lwz     r30, 0x2d8(r1)
    mtlr    r0
    addi    r1, r1, 0x2e0
    blr
    // clang-format on
}
