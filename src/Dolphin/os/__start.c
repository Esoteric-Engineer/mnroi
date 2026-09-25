extern char _stack_addr[];
extern char _SDA2_BASE_[];
extern char _SDA_BASE_[];
extern char lbl_8050F760[];
extern char lbl_8066B4E0[];
extern char lbl_8066CF20[];
extern char lbl_8066FB50[];
extern char lbl_804CFC40[];
extern char lbl_804CFC64[];
extern char lbl_804CFC20[];
extern void memset(void);
extern void fn_80003300(void);
extern void fn_80003334(void);
extern void fn_80003468(void);
extern void fn_80003254(void);
extern void fn_800032C0(void);
extern void fn_80003464(void);
extern void fn_8016894C(void);
extern void fn_801813D4(void);
extern void fn_8002A124(void);
extern void fn_80181448(void);
extern void DBInit(void);
extern void OSInit(void);
extern void OSReport(const char* msg, ...);

__declspec(section ".init") asm void __start(void)
{
    // clang-format off
    nofralloc
    lis r1, _stack_addr@h
    ori r1, r1, _stack_addr@l
    lis r2, _SDA2_BASE_@h
    ori r2, r2, _SDA2_BASE_@l
    lis r13, _SDA_BASE_@h
    ori r13, r13, _SDA_BASE_@l
    bl fn_80003300
    bl fn_80003334
    bl fn_80003468
    li r0, -0x1
    stwu r1, -0x8(r1)
    stw r0, 0x4(r1)
    stw r0, 0x0(r1)
    lis r3, lbl_8050F760@h
    ori r3, r3, lbl_8050F760@l
    li r4, 0x0
    lis r5, lbl_8066B4E0@h
    ori r5, r5, lbl_8066B4E0@l
    subf r5, r3, r5
    bl memset
    lis r3, lbl_8066CF20@h
    ori r3, r3, lbl_8066CF20@l
    li r4, 0x0
    lis r5, 0x8066
    ori r5, r5, lbl_8066FB50@l
    subf r5, r3, r5
    bl memset
    li r4, 0x0
    lis r5, 0x8000
    stw r4, 0x44(r5)
    li r29, 0x0
    lis r6, 0x8000
    ori r6, r6, 0xf4
    lwz r6, 0x0(r6)
    cmpwi r6, 0x0
    beq L_800031A4
    lwz r3, 0xc(r6)
    cmplwi r3, 0x2
    blt L_800031A4
    bl fn_8016894C
    li r29, 0x1
L_800031A4:
    bl fn_80003254
    mr r30, r3
    mr r31, r4
    bl DBInit
    bl OSInit
    lis r4, 0x8000
    lhz r3, 0x30e6(r4)
    andi. r4, r3, 0x8000
    beq L_800031D4
    andi. r3, r3, 0x7fff
    cmplwi r3, 0x1
    bne L_800031D8
L_800031D4:
    bl fn_800032C0
L_800031D8:
    bl fn_80003464
    mr r3, r30
    mr r4, r31
    bl fn_80003464
    bl fn_801813D4
    cmpwi r29, 0x0
    beq L_80003244
    lis r3, lbl_804CFC40@h
    ori r3, r3, lbl_804CFC40@l
    lis r4, lbl_804CFC64@h
    ori r4, r4, lbl_804CFC64@l
    lwz r4, 0x0(r4)
    bl OSReport
    lis r3, lbl_804CFC20@h
    ori r3, r3, lbl_804CFC20@l
    bl OSReport
    mfmsr r5
    ori r4, r5, 0x8000
    xori r4, r4, 0x8000
    mtmsr r4
    sync
    ori r5, r5, 0x200
    mtsrr1 r5
    lis r4, __start+0x144@h
    ori r4, r4, __start+0x144@l
    mtsrr0 r4
    rfi
L_80003244:
    mr r3, r30
    mr r4, r31
    bl fn_8002A124
    b fn_80181448
    // clang-format on
}
