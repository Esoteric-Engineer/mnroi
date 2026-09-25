asm void fn_8016A1B4(void)
{
    // clang-format off
    nofralloc
    mr r4, r3
    lhz r5, 0x1a2(r4)
    clrlwi. r5, r5, 31
    beq L_8016A2D8
    lfd f0, 0x190(r4)
    mtfsf 255, f0
    mfspr r5, 920
    extrwi. r5, r5, 1, 2
    beq L_8016A258
    psq_l f0, 0x1c8(r4), 0, 0
    psq_l f1, 0x1d0(r4), 0, 0
    psq_l f2, 0x1d8(r4), 0, 0
    psq_l f3, 0x1e0(r4), 0, 0
    psq_l f4, 0x1e8(r4), 0, 0
    psq_l f5, 0x1f0(r4), 0, 0
    psq_l f6, 0x1f8(r4), 0, 0
    psq_l f7, 0x200(r4), 0, 0
    psq_l f8, 0x208(r4), 0, 0
    psq_l f9, 0x210(r4), 0, 0
    psq_l f10, 0x218(r4), 0, 0
    psq_l f11, 0x220(r4), 0, 0
    psq_l f12, 0x228(r4), 0, 0
    psq_l f13, 0x230(r4), 0, 0
    psq_l f14, 0x238(r4), 0, 0
    psq_l f15, 0x240(r4), 0, 0
    psq_l f16, 0x248(r4), 0, 0
    psq_l f17, 0x250(r4), 0, 0
    psq_l f18, 0x258(r4), 0, 0
    psq_l f19, 0x260(r4), 0, 0
    psq_l f20, 0x268(r4), 0, 0
    psq_l f21, 0x270(r4), 0, 0
    psq_l f22, 0x278(r4), 0, 0
    psq_l f23, 0x280(r4), 0, 0
    psq_l f24, 0x288(r4), 0, 0
    psq_l f25, 0x290(r4), 0, 0
    psq_l f26, 0x298(r4), 0, 0
    psq_l f27, 0x2a0(r4), 0, 0
    psq_l f28, 0x2a8(r4), 0, 0
    psq_l f29, 0x2b0(r4), 0, 0
    psq_l f30, 0x2b8(r4), 0, 0
    psq_l f31, 0x2c0(r4), 0, 0
L_8016A258:
    lfd f0, 0x90(r4)
    lfd f1, 0x98(r4)
    lfd f2, 0xa0(r4)
    lfd f3, 0xa8(r4)
    lfd f4, 0xb0(r4)
    lfd f5, 0xb8(r4)
    lfd f6, 0xc0(r4)
    lfd f7, 0xc8(r4)
    lfd f8, 0xd0(r4)
    lfd f9, 0xd8(r4)
    lfd f10, 0xe0(r4)
    lfd f11, 0xe8(r4)
    lfd f12, 0xf0(r4)
    lfd f13, 0xf8(r4)
    lfd f14, 0x100(r4)
    lfd f15, 0x108(r4)
    lfd f16, 0x110(r4)
    lfd f17, 0x118(r4)
    lfd f18, 0x120(r4)
    lfd f19, 0x128(r4)
    lfd f20, 0x130(r4)
    lfd f21, 0x138(r4)
    lfd f22, 0x140(r4)
    lfd f23, 0x148(r4)
    lfd f24, 0x150(r4)
    lfd f25, 0x158(r4)
    lfd f26, 0x160(r4)
    lfd f27, 0x168(r4)
    lfd f28, 0x170(r4)
    lfd f29, 0x178(r4)
    lfd f30, 0x180(r4)
    lfd f31, 0x188(r4)
L_8016A2D8:
    blr
    // clang-format on
}
