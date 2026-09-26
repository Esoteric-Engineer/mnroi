asm void* __va_arg(void)
{
    // clang-format off
    nofralloc
    clrlwi r0, r4, 24
    lbz r6, 0x0(r3)
    cmplwi r0, 0x4
    addi r7, r3, 0x0
    extsb r6, r6
    li r5, 0x8
    li r8, 0x4
    li r9, 0x1
    li r10, 0x0
    li r11, 0x0
    li r12, 0x4
    bne L_8016B604
    lwz r4, 0x4(r3)
    addi r0, r4, 0xf
    clrrwi r4, r0, 4
    addi r0, r4, 0x10
    stw r0, 0x4(r3)
    mr r3, r4
    blr
L_8016B604:
    cmplwi r0, 0x3
    bne L_8016B624
    lbz r6, 0x1(r3)
    addi r7, r3, 0x1
    li r8, 0x8
    extsb r6, r6
    li r11, 0x20
    li r12, 0x8
L_8016B624:
    clrlwi r0, r4, 24
    cmplwi r0, 0x2
    bne L_8016B648
    clrlwi. r0, r6, 31
    li r8, 0x8
    li r5, 0x7
    beq L_8016B644
    li r10, 0x1
L_8016B644:
    li r9, 0x2
L_8016B648:
    cmpw r6, r5
    bge L_8016B670
    add r6, r6, r10
    lwz r5, 0x8(r3)
    mullw r3, r6, r12
    add r0, r6, r9
    add r6, r11, r3
    stb r0, 0x0(r7)
    add r6, r5, r6
    b L_8016B698
L_8016B670:
    li r0, 0x8
    stb r0, 0x0(r7)
    subi r0, r8, 0x1
    nor r6, r0, r0
    lwz r0, 0x4(r3)
    add r5, r8, r0
    subi r0, r5, 0x1
    and r6, r6, r0
    add r0, r6, r8
    stw r0, 0x4(r3)
L_8016B698:
    clrlwi. r0, r4, 24
    bne L_8016B6A4
    lwz r6, 0x0(r6)
L_8016B6A4:
    mr r3, r6
    blr
    // clang-format on
}
