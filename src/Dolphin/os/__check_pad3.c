extern void OSResetSystem(void);

__declspec(section ".init") asm void __check_pad3(void)
{
    // clang-format off
    nofralloc
    mflr r0
    stw r0, 0x4(r1)
    stwu r1, -0x8(r1)
    lis r3, 0x8000
    lhz r0, 0x30e4(r3)
    andi. r0, r0, 0xeef
    cmpwi r0, 0xeef
    bne L_800032F0
    li r3, 0x0
    li r4, 0x0
    li r5, 0x0
    bl OSResetSystem
L_800032F0:
    lwz r0, 0xc(r1)
    addi r1, r1, 0x8
    mtlr r0
    blr
    // clang-format on
}
