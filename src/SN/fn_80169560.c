extern void fn_8016A2DC(void);
extern void fn_8016A1B4(void);

asm void fn_80169560(void)
{
    // clang-format off
    nofralloc
    mfmsr r5
    ori r5, r5, 0x900
    xori r5, r5, 0x900
    ori r5, r5, 0x2000
    mtmsr r5
    isync
    lfd f0, 0x200(r31)
    mtfsf 255, f0
    mfspr r5, 920
    isync
    extrwi. r5, r5, 1, 2
    beq L_8016965C
    li r5, 0x0
    mtspr 912, r5
    isync
    psq_l f0, 0x248(r31), 0, 0
    psq_l f1, 0x250(r31), 0, 0
    psq_l f2, 0x258(r31), 0, 0
    psq_l f3, 0x260(r31), 0, 0
    psq_l f4, 0x268(r31), 0, 0
    psq_l f5, 0x270(r31), 0, 0
    psq_l f6, 0x278(r31), 0, 0
    psq_l f7, 0x280(r31), 0, 0
    psq_l f8, 0x288(r31), 0, 0
    psq_l f9, 0x290(r31), 0, 0
    psq_l f10, 0x298(r31), 0, 0
    psq_l f11, 0x2a0(r31), 0, 0
    psq_l f12, 0x2a8(r31), 0, 0
    psq_l f13, 0x2b0(r31), 0, 0
    psq_l f14, 0x2b8(r31), 0, 0
    psq_l f15, 0x2c0(r31), 0, 0
    psq_l f16, 0x2c8(r31), 0, 0
    psq_l f17, 0x2d0(r31), 0, 0
    psq_l f18, 0x2d8(r31), 0, 0
    psq_l f19, 0x2e0(r31), 0, 0
    psq_l f20, 0x2e8(r31), 0, 0
    psq_l f21, 0x2f0(r31), 0, 0
    psq_l f22, 0x2f8(r31), 0, 0
    psq_l f23, 0x300(r31), 0, 0
    psq_l f24, 0x308(r31), 0, 0
    psq_l f25, 0x310(r31), 0, 0
    psq_l f26, 0x318(r31), 0, 0
    psq_l f27, 0x320(r31), 0, 0
    psq_l f28, 0x328(r31), 0, 0
    psq_l f29, 0x330(r31), 0, 0
    psq_l f30, 0x338(r31), 0, 0
    psq_l f31, 0x340(r31), 0, 0
    lwz r5, 0x208(r31)
    mtspr 912, r5
    lwz r5, 0x210(r31)
    mtspr 913, r5
    lwz r5, 0x218(r31)
    mtspr 914, r5
    lwz r5, 0x220(r31)
    mtspr 915, r5
    lwz r5, 0x228(r31)
    mtspr 916, r5
    lwz r5, 0x230(r31)
    mtspr 917, r5
    lwz r5, 0x238(r31)
    mtspr 918, r5
    lwz r5, 0x240(r31)
    mtspr 919, r5
L_8016965C:
    lfd f0, 0x100(r31)
    lfd f1, 0x108(r31)
    lfd f2, 0x110(r31)
    lfd f3, 0x118(r31)
    lfd f4, 0x120(r31)
    lfd f5, 0x128(r31)
    lfd f6, 0x130(r31)
    lfd f7, 0x138(r31)
    lfd f8, 0x140(r31)
    lfd f9, 0x148(r31)
    lfd f10, 0x150(r31)
    lfd f11, 0x158(r31)
    lfd f12, 0x160(r31)
    lfd f13, 0x168(r31)
    lfd f14, 0x170(r31)
    lfd f15, 0x178(r31)
    lfd f16, 0x180(r31)
    lfd f17, 0x188(r31)
    lfd f18, 0x190(r31)
    lfd f19, 0x198(r31)
    lfd f20, 0x1a0(r31)
    lfd f21, 0x1a8(r31)
    lfd f22, 0x1b0(r31)
    lfd f23, 0x1b8(r31)
    lfd f24, 0x1c0(r31)
    lfd f25, 0x1c8(r31)
    lfd f26, 0x1d0(r31)
    lfd f27, 0x1d8(r31)
    lfd f28, 0x1e0(r31)
    lfd f29, 0x1e8(r31)
    lfd f30, 0x1f0(r31)
    lfd f31, 0x1f8(r31)
    lis r5, 0x8000
    lwz r3, 0xd4(r5)
    lwz r30, 0xd8(r5)
    cmpw r3, r30
    beq L_8016971C
    mflr r29
    bl fn_8016A2DC
    cmpwi r30, 0x0
    beq L_80169718
    mr r3, r30
    lhz r30, 0x1a2(r3)
    ori r4, r30, 0x1
    sth r4, 0x1a2(r3)
    bl fn_8016A1B4
    sth r30, 0x1a2(r3)
L_80169718:
    mtlr r29
L_8016971C:
    blr
    // clang-format on
}
