extern void __VMBASEDSIServiceExceptionPrep(void);
extern void lbl_80401C4C(void);
extern void lbl_80401C50(void);

// DSI vector body: faults in the 0x7E000000-0x80000000 VM window go to __VMBASEDSIServiceExceptionPrep via rfi; others fall into the two nop slots patched by __VMBASESetupExceptionHandlers.
asm void __VMBASEDSIExceptionHandler(void)
{
    // clang-format off
    nofralloc
    mtsprg  0, r4
    mtsprg  1, r5
    mtsprg  2, r6
    mfcr    r4
    mtsprg  3, r4
    mfspr   r5, 19
    li      r6, 0x7e
    slwi    r6, r6, 24
    cmplw   r5, r6
    blt     L_not_vm
    mfspr   r5, 19
    li      r6, 0x80
    slwi    r6, r6, 24
    cmplw   r5, r6
    bge     L_not_vm
    mfspr   r5, 18
    rlwinm  r6, r5, 0, 1, 1
    cmplwi  r6, 0x0
    beq     L_not_vm
    mfsprg  r4, 3
    mtcrf   255, r4
    mfsprg  r4, 0
    mfsprg  r5, 1
    mfsprg  r6, 2
    mtsprg  0, r4
    lwz     r4, 0xc0(r0)
    stw     r3, 0xc(r4)
    mfsprg  r3, 0
    stw     r3, 0x10(r4)
    stw     r5, 0x14(r4)
    lhz     r3, 0x1a2(r4)
    ori     r3, r3, 0x2
    sth     r3, 0x1a2(r4)
    mfcr    r3
    stw     r3, 0x80(r4)
    mflr    r3
    stw     r3, 0x84(r4)
    mfctr   r3
    stw     r3, 0x88(r4)
    mfxer   r3
    stw     r3, 0x8c(r4)
    mfsrr0  r3
    stw     r3, 0x198(r4)
    mfsrr1  r3
    stw     r3, 0x19c(r4)
    mr      r5, r3
    mfmsr   r3
    ori     r3, r3, 0x30
    mtsrr1  r3
    lwz     r3, 0xd4(r0)
    lis     r5, __VMBASEDSIServiceExceptionPrep@ha
    addi    r5, r5, __VMBASEDSIServiceExceptionPrep@l
    mtsrr0  r5
    rfi
L_not_vm:
    mfsprg  r4, 3
    mtcrf   255, r4
    mfsprg  r4, 0
    mfsprg  r5, 1
    mfsprg  r6, 2
    entry   lbl_80401C4C
    nop
    entry   lbl_80401C50
    nop
    // clang-format on
}
