typedef unsigned long u32;
typedef long s32;
typedef unsigned short u16;

asm u32 PPCMfmsr(void)
{
    // clang-format off
    nofralloc
    mfmsr r3
    blr
    // clang-format on
}

asm void PPCMtmsr(register u32 msr)
{
    // clang-format off
    nofralloc
    mtmsr r3
    blr
    // clang-format on
}

asm u32 PPCMfhid0(void)
{
    // clang-format off
    nofralloc
    mfspr r3, HID0
    blr
    // clang-format on
}

asm void PPCMthid0(register u32 hid0)
{
    // clang-format off
    nofralloc
    mtspr HID0, r3
    blr
    // clang-format on
}

asm u32 PPCMfl2cr(void)
{
    // clang-format off
    nofralloc
    mfspr r3, 1017
    blr
    // clang-format on
}

asm void PPCMtl2cr(register u32 l2cr)
{
    // clang-format off
    nofralloc
    mtspr 1017, r3
    blr
    // clang-format on
}

asm void PPCMtdec(register u32 dec)
{
    // clang-format off
    nofralloc
    mtdec r3
    blr
    // clang-format on
}

asm void fn_8017A838(void)
{
    // clang-format off
    nofralloc
    sc
    blr
    // clang-format on
}

asm void PPCHalt(void)
{
    // clang-format off
    nofralloc
    sync
loop:
    nop
    li   r3, 0
    nop
    b    loop
    // clang-format on
}

asm void PPCMtmmcr0(register u32 mmcr0)
{
    // clang-format off
    nofralloc
    mtspr 952, r3
    blr
    // clang-format on
}

asm void PPCMtmmcr1(register u32 mmcr1)
{
    // clang-format off
    nofralloc
    mtspr 956, r3
    blr
    // clang-format on
}

asm void PPCMtpmc1(register u32 pmc1)
{
    // clang-format off
    nofralloc
    mtspr 953, r3
    blr
    // clang-format on
}

asm void PPCMtpmc2(register u32 pmc2)
{
    // clang-format off
    nofralloc
    mtspr 954, r3
    blr
    // clang-format on
}

asm void PPCMtpmc3(register u32 pmc3)
{
    // clang-format off
    nofralloc
    mtspr 957, r3
    blr
    // clang-format on
}

asm void PPCMtpmc4(register u32 pmc4)
{
    // clang-format off
    nofralloc
    mtspr 958, r3
    blr
    // clang-format on
}

asm u32 PPCMffpscr(void)
{
    // clang-format off
    nofralloc
    stwu r1, -24(r1)
    stfd f31, 16(r1)
    mffs f31
    stfd f31, 8(r1)
    lwz  r3, 12(r1)
    lfd  f31, 16(r1)
    addi r1, r1, 24
    blr
    // clang-format on
}

asm void PPCMtfpscr(register u32 fpscr)
{
    // clang-format off
    nofralloc
    stwu  r1, -32(r1)
    stfd  f31, 24(r1)
    li    r4, 0
    stw   r4, 16(r1)
    stw   r3, 20(r1)
    lfd   f31, 16(r1)
    mtfsf 255, f31
    lfd   f31, 24(r1)
    addi  r1, r1, 32
    blr
    // clang-format on
}

asm u32 PPCMfhid2(void)
{
    // clang-format off
    nofralloc
    mfspr r3, 920
    blr
    // clang-format on
}

asm void PPCMthid2(register u32 hid2)
{
    // clang-format off
    nofralloc
    mtspr 920, r3
    blr
    // clang-format on
}

asm u32 PPCMfwpar(void)
{
    // clang-format off
    nofralloc
    sync
    mfspr r3, 921
    blr
    // clang-format on
}

asm void PPCMtwpar(register u32 wpar)
{
    // clang-format off
    nofralloc
    mtspr 921, r3
    blr
    // clang-format on
}

void PPCDisableSpeculation(void)
{
    PPCMthid0(PPCMfhid0() | 0x200);
}

asm void PPCSetFpNonIEEEMode(void)
{
    // clang-format off
    nofralloc
    mtfsb1 29
    blr
    // clang-format on
}

u32* lbl_8066F1D0 = 0;
u32 BI2DebugFlag = 0;
u32 lbl_8066F1D8 = 0;
u32 lbl_8066F1DC = 0;
static double lbl_8066F1E0;
static float lbl_8066F1E8[2];

asm void fn_8017A920(void)
{
    // clang-format off
    nofralloc
    mfmsr   r3
    ori     r3, r3, 8192
    mtmsr   r3
    mfspr   r3, 920
    rlwinm. r3, r3, 3, 31, 31
    beq     scalar_init
    lis     r3, lbl_8066F1E8@ha
    addi    r3, r3, lbl_8066F1E8@l
    psq_l   f0, 0(r3), 0, 0
    ps_mr   f1, f0
    ps_mr   f2, f0
    ps_mr   f3, f0
    ps_mr   f4, f0
    ps_mr   f5, f0
    ps_mr   f6, f0
    ps_mr   f7, f0
    ps_mr   f8, f0
    ps_mr   f9, f0
    ps_mr   f10, f0
    ps_mr   f11, f0
    ps_mr   f12, f0
    ps_mr   f13, f0
    ps_mr   f14, f0
    ps_mr   f15, f0
    ps_mr   f16, f0
    ps_mr   f17, f0
    ps_mr   f18, f0
    ps_mr   f19, f0
    ps_mr   f20, f0
    ps_mr   f21, f0
    ps_mr   f22, f0
    ps_mr   f23, f0
    ps_mr   f24, f0
    ps_mr   f25, f0
    ps_mr   f26, f0
    ps_mr   f27, f0
    ps_mr   f28, f0
    ps_mr   f29, f0
    ps_mr   f30, f0
    ps_mr   f31, f0
scalar_init:
    lfd     f0, lbl_8066F1E0
    fmr     f1, f0
    fmr     f2, f0
    fmr     f3, f0
    fmr     f4, f0
    fmr     f5, f0
    fmr     f6, f0
    fmr     f7, f0
    fmr     f8, f0
    fmr     f9, f0
    fmr     f10, f0
    fmr     f11, f0
    fmr     f12, f0
    fmr     f13, f0
    fmr     f14, f0
    fmr     f15, f0
    fmr     f16, f0
    fmr     f17, f0
    fmr     f18, f0
    fmr     f19, f0
    fmr     f20, f0
    fmr     f21, f0
    fmr     f22, f0
    fmr     f23, f0
    fmr     f24, f0
    fmr     f25, f0
    fmr     f26, f0
    fmr     f27, f0
    fmr     f28, f0
    fmr     f29, f0
    fmr     f30, f0
    fmr     f31, f0
    mtfsf   255, f0
    blr
    // clang-format on
}

u32 OSGetConsoleType(void)
{
    u32* p = lbl_8066F1D0;
    if (p == 0 || p[11] == 0) {
        return 0x10000002;
    }
    return p[11];
}

extern u16 lbl_8057C500[40];

void fn_8017AA70(void* unused, s32* p)
{
    switch (p[3]) {
    case 0:
        *(u16*)0x800030E6 = lbl_8057C500[1] | 0x8000;
        break;
    default:
        *(u16*)0x800030E6 = 1;
        break;
    }
}
