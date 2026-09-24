extern char lbl_804D2880[];
extern char lbl_8057D418[];
extern int lbl_8066F398;
extern short lbl_8066F39C;
extern short lbl_8066F39E;
extern int lbl_8066F3A0;
extern long long lbl_8066F3A8;
extern int lbl_8066F3D0;
extern int lbl_8066F3D4;
extern char lbl_8066C48C[5];
extern void* OSDisableInterrupts(void);
extern void OSRestoreInterrupts(void*);
extern void OSReport(const char*, ...);
extern void OSPanic(const char*, int, const char*, ...);
extern void* getTiming(int);
extern void setFbbRegs(void);
extern void setVerticalRegs(void);

// VIConfigure(rm): applies a GXRenderModeObj to the VI shadow state (HorVer/regs) with AdjustPosition,
// setInterruptRegs, setScalingRegs, setHorizontalRegs, setBBIntervalRegs and setPicConfig inlined.
// This game's version panics on an invalid TV mode; the register-heavy body is kept as asm.
asm void VIConfigure(const void* rm)
{
    // clang-format off
    nofralloc
    mflr r0
    lis r5, lbl_804D2880@ha
    stw r0, 0x4(r1)
    lis r4, lbl_8057D418@ha
    stwu r1, -0x78(r1)
    stmw r14, 0x30(r1)
    addi r31, r3, 0x0
    addi r15, r5, lbl_804D2880@l
    addi r29, r4, lbl_8057D418@l
    bl OSDisableInterrupts
    lwz r4, 0x0(r31)
    addi r28, r29, 0x114
    lwz r0, 0x114(r29)
    addi r14, r3, 0x0
    clrlwi r4, r4, 30
    cmplw r0, r4
    beq L_80188AA0
    li r0, 0x1
    stw r0, lbl_8066F3A0
    stw r4, 0x0(r28)
L_80188AA0:
    lwz r0, 0x0(r31)
    lis r3, 0x8000
    lwz r16, 0xcc(r3)
    srwi r0, r0, 2
    cmplwi r0, 0x4
    mr r17, r0
    bne L_80188B24
    lwz r0, lbl_8066F3D4
    cmplwi r0, 0x0
    bne L_80188B24
    li r0, 0x1
    crclr 6
    stw r0, lbl_8066F3D4
    addi r3, r15, 0x260
    bl OSReport
    addi r3, r15, 0x28c
    crclr 6
    bl OSReport
    addi r3, r15, 0x2b8
    crclr 6
    bl OSReport
    addi r3, r15, 0x2e4
    crclr 6
    bl OSReport
    addi r3, r15, 0x310
    crclr 6
    bl OSReport
    addi r3, r15, 0x33c
    crclr 6
    bl OSReport
    addi r3, r15, 0x260
    crclr 6
    bl OSReport
L_80188B24:
    cmpwi r16, 0x2
    beq L_80188B58
    bge L_80188B40
    cmpwi r16, 0x0
    beq L_80188B58
    bge L_80188B74
    b L_80188B84
L_80188B40:
    cmpwi r16, 0x6
    beq L_80188B58
    bge L_80188B84
    cmpwi r16, 0x5
    bge L_80188B74
    b L_80188B84
L_80188B58:
    cmplwi r17, 0x0
    beq L_80188BA0
    cmplwi r17, 0x2
    beq L_80188BA0
    cmplwi r17, 0x6
    bne L_80188B84
    b L_80188BA0
L_80188B74:
    cmplwi r17, 0x1
    beq L_80188BA0
    cmplwi r17, 0x5
    beq L_80188BA0
L_80188B84:
    addi r6, r16, 0x0
    crclr 6
    addi r7, r17, 0x0
    addi r5, r15, 0x368
    la r3, lbl_8066C48C
    li r4, 0x774
    bl OSPanic
L_80188BA0:
    cmplwi r17, 0x0
    beq L_80188BB0
    cmplwi r17, 0x2
    bne L_80188BB8
L_80188BB0:
    stw r16, 0x118(r29)
    b L_80188BBC
L_80188BB8:
    stw r17, 0x118(r29)
L_80188BBC:
    lhz r0, 0xa(r31)
    sth r0, 0xf0(r29)
    lwz r0, 0x0(r28)
    cmplwi r0, 0x1
    bne L_80188BDC
    lhz r0, 0xc(r31)
    clrlslwi r0, r0, 17, 1
    b L_80188BE0
L_80188BDC:
    lhz r0, 0xc(r31)
L_80188BE0:
    sth r0, 0xf2(r29)
    addi r23, r29, 0xf2
    addi r24, r29, 0xf4
    lhz r0, 0xe(r31)
    addi r27, r29, 0x102
    addi r25, r29, 0x110
    sth r0, 0xf4(r29)
    li r0, 0x0
    addi r16, r29, 0x10a
    lhz r3, 0x4(r31)
    addi r26, r29, 0x10c
    addi r15, r29, 0x106
    sth r3, 0x102(r29)
    addi r17, r29, 0x108
    lhz r3, 0x8(r31)
    sth r3, 0x104(r29)
    lwz r3, 0x14(r31)
    stw r3, 0x110(r29)
    lhz r3, 0x102(r29)
    sth r3, 0x10a(r29)
    lhz r3, 0x104(r29)
    sth r3, 0x10c(r29)
    sth r0, 0x106(r29)
    sth r0, 0x108(r29)
    lwz r0, 0x0(r28)
    cmplwi r0, 0x2
    bne L_80188C54
    lhz r0, 0x0(r26)
    b L_80188C80
L_80188C54:
    cmplwi r0, 0x3
    bne L_80188C64
    lhz r0, 0x0(r26)
    b L_80188C80
L_80188C64:
    lwz r0, 0x0(r25)
    cmpwi r0, 0x0
    bne L_80188C7C
    lhz r0, 0x0(r26)
    clrlslwi r0, r0, 17, 1
    b L_80188C80
L_80188C7C:
    lhz r0, 0x0(r26)
L_80188C80:
    addi r22, r29, 0xf6
    sth r0, 0xf6(r29)
    lwz r0, 0x0(r28)
    cmplwi r0, 0x3
    bne L_80188C9C
    li r0, 0x1
    b L_80188CA0
L_80188C9C:
    li r0, 0x0
L_80188CA0:
    addi r18, r29, 0x134
    stw r0, 0x134(r29)
    addi r21, r29, 0x118
    lwz r3, 0x118(r29)
    lwz r0, 0x0(r28)
    slwi r3, r3, 2
    add r3, r3, r0
    bl getTiming
    mr r30, r3
    stw r30, 0x144(r29)
    lhz r0, 0x0(r24)
    lha r4, 0xf0(r29)
    lha r3, lbl_8066F39C
    subfic r5, r0, 0x2d0
    lhz r0, 0x2(r30)
    add r3, r4, r3
    cmpw r3, r5
    ble L_80188CEC
    b L_80188CFC
L_80188CEC:
    cmpwi r3, 0x0
    bge L_80188CF8
    li r3, 0x0
L_80188CF8:
    mr r5, r3
L_80188CFC:
    sth r5, 0xf8(r29)
    addi r3, r29, 0xf8
    lwz r4, 0x0(r25)
    cmpwi r4, 0x0
    bne L_80188D18
    li r4, 0x2
    b L_80188D1C
L_80188D18:
    li r4, 0x1
L_80188D1C:
    lhz r5, 0x0(r23)
    lha r6, lbl_8066F39E
    extsh r7, r5
    clrlwi r5, r5, 31
    add r7, r7, r6
    cmpw r7, r5
    ble L_80188D3C
    b L_80188D40
L_80188D3C:
    mr r7, r5
L_80188D40:
    sth r7, 0xfa(r29)
    extsh r0, r0
    slwi r0, r0, 1
    lhz r8, 0x0(r22)
    subf r0, r5, r0
    lha r7, 0x0(r23)
    addi r19, r29, 0xfa
    extsh r9, r8
    add r10, r9, r6
    add r10, r7, r10
    subf. r9, r0, r10
    ble L_80188D78
    subf r9, r0, r10
    b L_80188D7C
L_80188D78:
    li r9, 0x0
L_80188D7C:
    add r10, r7, r6
    subf. r7, r5, r10
    bge L_80188D90
    subf r7, r5, r10
    b L_80188D94
L_80188D90:
    li r7, 0x0
L_80188D94:
    add r7, r8, r7
    subf r7, r9, r7
    addi r20, r29, 0xfc
    sth r7, 0xfc(r29)
    lha r7, 0x0(r23)
    add r8, r7, r6
    subf. r7, r5, r8
    bge L_80188DBC
    subf r7, r5, r8
    b L_80188DC0
L_80188DBC:
    li r7, 0x0
L_80188DC0:
    divw r8, r7, r4
    lhz r7, 0x0(r17)
    subf r7, r8, r7
    sth r7, 0xfe(r29)
    lha r7, 0x0(r22)
    lha r9, 0x0(r23)
    add r8, r7, r6
    add r8, r9, r8
    subf. r7, r0, r8
    ble L_80188DF0
    subf r7, r0, r8
    b L_80188DF4
L_80188DF0:
    li r7, 0x0
L_80188DF4:
    add r6, r9, r6
    subf. r0, r5, r6
    bge L_80188E08
    subf r0, r5, r6
    b L_80188E0C
L_80188E08:
    li r0, 0x0
L_80188E0C:
    divw r0, r0, r4
    lhz r5, 0x0(r26)
    divw r4, r7, r4
    add r0, r5, r0
    subf r0, r4, r0
    sth r0, 0x100(r29)
    lwz r0, lbl_8066F398
    cmplwi r0, 0x0
    bne L_80188E38
    li r0, 0x3
    stw r0, 0x0(r21)
L_80188E38:
    lhz r5, 0x18(r30)
    srawi r4, r5, 1
    addze r4, r4
    srawi r0, r5, 1
    addze r0, r0
    slwi r0, r0, 1
    subfc r0, r0, r5
    clrlwi. r0, r0, 16
    clrlwi r4, r4, 16
    beq L_80188E68
    lhz r5, 0x1a(r30)
    b L_80188E6C
L_80188E68:
    li r5, 0x0
L_80188E6C:
    addi r0, r5, 0x1
    sth r0, 0x32(r29)
    addi r0, r4, 0x1
    ori r0, r0, 0x1000
    lwz r5, lbl_8066F3A8
    addi r4, r29, 0x2
    lwz r6, lbl_8066F3A8+4
    ori r5, r5, 0x40
    stw r6, lbl_8066F3A8+4
    stw r5, lbl_8066F3A8
    sth r0, 0x30(r29)
    lwz r0, lbl_8066F3A8
    lwz r5, lbl_8066F3A8+4
    ori r0, r0, 0x80
    stw r5, lbl_8066F3A8+4
    stw r0, lbl_8066F3A8
    lwz r0, 0x0(r28)
    lhz r5, 0x2(r29)
    cmplwi r0, 0x2
    beq L_80188EC4
    cmplwi r0, 0x3
    bne L_80188ED0
L_80188EC4:
    rlwinm r0, r5, 0, 30, 28
    ori r5, r0, 0x4
    b L_80188ED8
L_80188ED0:
    rlwinm r5, r5, 0, 30, 28
    rlwimi r5, r0, 2, 29, 29
L_80188ED8:
    lwz r6, 0x0(r21)
    rlwinm r5, r5, 0, 29, 27
    lwz r7, 0x0(r18)
    cmplwi r6, 0x4
    slwi r0, r7, 3
    or r5, r5, r0
    beq L_80188F00
    subi r0, r6, 0x5
    cmplwi r0, 0x1
    bgt L_80188F08
L_80188F00:
    rlwinm r0, r5, 0, 24, 21
    b L_80188F14
L_80188F08:
    rlwinm r5, r5, 0, 24, 21
    slwi r0, r6, 8
    or r0, r5, r0
L_80188F14:
    sth r0, 0x0(r4)
    lis r0, 0x4000
    addi r6, r29, 0x6c
    lwz r4, lbl_8066F3A8
    lwz r5, lbl_8066F3A8+4
    or r0, r4, r0
    stw r5, lbl_8066F3A8+4
    stw r0, lbl_8066F3A8
    lwz r0, 0x0(r31)
    lhz r4, 0x6c(r29)
    cmpwi r0, 0x2
    beq L_80188F54
    cmpwi r0, 0x3
    beq L_80188F54
    cmpwi r0, 0x1a
    bne L_80188F60
L_80188F54:
    clrrwi r0, r4, 1
    ori r0, r0, 0x1
    b L_80188F64
L_80188F60:
    clrrwi r0, r4, 1
L_80188F64:
    sth r0, 0x0(r6)
    cmpwi r7, 0x0
    lwz r4, lbl_8066F3A8
    lwz r0, lbl_8066F3A8+4
    ori r0, r0, 0x200
    stw r0, lbl_8066F3A8+4
    stw r4, lbl_8066F3A8
    lhz r4, 0x0(r24)
    lhz r5, 0x0(r16)
    beq L_80188F94
    slwi r0, r5, 1
    b L_80188F98
L_80188F94:
    mr r0, r5
L_80188F98:
    clrlwi r8, r0, 16
    cmplw r8, r4
    bge L_80188FF0
    slwi r6, r8, 8
    subi r0, r6, 0x1
    add r0, r4, r0
    divwu r0, r0, r4
    ori r0, r0, 0x1000
    sth r0, 0x4a(r29)
    lis r0, 0x400
    lwz r6, lbl_8066F3A8
    lwz r7, lbl_8066F3A8+4
    or r0, r7, r0
    stw r0, lbl_8066F3A8+4
    stw r6, lbl_8066F3A8
    sth r8, 0x70(r29)
    lwz r6, lbl_8066F3A8
    lwz r0, lbl_8066F3A8+4
    ori r0, r0, 0x80
    stw r0, lbl_8066F3A8+4
    stw r6, lbl_8066F3A8
    b L_80189010
L_80188FF0:
    li r0, 0x100
    sth r0, 0x4a(r29)
    lis r0, 0x400
    lwz r6, lbl_8066F3A8
    lwz r7, lbl_8066F3A8+4
    or r0, r7, r0
    stw r0, lbl_8066F3A8+4
    stw r6, lbl_8066F3A8
L_80189010:
    lhz r0, 0x0(r3)
    subfic r12, r4, 0x2d0
    lhz r6, 0x1a(r30)
    lis r3, 0x1000
    lis r8, 0x2000
    sth r6, 0x6(r29)
    lis r9, 0x400
    lis r7, 0x800
    lwz r10, lbl_8066F3A8
    lis r6, 0x10
    lis r4, 0x20
    lwz r11, lbl_8066F3A8+4
    or r10, r10, r3
    lis r3, 0x4
    stw r11, lbl_8066F3A8+4
    stw r10, lbl_8066F3A8
    lbz r10, 0x1d(r30)
    lbz r11, 0x1e(r30)
    rlwimi r11, r10, 8, 16, 23
    sth r11, 0x4(r29)
    lwz r10, lbl_8066F3A8
    lwz r11, lbl_8066F3A8+4
    or r8, r10, r8
    stw r11, lbl_8066F3A8+4
    stw r8, lbl_8066F3A8
    lbz r8, 0x1f(r30)
    lbz r10, 0x1c(r30)
    add r16, r8, r0
    lhz r11, 0x20(r30)
    subi r16, r16, 0x28
    clrlslwi r8, r16, 23, 7
    or r8, r10, r8
    sth r8, 0xa(r29)
    add r8, r11, r0
    addi r0, r8, 0x28
    lwz r10, lbl_8066F3A8
    subf r0, r12, r0
    srwi r8, r16, 9
    lwz r11, lbl_8066F3A8+4
    slwi r0, r0, 1
    or r9, r10, r9
    stw r11, lbl_8066F3A8+4
    or r0, r8, r0
    stw r9, lbl_8066F3A8
    sth r0, 0x8(r29)
    lwz r0, lbl_8066F3A8
    lwz r8, lbl_8066F3A8+4
    or r0, r0, r7
    stw r8, lbl_8066F3A8+4
    stw r0, lbl_8066F3A8
    lhz r0, 0x10(r30)
    lbz r7, 0xc(r30)
    slwi r0, r0, 5
    or r0, r7, r0
    sth r0, 0x16(r29)
    lwz r0, lbl_8066F3A8
    lwz r7, lbl_8066F3A8+4
    or r0, r0, r6
    stw r7, lbl_8066F3A8+4
    stw r0, lbl_8066F3A8
    lhz r0, 0x14(r30)
    lbz r6, 0xe(r30)
    slwi r0, r0, 5
    or r0, r6, r0
    sth r0, 0x14(r29)
    lwz r0, lbl_8066F3A8
    lwz r6, lbl_8066F3A8+4
    or r0, r0, r4
    stw r6, lbl_8066F3A8+4
    stw r0, lbl_8066F3A8
    lhz r0, 0x12(r30)
    lbz r4, 0xd(r30)
    slwi r0, r0, 5
    or r0, r4, r0
    sth r0, 0x1a(r29)
    lwz r0, lbl_8066F3A8
    lwz r4, lbl_8066F3A8+4
    or r0, r0, r3
    stw r4, lbl_8066F3A8+4
    stw r0, lbl_8066F3A8
    lhz r0, 0x16(r30)
    lbz r3, 0xf(r30)
    slwi r0, r0, 5
    or r0, r3, r0
    sth r0, 0x18(r29)
    lwz r3, lbl_8066F3A8
    lis r0, 0x8
    addi r6, r29, 0x11c
    lwz r4, lbl_8066F3A8+4
    or r0, r3, r0
    stw r4, lbl_8066F3A8+4
    stw r0, lbl_8066F3A8
    lhz r3, 0x0(r27)
    lwz r4, 0x0(r25)
    addi r0, r3, 0xf
    lhz r3, 0x0(r15)
    srawi r0, r0, 4
    addze r0, r0
    cmpwi r4, 0x0
    stb r0, 0x11c(r29)
    bne L_801891AC
    lbz r4, 0x0(r6)
    b L_801891B4
L_801891AC:
    lbz r0, 0x0(r6)
    clrlslwi r4, r0, 25, 1
L_801891B4:
    srawi r0, r3, 4
    stb r4, 0x11d(r29)
    addze r0, r0
    slwi r0, r0, 4
    subfc r0, r0, r3
    stb r0, 0x12c(r29)
    addi r0, r5, 0xf
    lis r3, 0x800
    lbz r4, 0x12c(r29)
    add r0, r4, r0
    srawi r0, r0, 4
    addze r0, r0
    stb r0, 0x11e(r29)
    lbz r0, 0x11e(r29)
    lbz r4, 0x11d(r29)
    rlwimi r4, r0, 8, 16, 23
    sth r4, 0x48(r29)
    lwz r4, lbl_8066F3A8
    lwz r0, lbl_8066F3D0
    lwz r5, lbl_8066F3A8+4
    cmplwi r0, 0x0
    or r0, r5, r3
    stw r0, lbl_8066F3A8+4
    stw r4, lbl_8066F3A8
    beq L_80189230
    addi r3, r29, 0xf0
    addi r4, r29, 0x124
    addi r5, r29, 0x128
    addi r6, r29, 0x13c
    addi r7, r29, 0x140
    bl setFbbRegs
L_80189230:
    lwz r0, 0x130(r29)
    stw r0, 0x8(r1)
    lhz r3, 0x0(r19)
    lhz r4, 0x0(r20)
    lbz r5, 0x0(r30)
    lhz r6, 0x2(r30)
    lhz r7, 0x4(r30)
    lhz r8, 0x6(r30)
    lhz r9, 0x8(r30)
    lhz r10, 0xa(r30)
    bl setVerticalRegs
    mr r3, r14
    bl OSRestoreInterrupts
    lmw r14, 0x30(r1)
    lwz r0, 0x7c(r1)
    addi r1, r1, 0x78
    mtlr r0
    blr
    // clang-format on
}
