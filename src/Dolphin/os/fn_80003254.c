__declspec(section ".init") asm void fn_80003254(void)
{
    // clang-format off
    nofralloc
    lis r6, 0x8000
    ori r6, r6, 0xf4
    lwz r5, 0x0(r6)
    cmpwi r5, 0x0
    bne L_80003274
L_80003268:
    li r3, 0x0
    li r4, 0x0
    blr
L_80003274:
    lwz r6, 0x8(r5)
    cmpwi r6, 0x0
    beq L_80003268
    add r6, r5, r6
    lwz r3, 0x0(r6)
    cmpwi r3, 0x0
    beq L_80003268
    addi r4, r6, 0x4
    mtctr r3
L_80003298:
    addi r6, r6, 0x4
    lwz r7, 0x0(r6)
    add r7, r7, r5
    stw r7, 0x0(r6)
    bdnz L_80003298
    lis r5, 0x8000
    ori r5, r5, 0x34
    clrrwi r7, r4, 5
    stw r7, 0x0(r5)
    blr
    // clang-format on
}
