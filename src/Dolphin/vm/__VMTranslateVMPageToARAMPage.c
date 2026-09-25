extern unsigned long* lbl_8066F974;
extern void __VMMappingErrorAlert(void);

// Returns the ARAM page for a mapped VM page, else reports the unmapped address and returns 0. GCC output, so asm.
asm unsigned long __VMTranslateVMPageToARAMPage(unsigned long addr)
{
    // clang-format off
    nofralloc
    stwu    r1, -0x10(r1)
    mflr    r0
    stw     r0, 0x14(r1)
    rlwinm  r0, r3, 22, 17, 29
    lwz     r4, lbl_8066F974
    lwzx    r0, r4, r0
    clrlwi. r0, r0, 1
    beq     L_alert
    mr      r3, r0
    b       L_done
L_alert:
    bl      __VMMappingErrorAlert
    li      r3, 0
L_done:
    lwz     r0, 0x14(r1)
    mtlr    r0
    addi    r1, r1, 0x10
    blr
    // clang-format on
}
