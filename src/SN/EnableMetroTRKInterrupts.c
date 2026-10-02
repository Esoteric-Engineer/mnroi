extern char lbl_80573680[];
extern char lbl_804CFD58[];
extern void OSReport(const char* msg, ...);
extern void fn_8016BE74(void);
extern void fn_8016C3DC(void);

asm void EnableMetroTRKInterrupts(void)
{
    // clang-format off
    nofralloc
    mflr    r0
    stw     r0, 4(r1)
    stwu    r1, -16(r1)
    stw     r31, 8(r1)
    lis     r31, lbl_80573680@h
    ori     r31, r31, lbl_80573680@l
    li      r5, 0
    stw     r5, 0x6BC(r31)
    lwz     r0, 0x698(r31)
    mtlr    r0
    blrl
    mr      r4, r3
    lis     r3, lbl_804CFD58@h
    ori     r3, r3, lbl_804CFD58@l
    bl      OSReport
    lwz     r3, 0x6CC(r31)
    cmpwi   r3, 4
    bne     L_end
    bl      fn_8016BE74
    bl      fn_8016C3DC
L_end:
    lwz     r31, 8(r1)
    addi    r1, r1, 16
    lwz     r0, 4(r1)
    mtlr    r0
    blr
    // clang-format on
}
