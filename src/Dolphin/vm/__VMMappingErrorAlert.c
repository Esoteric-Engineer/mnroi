extern char lbl_804DCD98[];
extern void sprintf(void);
extern void PPCHalt(void);

// sprintf's the unmapped-address message into a 0x400 stack buffer, then halts. GCC output, so asm.
asm void __VMMappingErrorAlert(unsigned long addr)
{
    // clang-format off
    nofralloc
    stwu    r1, -0x410(r1)
    mflr    r0
    lis     r4, lbl_804DCD98@ha
    mr      r5, r3
    stw     r0, 0x414(r1)
    addi    r4, r4, lbl_804DCD98@l
    addi    r3, r1, 0x8
    crclr   6
    bl      sprintf
    bl      PPCHalt
    lwz     r0, 0x414(r1)
    mtlr    r0
    addi    r1, r1, 0x410
    blr
    // clang-format on
}
