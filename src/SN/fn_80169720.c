extern void fn_8016A2DC(void);
extern void fn_8016A1B4(void);

asm void fn_80169720(void)
{
    // clang-format off
    nofralloc
    mfmsr r5
    ori r5, r5, 0x900
    xori r5, r5, 0x900
    ori r5, r5, 0x2000
    mtmsr r5
    isync
    lis r5, 0x8000
    lwz r30, 0xd4(r5)
    lwz r3, 0xd8(r5)
    cmpw r3, r30
    beq L_80169778
    mflr r29
    cmpwi r3, 0x0
    beq L_8016975C
    bl fn_8016A2DC
L_8016975C:
    mr r3, r30
    lhz r30, 0x1a2(r3)
    ori r4, r30, 0x1
    sth r4, 0x1a2(r3)
    bl fn_8016A1B4
    sth r30, 0x1a2(r3)
    mtlr r29
L_80169778:
    stfd f0, 0x100(r31)
    stfd f1, 0x108(r31)
    stfd f2, 0x110(r31)
    stfd f3, 0x118(r31)
    stfd f4, 0x120(r31)
    stfd f5, 0x128(r31)
    stfd f6, 0x130(r31)
    stfd f7, 0x138(r31)
    stfd f8, 0x140(r31)
    stfd f9, 0x148(r31)
    stfd f10, 0x150(r31)
    stfd f11, 0x158(r31)
    stfd f12, 0x160(r31)
    stfd f13, 0x168(r31)
    stfd f14, 0x170(r31)
    stfd f15, 0x178(r31)
    stfd f16, 0x180(r31)
    stfd f17, 0x188(r31)
    stfd f18, 0x190(r31)
    stfd f19, 0x198(r31)
    stfd f20, 0x1a0(r31)
    stfd f21, 0x1a8(r31)
    stfd f22, 0x1b0(r31)
    stfd f23, 0x1b8(r31)
    stfd f24, 0x1c0(r31)
    stfd f25, 0x1c8(r31)
    stfd f26, 0x1d0(r31)
    stfd f27, 0x1d8(r31)
    stfd f28, 0x1e0(r31)
    stfd f29, 0x1e8(r31)
    stfd f30, 0x1f0(r31)
    stfd f31, 0x1f8(r31)
    mfspr r5, 920
    isync
    extrwi. r5, r5, 1, 2
    beq L_801698D4
    mfspr r5, 912
    stw r5, 0x208(r31)
    mfspr r5, 913
    stw r5, 0x210(r31)
    mfspr r5, 914
    stw r5, 0x218(r31)
    mfspr r5, 915
    stw r5, 0x220(r31)
    mfspr r5, 916
    stw r5, 0x228(r31)
    mfspr r5, 917
    stw r5, 0x230(r31)
    mfspr r5, 918
    stw r5, 0x238(r31)
    mfspr r5, 919
    stw r5, 0x240(r31)
    li r5, 0x0
    mtspr 912, r5
    isync
    psq_st f0, 0x248(r31), 0, 0
    psq_st f1, 0x250(r31), 0, 0
    psq_st f2, 0x258(r31), 0, 0
    psq_st f3, 0x260(r31), 0, 0
    psq_st f4, 0x268(r31), 0, 0
    psq_st f5, 0x270(r31), 0, 0
    psq_st f6, 0x278(r31), 0, 0
    psq_st f7, 0x280(r31), 0, 0
    psq_st f8, 0x288(r31), 0, 0
    psq_st f9, 0x290(r31), 0, 0
    psq_st f10, 0x298(r31), 0, 0
    psq_st f11, 0x2a0(r31), 0, 0
    psq_st f12, 0x2a8(r31), 0, 0
    psq_st f13, 0x2b0(r31), 0, 0
    psq_st f14, 0x2b8(r31), 0, 0
    psq_st f15, 0x2c0(r31), 0, 0
    psq_st f16, 0x2c8(r31), 0, 0
    psq_st f17, 0x2d0(r31), 0, 0
    psq_st f18, 0x2d8(r31), 0, 0
    psq_st f19, 0x2e0(r31), 0, 0
    psq_st f20, 0x2e8(r31), 0, 0
    psq_st f21, 0x2f0(r31), 0, 0
    psq_st f22, 0x2f8(r31), 0, 0
    psq_st f23, 0x300(r31), 0, 0
    psq_st f24, 0x308(r31), 0, 0
    psq_st f25, 0x310(r31), 0, 0
    psq_st f26, 0x318(r31), 0, 0
    psq_st f27, 0x320(r31), 0, 0
    psq_st f28, 0x328(r31), 0, 0
    psq_st f29, 0x330(r31), 0, 0
    psq_st f30, 0x338(r31), 0, 0
    psq_st f31, 0x340(r31), 0, 0
L_801698D4:
    mffs f0
    stfd f0, 0x200(r31)
    blr
    // clang-format on
}
