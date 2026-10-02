extern char lbl_804CFC78[];
extern char lbl_804CFC7C[];
extern char lbl_804CFC80[];
extern char lbl_804CFC90[];
extern char lbl_804CFCAC[];
extern char lbl_804CFCC8[];
extern char lbl_804CFCE4[];
extern char lbl_80573680[];
void DCFlushRange(void);
void ICInvalidateRange(void);
void InitializeUART(void);
void PPCHalt(void);
void WriteUARTN(void);
void fn_80168770(void);
void fn_801687F8(void);
void fn_80169ECC(void);
void fn_8016A9E0(void);
void fn_8016AAD0(void);
void fn_8016C3BC(void);

asm void fn_8016894C(void)
{
    // clang-format off
    nofralloc
    mflr r0
    stw r0, 0x4(r1)
    stwu r1, -0x10(r1)
    stw r31, 0x8(r1)
    lis r31, lbl_80573680@h
    ori r31, r31, lbl_80573680@l
    stw r3, 0x6cc(r31)
    li r5, 0x0
    stw r5, 0x6d0(r31)
    lis r4, lbl_804CFC90@h
    ori r4, r4, lbl_804CFC90@l
    cmpwi r3, 0x2
    beq L_80168A10
    lis r4, lbl_804CFCAC@h
    ori r4, r4, lbl_804CFCAC@l
    cmpwi r3, 0x3
    beq L_80168A10
    lis r4, lbl_804CFCC8@h
    ori r4, r4, lbl_804CFCC8@l
    cmpwi r3, 0x4
    bne L_801689FC
    li r5, 0x1
    stw r5, 0x6d0(r31)
    lis r3, WriteUARTN@h
    ori r3, r3, WriteUARTN@l
    li r5, 0x3
    stw r5, 0x0(r3)
    lis r5, 0x4e80
    ori r5, r5, 0x20
    stw r5, 0x4(r3)
    lis r3, InitializeUART@h
    ori r3, r3, InitializeUART@l
    lis r5, 0x3860
    stw r5, 0x0(r3)
    lis r5, 0x4e80
    ori r5, r5, 0x20
    stw r5, 0x4(r3)
    lis r3, 0x8000
    ori r3, r3, 0xf4
    lwz r3, 0x0(r3)
    subi r3, r3, 0x4
    lwz r3, 0x0(r3)
    bl fn_8016C3BC
    b L_80168A10
L_801689FC:
    li r3, 0x1
    addi r1, r1, 0x10
    lwz r0, 0x4(r1)
    mtlr r0
    blr
L_80168A10:
    addi r3, r31, 0x694
    li r5, 0x1c
    bl fn_80168770
    li r5, 0x0
    stw r5, 0x6bc(r31)
    addi r3, r31, 0x6b0
    stw r5, 0x0(r3)
    lis r4, fn_801687F8@h
    ori r4, r4, fn_801687F8@l
    lwz r0, 0x694(r31)
    mtlr r0
    blrl
    lwz r0, 0x6a8(r31)
    mtlr r0
    blrl
    lis r3, 0x4
    ori r3, r3, 0x1040
    li r4, 0x1440
    lis r5, lbl_804CFC7C@h
    ori r5, r5, lbl_804CFC7C@l
    lwz r5, 0x0(r5)
    cmpwi r5, 0x0
    beq L_80168A74
    ori r3, r3, 0x4
    ori r4, r4, 0x4
L_80168A74:
    lis r5, lbl_804CFC78@h
    ori r5, r5, lbl_804CFC78@l
    lwz r5, 0x0(r5)
    cmpwi r5, 0x0
    beq L_80168A90
    ori r3, r3, 0x8
    ori r4, r4, 0x8
L_80168A90:
    lis r5, lbl_804CFC80@h
    ori r5, r5, lbl_804CFC80@l
    lwz r5, 0x0(r5)
    cmpwi r5, 0x0
    beq L_80168AAC
    ori r3, r3, 0x20
    ori r4, r4, 0x20
L_80168AAC:
    bl fn_80169ECC
    li r3, 0x0
    stw r3, 0x688(r31)
    stw r3, 0x68c(r31)
    stw r3, 0x690(r31)
    lis r5, PPCHalt@h
    ori r5, r5, PPCHalt@l
    lis r3, lbl_804CFCE4@h
    ori r3, r3, lbl_804CFCE4@l
L_80168AD0:
    lwz r4, 0x0(r3)
    cmpwi r4, -0x1
    beq L_80168AF4
    lwz r6, 0x0(r5)
    cmplw r6, r4
    bne L_80168B04
    addi r3, r3, 0x4
    addi r5, r5, 0x4
    b L_80168AD0
L_80168AF4:
    lis r3, PPCHalt@h
    ori r3, r3, PPCHalt@l
    li r31, 0x1
    stw r31, 0xc(r3)
L_80168B04:
    bl fn_8016A9E0
    lis r3, WriteUARTN@h
    ori r3, r3, WriteUARTN@l
    li r4, 0x100
    bl DCFlushRange
    lis r3, InitializeUART@h
    ori r3, r3, InitializeUART@l
    li r4, 0x100
    bl DCFlushRange
    lis r3, fn_8016AAD0@h
    ori r3, r3, fn_8016AAD0@l
    li r4, 0x100
    bl DCFlushRange
    lis r3, PPCHalt@h
    ori r3, r3, PPCHalt@l
    li r4, 0x100
    bl DCFlushRange
    lis r3, WriteUARTN@h
    ori r3, r3, WriteUARTN@l
    li r4, 0x100
    bl ICInvalidateRange
    lis r3, InitializeUART@h
    ori r3, r3, InitializeUART@l
    li r4, 0x100
    bl ICInvalidateRange
    lis r3, fn_8016AAD0@h
    ori r3, r3, fn_8016AAD0@l
    li r4, 0x100
    bl ICInvalidateRange
    lis r3, PPCHalt@h
    ori r3, r3, PPCHalt@l
    li r4, 0x100
    bl ICInvalidateRange
    lwz r31, 0x8(r1)
    addi r1, r1, 0x10
    lwz r0, 0x4(r1)
    mtlr r0
    blr
    // clang-format on
}
