extern void OSReport(const char* msg, ...);
extern void fn_801694B8(void);
extern char lbl_804CFDE2[];

asm void fn_80168C9C(void)
{
    // clang-format off
    nofralloc
    lis     r3, lbl_804CFDE2@h
    ori     r3, r3, lbl_804CFDE2@l
    lwz     r4, 0x6D0(r31)
    cmpwi   r4, 0
    bne     L_call
    bl      OSReport
    b       L_end
L_call:
    bl      fn_801694B8
L_end:
    mtlr    r30
    blr
    // clang-format on
}
