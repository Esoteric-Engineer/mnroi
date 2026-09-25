extern char lbl_804CFD85[];
extern char lbl_80573680[];
void fn_80169AF4(void);
void fn_801698E0(void);
void fn_80169B48(void);
void fn_8016A078(void);
void fn_801694B8(void);
void OSReport(void);
void PPCHalt(void);
void DCFlushRange(void);
void ICInvalidateRange(void);

asm void fn_80169ECC(void)
{
    // clang-format off
    nofralloc
    mflr r0
    stw r0, 0x4(r1)
    stwu r1, -0x8(r1)
    lis r5, 0x8000
    stw r4, 0x44(r5)
    li r0, 0x1
    stw r0, 0x40(r5)
    rlwinm. r4, r3, 0, 29, 29
    beq L_80169F20
    lis r6, fn_8016A078@h
    ori r6, r6, fn_8016A078@l
    lis r4, 0x8000
    ori r4, r4, 0x300
    lis r5, 0x6000
    stw r5, 0x0(r4)
    addi r5, r4, 0x4
    subf r6, r5, r6
    lis r5, 0x4800
    or r6, r6, r5
    stw r6, 0x4(r4)
    rlwinm r3, r3, 0, 30, 28
L_80169F20:
    lis r5, 0x8000
    ori r5, r5, 0x100
    li r6, 0x1
L_80169F2C:
    and. r4, r3, r6
    beq L_80169F54
    lis r7, (fn_801698E0+0x210)@h
    ori r7, r7, (fn_801698E0+0x210)@l
    subi r8, r5, 0x4
    addi r9, r7, 0x54
L_80169F44:
    lwzu r4, 0x4(r7)
    stwu r4, 0x4(r8)
    cmplw r7, r9
    blt L_80169F44
L_80169F54:
    addi r5, r5, 0x100
    slwi. r6, r6, 1
    bne L_80169F2C
    lis r7, (fn_80169AF4+0x50)@h
    ori r7, r7, (fn_80169AF4+0x50)@l
    lis r8, 0x8000
    ori r8, r8, 0x6fc
    addi r9, r7, 0xb0
L_80169F74:
    lwzu r4, 0x4(r7)
    stwu r4, 0x4(r8)
    cmplw r7, r9
    blt L_80169F74
    lis r7, 0x8000
    ori r7, r7, 0x4fc
    lis r8, (lbl_80573680+0x8704)@h
    ori r8, r8, (lbl_80573680+0x8704)@l
    addi r9, r7, 0x104
L_80169F98:
    lwzu r4, 0x4(r7)
    stwu r4, 0x4(r8)
    cmplw r7, r9
    blt L_80169F98
    lis r3, 0x3860
    ori r3, r3, 0x4
    lis r4, (lbl_80573680+0x8704)@h
    ori r4, r4, (lbl_80573680+0x8704)@l
    addi r5, r4, 0x104
L_80169FBC:
    lwzu r6, 0x4(r4)
    cmplw r3, r6
    beq L_80169FF4
    cmplw r4, r5
    blt L_80169FBC
    lis r3, (lbl_804CFD85+0x37)@h
    ori r3, r3, (lbl_804CFD85+0x37)@l
    lwz r4, 0x6d0(r31)
    cmpwi r4, 0x0
    bne L_80169FEC
    bl OSReport
    b PPCHalt
L_80169FEC:
    bl fn_801694B8
    b PPCHalt
L_80169FF4:
    subi r4, r4, 0x4
    lis r6, 0x3860
    ori r6, r6, 0x6
    stwu r6, 0x4(r4)
    lis r3, 0x8000
    ori r3, r3, 0x700
    lwz r4, 0x5c(r3)
    lis r5, fn_80169B48@h
    ori r5, r5, fn_80169B48@l
    subf r5, r3, r5
    add r4, r4, r5
    stw r4, 0x5c(r3)
    lis r3, 0x8000
    ori r3, r3, 0x100
    li r4, 0x2000
    bl DCFlushRange
    lis r3, 0x8000
    ori r3, r3, 0x100
    li r4, 0x2000
    bl ICInvalidateRange
    li r3, 0x0
    li r4, 0x2000
    bl ICInvalidateRange
    addi r1, r1, 0x8
    lwz r0, 0x4(r1)
    mtlr r0
    blr
}
