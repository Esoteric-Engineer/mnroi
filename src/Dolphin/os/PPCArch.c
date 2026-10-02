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

asm void PPCSync(void)
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
