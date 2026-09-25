extern char lbl_804CFC70[];
extern char lbl_804CFF30[];
extern char lbl_80573680[];
extern void OSDisableInterrupts(void);
extern void fn_8016BCC4(void);

asm void fn_801687F8(void)
{
    // clang-format off
    nofralloc
    mflr    r0
    stw     r0, 4(r1)
    stwu    r1, -16(r1)
    stw     r31, 8(r1)
    stw     r4, 12(r1)
    lis     r6, lbl_804CFC70@h
    ori     r6, r6, lbl_804CFC70@l
    lwz     r5, 0(r6)
    cmpwi   r5, 0
    bne     L_end
    lis     r3, lbl_804CFF30@h
    ori     r3, r3, lbl_804CFF30@l
    lwz     r3, 0(r3)
    cmpwi   r3, 0
    beq     L_noflag
    bl      fn_8016BCC4
    b       L_end
L_noflag:
    lis     r31, lbl_80573680@h
    ori     r31, r31, lbl_80573680@l
    lwz     r3, 0x6cc(r31)
    cmpwi   r3, 2
    beq     L_go
    cmpwi   r3, 3
    beq     L_go
    lwz     r0, 0x69c(r31)
    mtlr    r0
    blrl
    cmpwi   r3, 0
    beq     L_end
L_go:
    lwz     r4, 12(r1)
    lwz     r5, 0x19c(r4)
    ori     r5, r5, 0x400
    stw     r5, 0x19c(r4)
    li      r5, 1
    stw     r5, 0x6bc(r31)
    lwz     r10, 0x198(r4)
    lis     r7, OSDisableInterrupts@h
    ori     r7, r7, OSDisableInterrupts@l
    cmplw   r10, r7
    blt     L_load
    lis     r8, OSDisableInterrupts+0xC@h
    ori     r8, r8, OSDisableInterrupts+0xC@l
    cmplw   r10, r8
    bgt     L_load
    stw     r7, 0x198(r4)
    mr      r10, r7
L_load:
    lwz     r7, 0(r10)
    rlwinm  r9, r7, 0, 11, 5
    lis     r8, 0x7c00
    ori     r8, r8, 0xa6
    cmpw    r9, r8
    bne     L_end
    rlwinm  r7, r7, 14, 24, 28
    stw     r7, 0x6c4(r31)
    stw     r10, 0x6c0(r31)
L_end:
    lwz     r31, 8(r1)
    lwz     r0, 0x14(r1)
    addi    r1, r1, 16
    mtlr    r0
    blr
    // clang-format on
}
