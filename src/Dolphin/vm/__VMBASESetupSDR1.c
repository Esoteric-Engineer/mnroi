void lbl_804019B4(void);
void lbl_804019DC(void);

// Writes SDR1 (r4) with translation off: rfi to lbl_804019B4 with MSR r3, sync/mtsdr1, then rfi back to lbl_804019DC with IR/DR on. Hand-written asm.
asm void __VMBASESetupSDR1(void)
{
    // clang-format off
    nofralloc
    mtsrr1  r3
    lis     r5, lbl_804019B4@ha
    addi    r5, r5, lbl_804019B4@l
    clrlwi  r5, r5, 1
    mtsrr0  r5
    rfi
entry lbl_804019B4
    sync
    mtsdr1  r4
    sync
    mfmsr   r3
    ori     r3, r3, 0x30
    mtsrr1  r3
    lis     r5, lbl_804019DC@ha
    addi    r5, r5, lbl_804019DC@l
    mtsrr0  r5
    rfi
entry lbl_804019DC
    nop
    blr
    // clang-format on
}
