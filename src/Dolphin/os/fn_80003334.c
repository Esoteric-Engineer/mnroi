extern void lbl_8000332C(void);

/* 12 bytes of zero data (a double 0.0 at +0, a paired-single 0.0 pair at +4) read by fn_80003334 */
__declspec(section ".init") asm void lbl_80003328(void)
{
    // clang-format off
    nofralloc
    opword 0
entry lbl_8000332C
    opword 0
    opword 0
    // clang-format on
}

__declspec(section ".init") asm void fn_80003334(void)
{
    // clang-format off
    nofralloc
    mfmsr r3
    ori r3, r3, 0x2000
    mtmsr r3
    mfspr r3, 920
    extrwi. r3, r3, 1, 2
    beq L_800033D4
    lis r3, lbl_8000332C@h
    ori r3, r3, lbl_8000332C@l
    psq_l f0, 0x0(r3), 0, 0
    ps_mr f1, f0
    ps_mr f2, f0
    ps_mr f3, f0
    ps_mr f4, f0
    ps_mr f5, f0
    ps_mr f6, f0
    ps_mr f7, f0
    ps_mr f8, f0
    ps_mr f9, f0
    ps_mr f10, f0
    ps_mr f11, f0
    ps_mr f12, f0
    ps_mr f13, f0
    ps_mr f14, f0
    ps_mr f15, f0
    ps_mr f16, f0
    ps_mr f17, f0
    ps_mr f18, f0
    ps_mr f19, f0
    ps_mr f20, f0
    ps_mr f21, f0
    ps_mr f22, f0
    ps_mr f23, f0
    ps_mr f24, f0
    ps_mr f25, f0
    ps_mr f26, f0
    ps_mr f27, f0
    ps_mr f28, f0
    ps_mr f29, f0
    ps_mr f30, f0
    ps_mr f31, f0
L_800033D4:
    lis r3, lbl_80003328@h
    ori r3, r3, lbl_80003328@l
    lfd f0, 0x0(r3)
    fmr f1, f0
    fmr f2, f0
    fmr f3, f0
    fmr f4, f0
    fmr f5, f0
    fmr f6, f0
    fmr f7, f0
    fmr f8, f0
    fmr f9, f0
    fmr f10, f0
    fmr f11, f0
    fmr f12, f0
    fmr f13, f0
    fmr f14, f0
    fmr f15, f0
    fmr f16, f0
    fmr f17, f0
    fmr f18, f0
    fmr f19, f0
    fmr f20, f0
    fmr f21, f0
    fmr f22, f0
    fmr f23, f0
    fmr f24, f0
    fmr f25, f0
    fmr f26, f0
    fmr f27, f0
    fmr f28, f0
    fmr f29, f0
    fmr f30, f0
    fmr f31, f0
    mtfsf 255, f0
    blr
    // clang-format on
}
