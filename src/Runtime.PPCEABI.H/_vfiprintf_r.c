extern int lbl_8066C3AC;
extern int lbl_8066C3B0;
extern char lbl_8049C610[];
extern char lbl_8049C620[];
extern char lbl_8049C630[];
extern char lbl_8049C644[];
extern char lbl_8049C64C[];
extern char lbl_8049C660[];
extern void _vfiwrite(void);
extern void __group_digits(void);
extern void _mbtowc_r(void);
extern void memchr(void);
extern void memcpy(void);
extern void strlen(void);
extern void __udivdi3(void);
extern void __umoddi3(void);

// _vfiprintf_r(reent, fp, fmt, ap): Newlib printf body without float support (GCC output).
asm int _vfiprintf_r(void* reent, void* fp, const char* fmt, void* ap)
{
    // clang-format off
    nofralloc
    stwu r1, -0xa0(r1)
    mflr r0
    mfcr r12
    stmw r14, 0x58(r1)
    stw r0, 0xa4(r1)
    stw r12, 0x54(r1)
    li r0, 0x0
    addi r9, r1, 0x34
    stw r0, 0x34(r1)
    mr r29, r4
    addi r0, r1, 0x30
    stw r9, 0x48(r1)
    stw r0, 0x44(r1)
    mr r28, r6
    mr r22, r5
    li r14, 0x0
    li r16, 0x0
    li r18, 0x8
L_80175820:
    mr r26, r22
L_80175824:
    lwz r3, lbl_8066C3B0
    mr r5, r22
    lwz r4, 0x44(r1)
    lwz r6, lbl_8066C3AC
    lwz r7, 0x48(r1)
    bl _mbtowc_r
    mr. r30, r3
    ble L_80175858
    lhz r0, 0x30(r1)
    add r22, r22, r30
    cmpwi r0, 0x25
    bne L_80175824
    subi r22, r22, 0x1
L_80175858:
    subf. r31, r26, r22
    beq L_801758FC
    lhz r0, 0xc(r29)
    andi. r9, r0, 0x200
    beq L_801758D0
    lwz r5, 0x8(r29)
    cmpw r5, r31
    ble L_801758A8
    lwz r3, 0x0(r29)
    mr r4, r26
    mr r5, r31
    crclr 6
    bl memcpy
    lwz r0, 0x0(r29)
    lwz r9, 0x8(r29)
    add r0, r0, r31
    subf r9, r31, r9
    stw r0, 0x0(r29)
    stw r9, 0x8(r29)
    b L_801758F8
L_801758A8:
    lwz r3, 0x0(r29)
    mr r4, r26
    crclr 6
    bl memcpy
    lwz r0, 0x0(r29)
    lwz r9, 0x8(r29)
    stw r16, 0x8(r29)
    add r0, r0, r9
    stw r0, 0x0(r29)
    b L_801758F8
L_801758D0:
    lwz r0, 0xc(r29)
    cmpwi r0, 0x0
    bne L_801758E4
    li r0, 0x1
    sth r0, 0xe(r29)
L_801758E4:
    lha r3, 0xe(r29)
    mr r4, r26
    mr r5, r31
    li r6, 0x0
    bl _vfiwrite
L_801758F8:
    add r14, r14, r31
L_801758FC:
    cmpwi r30, 0x0
    ble L_80176E14
    lwz r0, 0x8(r29)
    cmpwi r0, 0x0
    bgt L_8017591C
    lhz r0, 0xc(r29)
    andi. r9, r0, 0x200
    bne L_80176E34
L_8017591C:
    li r17, 0x0
    addi r22, r22, 0x1
    stb r17, 0x32(r1)
    li r24, 0x0
    li r15, 0x0
L_80175930:
    li r25, -0x1
L_80175934:
    lbz r0, 0x0(r22)
    addi r22, r22, 0x1
    extsb r27, r0
L_80175940:
    cmpwi r27, 0x63
    beq L_80175BFC
    bgt L_801759E4
    cmpwi r27, 0x39
    bgt L_801759B8
    cmpwi r27, 0x31
    bge L_80175BA4
    cmpwi r27, 0x2b
    beq L_80175A64
    bgt L_80175994
    cmpwi r27, 0x23
    beq L_80175A6C
    bgt L_80175980
    cmpwi r27, 0x20
    beq L_80175A58
    b L_80176610
L_80175980:
    cmpwi r27, 0x27
    beq L_80175A74
    cmpwi r27, 0x2a
    beq L_80175A7C
    b L_80176610
L_80175994:
    cmpwi r27, 0x2e
    beq L_80175AE0
    bgt L_801759AC
    cmpwi r27, 0x2d
    beq L_80175AD8
    b L_80176610
L_801759AC:
    cmpwi r27, 0x30
    beq L_80175B9C
    b L_80176610
L_801759B8:
    cmpwi r27, 0x4f
    beq L_80175F34
    bgt L_801759D0
    cmpwi r27, 0x44
    beq L_80175C60
    b L_80176610
L_801759D0:
    cmpwi r27, 0x55
    beq L_801761B0
    cmpwi r27, 0x58
    beq L_80176314
    b L_80176610
L_801759E4:
    cmpwi r27, 0x6f
    beq L_80175F38
    bgt L_80175A24
    cmpwi r27, 0x69
    beq L_80175C64
    bgt L_80175A10
    cmpwi r27, 0x64
    beq L_80175C64
    cmpwi r27, 0x68
    beq L_80175BD4
    b L_80176610
L_80175A10:
    cmpwi r27, 0x6c
    beq L_80175BDC
    cmpwi r27, 0x6e
    beq L_80175DE0
    b L_80176610
L_80175A24:
    cmpwi r27, 0x73
    beq L_80176108
    bgt L_80175A44
    cmpwi r27, 0x70
    beq L_80176098
    cmpwi r27, 0x71
    beq L_80175BEC
    b L_80176610
L_80175A44:
    cmpwi r27, 0x75
    beq L_801761B4
    cmpwi r27, 0x78
    beq L_80176320
    b L_80176610
L_80175A58:
    lbz r0, 0x32(r1)
    cmpwi r0, 0x0
    bne L_80175934
L_80175A64:
    stb r27, 0x32(r1)
    b L_80175934
L_80175A6C:
    ori r24, r24, 0x1
    b L_80175934
L_80175A74:
    ori r24, r24, 0x200
    b L_80175934
L_80175A7C:
    lbz r11, 0x0(r28)
    extsb r9, r11
    addi r0, r9, 0x1
    cmplwi r0, 0x8
    bgt L_80175AA8
    lwz r0, 0x8(r28)
    slwi r9, r9, 2
    addi r11, r11, 0x1
    add r9, r0, r9
    stb r11, 0x0(r28)
    b L_80175AC8
L_80175AA8:
    cmpwi r9, 0x7
    bgt L_80175ABC
    lwz r9, 0x4(r28)
    stb r18, 0x0(r28)
    b L_80175AC0
L_80175ABC:
    lwz r9, 0x4(r28)
L_80175AC0:
    addi r0, r9, 0x4
    stw r0, 0x4(r28)
L_80175AC8:
    lwz r17, 0x0(r9)
    cmpwi r17, 0x0
    bge L_80175934
    neg r17, r17
L_80175AD8:
    ori r24, r24, 0x4
    b L_80175934
L_80175AE0:
    lbz r0, 0x0(r22)
    addi r22, r22, 0x1
    extsb r27, r0
    cmpwi r27, 0x2a
    bne L_80175B54
    lbz r11, 0x0(r28)
    extsb r9, r11
    addi r0, r9, 0x1
    cmplwi r0, 0x8
    bgt L_80175B20
    lwz r0, 0x8(r28)
    slwi r9, r9, 2
    addi r11, r11, 0x1
    add r3, r0, r9
    stb r11, 0x0(r28)
    b L_80175B40
L_80175B20:
    cmpwi r9, 0x7
    bgt L_80175B34
    lwz r3, 0x4(r28)
    stb r18, 0x0(r28)
    b L_80175B38
L_80175B34:
    lwz r3, 0x4(r28)
L_80175B38:
    addi r0, r3, 0x4
    stw r0, 0x4(r28)
L_80175B40:
    lwz r30, 0x0(r3)
    mr r25, r30
    cmpwi r25, -0x1
    bge L_80175934
    b L_80175930
L_80175B54:
    subi r0, r27, 0x30
    li r30, 0x0
    cmplwi r0, 0x9
    bgt L_80175B88
L_80175B64:
    mulli r9, r30, 0xa
    lbz r11, 0x0(r22)
    addi r22, r22, 0x1
    subi r9, r9, 0x30
    add r30, r9, r27
    extsb r27, r11
    subi r0, r27, 0x30
    cmplwi r0, 0x9
    ble L_80175B64
L_80175B88:
    mr r25, r30
    cmpwi r25, -0x1
    bge L_80175940
    li r25, -0x1
    b L_80175940
L_80175B9C:
    ori r24, r24, 0x80
    b L_80175934
L_80175BA4:
    li r30, 0x0
L_80175BA8:
    mulli r9, r30, 0xa
    lbz r11, 0x0(r22)
    addi r22, r22, 0x1
    subi r9, r9, 0x30
    add r30, r9, r27
    extsb r27, r11
    subi r0, r27, 0x30
    cmplwi r0, 0x9
    ble L_80175BA8
    mr r17, r30
    b L_80175940
L_80175BD4:
    ori r24, r24, 0x40
    b L_80175934
L_80175BDC:
    lbz r0, 0x0(r22)
    cmpwi r0, 0x6c
    bne L_80175BF4
    addi r22, r22, 0x1
L_80175BEC:
    ori r24, r24, 0x20
    b L_80175934
L_80175BF4:
    ori r24, r24, 0x10
    b L_80175934
L_80175BFC:
    lbz r11, 0x0(r28)
    addi r26, r1, 0x8
    extsb r9, r11
    addi r0, r9, 0x1
    cmplwi r0, 0x8
    bgt L_80175C2C
    lwz r0, 0x8(r28)
    slwi r9, r9, 2
    addi r11, r11, 0x1
    add r9, r0, r9
    stb r11, 0x0(r28)
    b L_80175C4C
L_80175C2C:
    cmpwi r9, 0x7
    bgt L_80175C40
    lwz r9, 0x4(r28)
    stb r18, 0x0(r28)
    b L_80175C44
L_80175C40:
    lwz r9, 0x4(r28)
L_80175C44:
    addi r0, r9, 0x4
    stw r0, 0x4(r28)
L_80175C4C:
    lbz r9, 0x3(r9)
    li r0, 0x1
    stw r0, 0x38(r1)
    stb r9, 0x8(r1)
    b L_80176628
L_80175C60:
    ori r24, r24, 0x10
L_80175C64:
    andi. r11, r24, 0x20
    beq L_80175CDC
    lbz r9, 0x0(r28)
    extsb r11, r9
    addi r0, r11, 0x2
    cmplwi r0, 0x8
    bgt L_80175CB0
    andi. r0, r9, 0x1
    beq L_80175C90
    addi r0, r9, 0x1
    stb r0, 0x0(r28)
L_80175C90:
    lbz r9, 0x0(r28)
    lwz r11, 0x8(r28)
    extsb r0, r9
    addi r9, r9, 0x2
    slwi r0, r0, 2
    stb r9, 0x0(r28)
    add r3, r11, r0
    b L_80175CD0
L_80175CB0:
    cmpwi r11, 0x7
    bgt L_80175CC4
    lwz r3, 0x4(r28)
    stb r18, 0x0(r28)
    b L_80175CC8
L_80175CC4:
    lwz r3, 0x4(r28)
L_80175CC8:
    addi r0, r3, 0x8
    stw r0, 0x4(r28)
L_80175CD0:
    lwz r30, 0x0(r3)
    lwz r31, 0x4(r3)
    b L_80175DC0
L_80175CDC:
    andi. r9, r24, 0x10
    beq L_80175D0C
    lbz r11, 0x0(r28)
    extsb r9, r11
    addi r0, r9, 0x1
    cmplwi r0, 0x8
    ble L_80175D7C
    cmpwi r9, 0x7
    bgt L_80175DA8
    lwz r9, 0x4(r28)
    stb r18, 0x0(r28)
    b L_80175DAC
L_80175D0C:
    andi. r11, r24, 0x40
    beq L_80175D68
    lbz r11, 0x0(r28)
    extsb r9, r11
    addi r0, r9, 0x1
    cmplwi r0, 0x8
    bgt L_80175D40
    lwz r0, 0x8(r28)
    slwi r9, r9, 2
    addi r11, r11, 0x1
    add r9, r0, r9
    stb r11, 0x0(r28)
    b L_80175D60
L_80175D40:
    cmpwi r9, 0x7
    bgt L_80175D54
    lwz r9, 0x4(r28)
    stb r18, 0x0(r28)
    b L_80175D58
L_80175D54:
    lwz r9, 0x4(r28)
L_80175D58:
    addi r0, r9, 0x4
    stw r0, 0x4(r28)
L_80175D60:
    lha r0, 0x2(r9)
    b L_80175DB8
L_80175D68:
    lbz r11, 0x0(r28)
    extsb r9, r11
    addi r0, r9, 0x1
    cmplwi r0, 0x8
    bgt L_80175D94
L_80175D7C:
    lwz r0, 0x8(r28)
    slwi r9, r9, 2
    addi r11, r11, 0x1
    add r9, r0, r9
    stb r11, 0x0(r28)
    b L_80175DB4
L_80175D94:
    cmpwi r9, 0x7
    bgt L_80175DA8
    lwz r9, 0x4(r28)
    stb r18, 0x0(r28)
    b L_80175DAC
L_80175DA8:
    lwz r9, 0x4(r28)
L_80175DAC:
    addi r0, r9, 0x4
    stw r0, 0x4(r28)
L_80175DB4:
    lwz r0, 0x0(r9)
L_80175DB8:
    mr r31, r0
    srawi r30, r0, 31
L_80175DC0:
    cmpwi r30, 0x0
    bge L_80175DD8
    li r0, 0x2d
    subfic r31, r31, 0x0
    subfze r30, r30
    stb r0, 0x32(r1)
L_80175DD8:
    li r0, 0x1
    b L_801764A0
L_80175DE0:
    andi. r0, r24, 0x20
    beq L_80175E4C
    lbz r11, 0x0(r28)
    extsb r9, r11
    addi r0, r9, 0x1
    cmplwi r0, 0x8
    bgt L_80175E14
    lwz r0, 0x8(r28)
    slwi r9, r9, 2
    addi r11, r11, 0x1
    add r8, r0, r9
    stb r11, 0x0(r28)
    b L_80175E34
L_80175E14:
    cmpwi r9, 0x7
    bgt L_80175E28
    lwz r8, 0x4(r28)
    stb r18, 0x0(r28)
    b L_80175E2C
L_80175E28:
    lwz r8, 0x4(r28)
L_80175E2C:
    addi r0, r8, 0x4
    stw r0, 0x4(r28)
L_80175E34:
    mr r10, r14
    lwz r11, 0x0(r8)
    srawi r9, r14, 31
    stw r9, 0x0(r11)
    stw r10, 0x4(r11)
    b L_80175820
L_80175E4C:
    andi. r9, r24, 0x10
    beq L_80175E7C
    lbz r11, 0x0(r28)
    extsb r9, r11
    addi r0, r9, 0x1
    cmplwi r0, 0x8
    ble L_80175EF0
    cmpwi r9, 0x7
    bgt L_80175F1C
    lwz r9, 0x4(r28)
    stb r18, 0x0(r28)
    b L_80175F20
L_80175E7C:
    andi. r11, r24, 0x40
    beq L_80175EDC
    lbz r11, 0x0(r28)
    extsb r9, r11
    addi r0, r9, 0x1
    cmplwi r0, 0x8
    bgt L_80175EB0
    lwz r0, 0x8(r28)
    slwi r9, r9, 2
    addi r11, r11, 0x1
    add r9, r0, r9
    stb r11, 0x0(r28)
    b L_80175ED0
L_80175EB0:
    cmpwi r9, 0x7
    bgt L_80175EC4
    lwz r9, 0x4(r28)
    stb r18, 0x0(r28)
    b L_80175EC8
L_80175EC4:
    lwz r9, 0x4(r28)
L_80175EC8:
    addi r0, r9, 0x4
    stw r0, 0x4(r28)
L_80175ED0:
    lwz r9, 0x0(r9)
    sth r14, 0x0(r9)
    b L_80175820
L_80175EDC:
    lbz r11, 0x0(r28)
    extsb r9, r11
    addi r0, r9, 0x1
    cmplwi r0, 0x8
    bgt L_80175F08
L_80175EF0:
    lwz r0, 0x8(r28)
    slwi r9, r9, 2
    addi r11, r11, 0x1
    add r9, r0, r9
    stb r11, 0x0(r28)
    b L_80175F28
L_80175F08:
    cmpwi r9, 0x7
    bgt L_80175F1C
    lwz r9, 0x4(r28)
    stb r18, 0x0(r28)
    b L_80175F20
L_80175F1C:
    lwz r9, 0x4(r28)
L_80175F20:
    addi r0, r9, 0x4
    stw r0, 0x4(r28)
L_80175F28:
    lwz r9, 0x0(r9)
    stw r14, 0x0(r9)
    b L_80175820
L_80175F34:
    ori r24, r24, 0x10
L_80175F38:
    andi. r0, r24, 0x20
    beq L_80175FB0
    lbz r9, 0x0(r28)
    extsb r11, r9
    addi r0, r11, 0x2
    cmplwi r0, 0x8
    bgt L_80175F84
    andi. r11, r9, 0x1
    beq L_80175F64
    addi r0, r9, 0x1
    stb r0, 0x0(r28)
L_80175F64:
    lbz r9, 0x0(r28)
    lwz r11, 0x8(r28)
    extsb r0, r9
    addi r9, r9, 0x2
    slwi r0, r0, 2
    stb r9, 0x0(r28)
    add r3, r11, r0
    b L_80175FA4
L_80175F84:
    cmpwi r11, 0x7
    bgt L_80175F98
    lwz r3, 0x4(r28)
    stb r18, 0x0(r28)
    b L_80175F9C
L_80175F98:
    lwz r3, 0x4(r28)
L_80175F9C:
    addi r0, r3, 0x8
    stw r0, 0x4(r28)
L_80175FA4:
    lwz r30, 0x0(r3)
    lwz r31, 0x4(r3)
    b L_80176090
L_80175FB0:
    andi. r0, r24, 0x10
    beq L_80175FE0
    lbz r11, 0x0(r28)
    extsb r9, r11
    addi r0, r9, 0x1
    cmplwi r0, 0x8
    ble L_80176050
    cmpwi r9, 0x7
    bgt L_8017607C
    lwz r9, 0x4(r28)
    stb r18, 0x0(r28)
    b L_80176080
L_80175FE0:
    andi. r9, r24, 0x40
    beq L_8017603C
    lbz r11, 0x0(r28)
    extsb r9, r11
    addi r0, r9, 0x1
    cmplwi r0, 0x8
    bgt L_80176014
    lwz r0, 0x8(r28)
    slwi r9, r9, 2
    addi r11, r11, 0x1
    add r9, r0, r9
    stb r11, 0x0(r28)
    b L_80176034
L_80176014:
    cmpwi r9, 0x7
    bgt L_80176028
    lwz r9, 0x4(r28)
    stb r18, 0x0(r28)
    b L_8017602C
L_80176028:
    lwz r9, 0x4(r28)
L_8017602C:
    addi r0, r9, 0x4
    stw r0, 0x4(r28)
L_80176034:
    lhz r31, 0x2(r9)
    b L_8017608C
L_8017603C:
    lbz r11, 0x0(r28)
    extsb r9, r11
    addi r0, r9, 0x1
    cmplwi r0, 0x8
    bgt L_80176068
L_80176050:
    lwz r0, 0x8(r28)
    slwi r9, r9, 2
    addi r11, r11, 0x1
    add r9, r0, r9
    stb r11, 0x0(r28)
    b L_80176088
L_80176068:
    cmpwi r9, 0x7
    bgt L_8017607C
    lwz r9, 0x4(r28)
    stb r18, 0x0(r28)
    b L_80176080
L_8017607C:
    lwz r9, 0x4(r28)
L_80176080:
    addi r0, r9, 0x4
    stw r0, 0x4(r28)
L_80176088:
    lwz r31, 0x0(r9)
L_8017608C:
    li r30, 0x0
L_80176090:
    li r0, 0x0
    b L_8017649C
L_80176098:
    lbz r11, 0x0(r28)
    extsb r9, r11
    addi r0, r9, 0x1
    cmplwi r0, 0x8
    bgt L_801760C4
    lwz r0, 0x8(r28)
    slwi r9, r9, 2
    addi r11, r11, 0x1
    add r10, r0, r9
    stb r11, 0x0(r28)
    b L_801760E4
L_801760C4:
    cmpwi r9, 0x7
    bgt L_801760D8
    lwz r10, 0x4(r28)
    stb r18, 0x0(r28)
    b L_801760DC
L_801760D8:
    lwz r10, 0x4(r28)
L_801760DC:
    addi r0, r10, 0x4
    stw r0, 0x4(r28)
L_801760E4:
    lwz r31, 0x0(r10)
    lis r9, lbl_8049C630@ha
    addi r9, r9, lbl_8049C630@l
    li r0, 0x2
    stw r9, 0x40(r1)
    ori r24, r24, 0x2
    li r30, 0x0
    li r27, 0x78
    b L_8017649C
L_80176108:
    lbz r11, 0x0(r28)
    extsb r9, r11
    addi r0, r9, 0x1
    cmplwi r0, 0x8
    bgt L_80176134
    lwz r0, 0x8(r28)
    slwi r9, r9, 2
    addi r11, r11, 0x1
    add r3, r0, r9
    stb r11, 0x0(r28)
    b L_80176154
L_80176134:
    cmpwi r9, 0x7
    bgt L_80176148
    lwz r3, 0x4(r28)
    stb r18, 0x0(r28)
    b L_8017614C
L_80176148:
    lwz r3, 0x4(r28)
L_8017614C:
    addi r0, r3, 0x4
    stw r0, 0x4(r28)
L_80176154:
    lwz r26, 0x0(r3)
    cmpwi r26, 0x0
    bne L_80176168
    lis r9, lbl_8049C644@ha
    addi r26, r9, lbl_8049C644@l
L_80176168:
    cmpwi r25, 0x0
    blt L_801761A0
    mr r3, r26
    li r4, 0x0
    mr r5, r25
    bl memchr
    mr. r3, r3
    beq L_80176198
    subf r0, r26, r3
    cmpw r0, r25
    stw r0, 0x38(r1)
    ble L_80176628
L_80176198:
    stw r25, 0x38(r1)
    b L_80176628
L_801761A0:
    mr r3, r26
    bl strlen
    stw r3, 0x38(r1)
    b L_80176628
L_801761B0:
    ori r24, r24, 0x10
L_801761B4:
    andi. r0, r24, 0x20
    beq L_8017622C
    lbz r9, 0x0(r28)
    extsb r11, r9
    addi r0, r11, 0x2
    cmplwi r0, 0x8
    bgt L_80176200
    andi. r11, r9, 0x1
    beq L_801761E0
    addi r0, r9, 0x1
    stb r0, 0x0(r28)
L_801761E0:
    lbz r9, 0x0(r28)
    lwz r11, 0x8(r28)
    extsb r0, r9
    addi r9, r9, 0x2
    slwi r0, r0, 2
    stb r9, 0x0(r28)
    add r3, r11, r0
    b L_80176220
L_80176200:
    cmpwi r11, 0x7
    bgt L_80176214
    lwz r3, 0x4(r28)
    stb r18, 0x0(r28)
    b L_80176218
L_80176214:
    lwz r3, 0x4(r28)
L_80176218:
    addi r0, r3, 0x8
    stw r0, 0x4(r28)
L_80176220:
    lwz r30, 0x0(r3)
    lwz r31, 0x4(r3)
    b L_8017630C
L_8017622C:
    andi. r0, r24, 0x10
    beq L_8017625C
    lbz r11, 0x0(r28)
    extsb r9, r11
    addi r0, r9, 0x1
    cmplwi r0, 0x8
    ble L_801762CC
    cmpwi r9, 0x7
    bgt L_801762F8
    lwz r9, 0x4(r28)
    stb r18, 0x0(r28)
    b L_801762FC
L_8017625C:
    andi. r9, r24, 0x40
    beq L_801762B8
    lbz r11, 0x0(r28)
    extsb r9, r11
    addi r0, r9, 0x1
    cmplwi r0, 0x8
    bgt L_80176290
    lwz r0, 0x8(r28)
    slwi r9, r9, 2
    addi r11, r11, 0x1
    add r9, r0, r9
    stb r11, 0x0(r28)
    b L_801762B0
L_80176290:
    cmpwi r9, 0x7
    bgt L_801762A4
    lwz r9, 0x4(r28)
    stb r18, 0x0(r28)
    b L_801762A8
L_801762A4:
    lwz r9, 0x4(r28)
L_801762A8:
    addi r0, r9, 0x4
    stw r0, 0x4(r28)
L_801762B0:
    lhz r31, 0x2(r9)
    b L_80176308
L_801762B8:
    lbz r11, 0x0(r28)
    extsb r9, r11
    addi r0, r9, 0x1
    cmplwi r0, 0x8
    bgt L_801762E4
L_801762CC:
    lwz r0, 0x8(r28)
    slwi r9, r9, 2
    addi r11, r11, 0x1
    add r9, r0, r9
    stb r11, 0x0(r28)
    b L_80176304
L_801762E4:
    cmpwi r9, 0x7
    bgt L_801762F8
    lwz r9, 0x4(r28)
    stb r18, 0x0(r28)
    b L_801762FC
L_801762F8:
    lwz r9, 0x4(r28)
L_801762FC:
    addi r0, r9, 0x4
    stw r0, 0x4(r28)
L_80176304:
    lwz r31, 0x0(r9)
L_80176308:
    li r30, 0x0
L_8017630C:
    li r0, 0x1
    b L_8017649C
L_80176314:
    lis r9, lbl_8049C64C@ha
    addi r9, r9, lbl_8049C64C@l
    b L_80176328
L_80176320:
    lis r9, lbl_8049C630@ha
    addi r9, r9, lbl_8049C630@l
L_80176328:
    stw r9, 0x40(r1)
    andi. r11, r24, 0x20
    beq L_801763A4
    lbz r9, 0x0(r28)
    extsb r11, r9
    addi r0, r11, 0x2
    cmplwi r0, 0x8
    bgt L_80176378
    andi. r0, r9, 0x1
    beq L_80176358
    addi r0, r9, 0x1
    stb r0, 0x0(r28)
L_80176358:
    lbz r9, 0x0(r28)
    lwz r11, 0x8(r28)
    extsb r0, r9
    addi r9, r9, 0x2
    slwi r0, r0, 2
    stb r9, 0x0(r28)
    add r3, r11, r0
    b L_80176398
L_80176378:
    cmpwi r11, 0x7
    bgt L_8017638C
    lwz r3, 0x4(r28)
    stb r18, 0x0(r28)
    b L_80176390
L_8017638C:
    lwz r3, 0x4(r28)
L_80176390:
    addi r0, r3, 0x8
    stw r0, 0x4(r28)
L_80176398:
    lwz r30, 0x0(r3)
    lwz r31, 0x4(r3)
    b L_80176484
L_801763A4:
    andi. r9, r24, 0x10
    beq L_801763D4
    lbz r11, 0x0(r28)
    extsb r9, r11
    addi r0, r9, 0x1
    cmplwi r0, 0x8
    ble L_80176444
    cmpwi r9, 0x7
    bgt L_80176470
    lwz r9, 0x4(r28)
    stb r18, 0x0(r28)
    b L_80176474
L_801763D4:
    andi. r11, r24, 0x40
    beq L_80176430
    lbz r11, 0x0(r28)
    extsb r9, r11
    addi r0, r9, 0x1
    cmplwi r0, 0x8
    bgt L_80176408
    lwz r0, 0x8(r28)
    slwi r9, r9, 2
    addi r11, r11, 0x1
    add r9, r0, r9
    stb r11, 0x0(r28)
    b L_80176428
L_80176408:
    cmpwi r9, 0x7
    bgt L_8017641C
    lwz r9, 0x4(r28)
    stb r18, 0x0(r28)
    b L_80176420
L_8017641C:
    lwz r9, 0x4(r28)
L_80176420:
    addi r0, r9, 0x4
    stw r0, 0x4(r28)
L_80176428:
    lhz r31, 0x2(r9)
    b L_80176480
L_80176430:
    lbz r11, 0x0(r28)
    extsb r9, r11
    addi r0, r9, 0x1
    cmplwi r0, 0x8
    bgt L_8017645C
L_80176444:
    lwz r0, 0x8(r28)
    slwi r9, r9, 2
    addi r11, r11, 0x1
    add r9, r0, r9
    stb r11, 0x0(r28)
    b L_8017647C
L_8017645C:
    cmpwi r9, 0x7
    bgt L_80176470
    lwz r9, 0x4(r28)
    stb r18, 0x0(r28)
    b L_80176474
L_80176470:
    lwz r9, 0x4(r28)
L_80176474:
    addi r0, r9, 0x4
    stw r0, 0x4(r28)
L_8017647C:
    lwz r31, 0x0(r9)
L_80176480:
    li r30, 0x0
L_80176484:
    li r0, 0x2
    andi. r9, r24, 0x1
    beq L_8017649C
    or. r11, r30, r31
    beq L_8017649C
    ori r24, r24, 0x2
L_8017649C:
    stb r16, 0x32(r1)
L_801764A0:
    mr. r15, r25
    mcrf cr7, cr0
    blt cr7, L_801764B0
    rlwinm r24, r24, 0, 25, 23
L_801764B0:
    lwz r26, 0x44(r1)
    or. r9, r30, r31
    bne L_801764C4
    cmpwi cr4, r0, 0x1
    beq cr7, L_801765D8
L_801764C4:
    cmpwi cr4, r0, 0x1
    beq cr4, L_80176568
    cmplwi r0, 0x1
    blt L_801764E0
    cmpwi r0, 0x2
    beq L_8017658C
    b L_801765C0
L_801764E0:
    srwi r0, r31, 3
    slwi r8, r30, 29
    or r10, r8, r0
    clrlwi r11, r31, 29
    srwi r9, r30, 3
    addi r11, r11, 0x30
    mr r30, r9
    mr r31, r10
    stbu r11, -0x1(r26)
    or. r0, r30, r31
    bne L_801764E0
    andi. r9, r24, 0x1
    beq L_801765D8
    cmpwi r11, 0x30
    beq L_801765D8
    li r0, 0x30
    stbu r0, -0x1(r26)
    b L_801765D8
L_80176528:
    li r5, 0x0
    mr r3, r30
    mr r4, r31
    li r6, 0xa
    crclr 6
    bl __umoddi3
    addi r0, r4, 0x30
    li r5, 0x0
    mr r3, r30
    mr r4, r31
    stbu r0, -0x1(r26)
    li r6, 0xa
    crclr 6
    bl __udivdi3
    mr r30, r3
    mr r31, r4
L_80176568:
    cmplwi r30, 0x0
    bgt L_80176528
    cmpwi r30, 0x0
    bne L_80176580
    cmplwi r31, 0x9
    bgt L_80176528
L_80176580:
    addi r0, r31, 0x30
    stbu r0, -0x1(r26)
    b L_801765D8
L_8017658C:
    srwi r11, r31, 4
    slwi r7, r30, 28
    or r10, r7, r11
    clrlwi r0, r31, 28
    lwz r11, 0x40(r1)
    srwi r9, r30, 4
    mr r30, r9
    mr r31, r10
    lbzx r8, r11, r0
    or. r0, r30, r31
    stbu r8, -0x1(r26)
    bne L_8017658C
    b L_801765D8
L_801765C0:
    lis r9, lbl_8049C660@ha
    addi r26, r9, lbl_8049C660@l
    mr r3, r26
    bl strlen
    stw r3, 0x38(r1)
    b L_8017662C
L_801765D8:
    bne cr4, L_80176600
    andi. r0, r24, 0x200
    beq L_80176600
    lwz r5, 0x44(r1)
    mr r4, r26
    addi r3, r1, 0x8
    addi r6, r1, 0x38
    bl __group_digits
    mr r26, r3
    b L_8017662C
L_80176600:
    subf r9, r26, r1
    addi r9, r9, 0x30
    stw r9, 0x38(r1)
    b L_8017662C
L_80176610:
    cmpwi r27, 0x0
    beq L_80176E14
    li r0, 0x1
    stb r27, 0x8(r1)
    stw r0, 0x38(r1)
    addi r26, r1, 0x8
L_80176628:
    stb r16, 0x32(r1)
L_8017662C:
    lwz r23, 0x38(r1)
    cmpw r23, r15
    bge L_8017663C
    mr r23, r15
L_8017663C:
    lbz r0, 0x32(r1)
    cmpwi r0, 0x0
    beq L_80176650
    addi r23, r23, 0x1
    b L_8017665C
L_80176650:
    andi. r0, r24, 0x2
    beq L_8017665C
    addi r23, r23, 0x2
L_8017665C:
    andi. r9, r24, 0x84
    bne L_801767D0
    subf. r30, r23, r17
    ble L_801767D0
    cmpwi r30, 0x10
    lis r25, lbl_8049C610@ha
    ble L_80176738
    lis r19, lbl_8049C610@ha
    addi r31, r25, lbl_8049C610@l
    li r20, 0x0
    li r21, 0x1
L_80176688:
    lhz r0, 0xc(r29)
    andi. r11, r0, 0x200
    beq L_80176708
    lwz r5, 0x8(r29)
    cmpwi r5, 0x10
    ble L_801766E0
    lwz r11, lbl_8049C610@l(r19)
    lwz r10, 0x4(r31)
    lwz r8, 0x8(r31)
    lwz r0, 0xc(r31)
    lwz r9, 0x0(r29)
    stw r0, 0xc(r9)
    stw r11, 0x0(r9)
    stw r10, 0x4(r9)
    stw r8, 0x8(r9)
    lwz r11, 0x0(r29)
    lwz r9, 0x8(r29)
    addi r11, r11, 0x10
    subi r9, r9, 0x10
    stw r11, 0x0(r29)
    stw r9, 0x8(r29)
    b L_8017672C
L_801766E0:
    lwz r3, 0x0(r29)
    addi r4, r25, lbl_8049C610@l
    crclr 6
    bl memcpy
    lwz r0, 0x0(r29)
    lwz r9, 0x8(r29)
    stw r20, 0x8(r29)
    add r0, r0, r9
    stw r0, 0x0(r29)
    b L_8017672C
L_80176708:
    lwz r0, 0xc(r29)
    cmpwi r0, 0x0
    bne L_80176718
    sth r21, 0xe(r29)
L_80176718:
    lha r3, 0xe(r29)
    addi r4, r25, lbl_8049C610@l
    li r5, 0x10
    li r6, 0x0
    bl _vfiwrite
L_8017672C:
    subi r30, r30, 0x10
    cmpwi r30, 0x10
    bgt L_80176688
L_80176738:
    lhz r0, 0xc(r29)
    andi. r9, r0, 0x200
    beq L_801767A8
    lwz r5, 0x8(r29)
    cmpw r5, r30
    ble L_80176780
    lwz r3, 0x0(r29)
    addi r4, r25, lbl_8049C610@l
    mr r5, r30
    crclr 6
    bl memcpy
    lwz r0, 0x0(r29)
    lwz r9, 0x8(r29)
    add r0, r0, r30
    subf r9, r30, r9
    stw r0, 0x0(r29)
    stw r9, 0x8(r29)
    b L_801767D0
L_80176780:
    lwz r3, 0x0(r29)
    addi r4, r25, lbl_8049C610@l
    crclr 6
    bl memcpy
    lwz r0, 0x0(r29)
    lwz r9, 0x8(r29)
    stw r16, 0x8(r29)
    add r0, r0, r9
    stw r0, 0x0(r29)
    b L_801767D0
L_801767A8:
    lwz r0, 0xc(r29)
    cmpwi r0, 0x0
    bne L_801767BC
    li r0, 0x1
    sth r0, 0xe(r29)
L_801767BC:
    lha r3, 0xe(r29)
    addi r4, r25, lbl_8049C610@l
    mr r5, r30
    li r6, 0x0
    bl _vfiwrite
L_801767D0:
    lbz r11, 0x32(r1)
    extsb r30, r11
    cmpwi r30, 0x0
    beq L_80176860
    lhz r0, 0xc(r29)
    andi. r9, r0, 0x200
    beq L_80176834
    lwz r5, 0x8(r29)
    cmpwi r5, 0x1
    ble L_80176814
    lwz r9, 0x0(r29)
    stb r11, 0x0(r9)
    lwz r11, 0x0(r29)
    lwz r9, 0x8(r29)
    addi r11, r11, 0x1
    subi r9, r9, 0x1
    b L_801768A4
L_80176814:
    lwz r3, 0x0(r29)
    addi r4, r1, 0x32
    crclr 6
    bl memcpy
    lwz r0, 0x0(r29)
    lwz r9, 0x8(r29)
    stw r16, 0x8(r29)
    b L_801768CC
L_80176834:
    lwz r0, 0xc(r29)
    cmpwi r0, 0x0
    bne L_80176848
    li r0, 0x1
    sth r0, 0xe(r29)
L_80176848:
    lha r3, 0xe(r29)
    addi r4, r1, 0x32
    li r5, 0x1
    li r6, 0x0
    bl _vfiwrite
    b L_80176900
L_80176860:
    andi. r0, r24, 0x2
    beq L_80176900
    lhz r9, 0xc(r29)
    clrlwi r0, r27, 24
    ori r0, r0, 0x3000
    sth r0, 0x3c(r1)
    andi. r11, r9, 0x200
    beq L_801768D8
    lwz r5, 0x8(r29)
    cmpwi r5, 0x2
    ble L_801768B0
    lwz r9, 0x0(r29)
    sth r0, 0x0(r9)
    lwz r11, 0x0(r29)
    lwz r9, 0x8(r29)
    addi r11, r11, 0x2
    subi r9, r9, 0x2
L_801768A4:
    stw r11, 0x0(r29)
    stw r9, 0x8(r29)
    b L_80176900
L_801768B0:
    lwz r3, 0x0(r29)
    addi r4, r1, 0x3c
    crclr 6
    bl memcpy
    lwz r0, 0x0(r29)
    lwz r9, 0x8(r29)
    stw r30, 0x8(r29)
L_801768CC:
    add r0, r0, r9
    stw r0, 0x0(r29)
    b L_80176900
L_801768D8:
    lwz r0, 0xc(r29)
    cmpwi r0, 0x0
    bne L_801768EC
    li r0, 0x1
    sth r0, 0xe(r29)
L_801768EC:
    lha r3, 0xe(r29)
    addi r4, r1, 0x3c
    li r5, 0x2
    li r6, 0x0
    bl _vfiwrite
L_80176900:
    andi. r0, r24, 0x84
    cmpwi r0, 0x80
    bne L_80176A78
    subf. r30, r23, r17
    ble L_80176A78
    cmpwi r30, 0x10
    lis r31, lbl_8049C620@ha
    ble L_801769E0
    lis r20, lbl_8049C620@ha
    addi r27, r31, lbl_8049C620@l
    li r21, 0x0
    li r25, 0x1
L_80176930:
    lhz r0, 0xc(r29)
    andi. r9, r0, 0x200
    beq L_801769B0
    lwz r5, 0x8(r29)
    cmpwi r5, 0x10
    ble L_80176988
    lwz r11, lbl_8049C620@l(r20)
    lwz r10, 0x4(r27)
    lwz r8, 0x8(r27)
    lwz r0, 0xc(r27)
    lwz r9, 0x0(r29)
    stw r0, 0xc(r9)
    stw r11, 0x0(r9)
    stw r10, 0x4(r9)
    stw r8, 0x8(r9)
    lwz r11, 0x0(r29)
    lwz r9, 0x8(r29)
    addi r11, r11, 0x10
    subi r9, r9, 0x10
    stw r11, 0x0(r29)
    stw r9, 0x8(r29)
    b L_801769D4
L_80176988:
    lwz r3, 0x0(r29)
    addi r4, r31, lbl_8049C620@l
    crclr 6
    bl memcpy
    lwz r0, 0x0(r29)
    lwz r9, 0x8(r29)
    stw r21, 0x8(r29)
    add r0, r0, r9
    stw r0, 0x0(r29)
    b L_801769D4
L_801769B0:
    lwz r0, 0xc(r29)
    cmpwi r0, 0x0
    bne L_801769C0
    sth r25, 0xe(r29)
L_801769C0:
    lha r3, 0xe(r29)
    addi r4, r31, lbl_8049C620@l
    li r5, 0x10
    li r6, 0x0
    bl _vfiwrite
L_801769D4:
    subi r30, r30, 0x10
    cmpwi r30, 0x10
    bgt L_80176930
L_801769E0:
    lhz r0, 0xc(r29)
    andi. r9, r0, 0x200
    beq L_80176A50
    lwz r5, 0x8(r29)
    cmpw r5, r30
    ble L_80176A28
    lwz r3, 0x0(r29)
    addi r4, r31, lbl_8049C620@l
    mr r5, r30
    crclr 6
    bl memcpy
    lwz r0, 0x0(r29)
    lwz r9, 0x8(r29)
    add r0, r0, r30
    subf r9, r30, r9
    stw r0, 0x0(r29)
    stw r9, 0x8(r29)
    b L_80176A78
L_80176A28:
    lwz r3, 0x0(r29)
    addi r4, r31, lbl_8049C620@l
    crclr 6
    bl memcpy
    lwz r0, 0x0(r29)
    lwz r9, 0x8(r29)
    stw r16, 0x8(r29)
    add r0, r0, r9
    stw r0, 0x0(r29)
    b L_80176A78
L_80176A50:
    lwz r0, 0xc(r29)
    cmpwi r0, 0x0
    bne L_80176A64
    li r0, 0x1
    sth r0, 0xe(r29)
L_80176A64:
    lha r3, 0xe(r29)
    addi r4, r31, lbl_8049C620@l
    mr r5, r30
    li r6, 0x0
    bl _vfiwrite
L_80176A78:
    lwz r0, 0x38(r1)
    subf. r30, r0, r15
    ble L_80176BE8
    cmpwi r30, 0x10
    lis r31, lbl_8049C620@ha
    ble L_80176B50
    lis r20, lbl_8049C620@ha
    addi r27, r31, lbl_8049C620@l
    li r21, 0x0
    li r25, 0x1
L_80176AA0:
    lhz r0, 0xc(r29)
    andi. r9, r0, 0x200
    beq L_80176B20
    lwz r5, 0x8(r29)
    cmpwi r5, 0x10
    ble L_80176AF8
    lwz r11, lbl_8049C620@l(r20)
    lwz r10, 0x4(r27)
    lwz r8, 0x8(r27)
    lwz r0, 0xc(r27)
    lwz r9, 0x0(r29)
    stw r0, 0xc(r9)
    stw r11, 0x0(r9)
    stw r10, 0x4(r9)
    stw r8, 0x8(r9)
    lwz r11, 0x0(r29)
    lwz r9, 0x8(r29)
    addi r11, r11, 0x10
    subi r9, r9, 0x10
    stw r11, 0x0(r29)
    stw r9, 0x8(r29)
    b L_80176B44
L_80176AF8:
    lwz r3, 0x0(r29)
    addi r4, r31, lbl_8049C620@l
    crclr 6
    bl memcpy
    lwz r0, 0x0(r29)
    lwz r9, 0x8(r29)
    stw r21, 0x8(r29)
    add r0, r0, r9
    stw r0, 0x0(r29)
    b L_80176B44
L_80176B20:
    lwz r0, 0xc(r29)
    cmpwi r0, 0x0
    bne L_80176B30
    sth r25, 0xe(r29)
L_80176B30:
    lha r3, 0xe(r29)
    addi r4, r31, lbl_8049C620@l
    li r5, 0x10
    li r6, 0x0
    bl _vfiwrite
L_80176B44:
    subi r30, r30, 0x10
    cmpwi r30, 0x10
    bgt L_80176AA0
L_80176B50:
    lhz r0, 0xc(r29)
    andi. r9, r0, 0x200
    beq L_80176BC0
    lwz r5, 0x8(r29)
    cmpw r5, r30
    ble L_80176B98
    lwz r3, 0x0(r29)
    addi r4, r31, lbl_8049C620@l
    mr r5, r30
    crclr 6
    bl memcpy
    lwz r0, 0x0(r29)
    lwz r9, 0x8(r29)
    add r0, r0, r30
    subf r9, r30, r9
    stw r0, 0x0(r29)
    stw r9, 0x8(r29)
    b L_80176BE8
L_80176B98:
    lwz r3, 0x0(r29)
    addi r4, r31, lbl_8049C620@l
    crclr 6
    bl memcpy
    lwz r0, 0x0(r29)
    lwz r9, 0x8(r29)
    stw r16, 0x8(r29)
    add r0, r0, r9
    stw r0, 0x0(r29)
    b L_80176BE8
L_80176BC0:
    lwz r0, 0xc(r29)
    cmpwi r0, 0x0
    bne L_80176BD4
    li r0, 0x1
    sth r0, 0xe(r29)
L_80176BD4:
    lha r3, 0xe(r29)
    addi r4, r31, lbl_8049C620@l
    mr r5, r30
    li r6, 0x0
    bl _vfiwrite
L_80176BE8:
    lhz r0, 0xc(r29)
    andi. r9, r0, 0x200
    beq L_80176C60
    lwz r0, 0x8(r29)
    lwz r5, 0x38(r1)
    cmpw r0, r5
    ble L_80176C34
    lwz r3, 0x0(r29)
    mr r4, r26
    crclr 6
    bl memcpy
    lwz r11, 0x38(r1)
    lwz r0, 0x0(r29)
    lwz r9, 0x8(r29)
    add r0, r0, r11
    subf r9, r11, r9
    stw r0, 0x0(r29)
    stw r9, 0x8(r29)
    b L_80176C88
L_80176C34:
    lwz r3, 0x0(r29)
    mr r5, r0
    mr r4, r26
    crclr 6
    bl memcpy
    lwz r0, 0x0(r29)
    lwz r9, 0x8(r29)
    stw r16, 0x8(r29)
    add r0, r0, r9
    stw r0, 0x0(r29)
    b L_80176C88
L_80176C60:
    lwz r0, 0xc(r29)
    cmpwi r0, 0x0
    bne L_80176C74
    li r0, 0x1
    sth r0, 0xe(r29)
L_80176C74:
    lha r3, 0xe(r29)
    mr r4, r26
    lwz r5, 0x38(r1)
    li r6, 0x0
    bl _vfiwrite
L_80176C88:
    andi. r0, r24, 0x4
    beq L_80176DFC
    subf. r30, r23, r17
    ble L_80176DFC
    cmpwi r30, 0x10
    lis r25, lbl_8049C610@ha
    ble L_80176D64
    lis r21, lbl_8049C610@ha
    addi r27, r25, lbl_8049C610@l
    li r24, 0x0
    li r26, 0x1
L_80176CB4:
    lhz r0, 0xc(r29)
    andi. r9, r0, 0x200
    beq L_80176D34
    lwz r5, 0x8(r29)
    cmpwi r5, 0x10
    ble L_80176D0C
    lwz r11, lbl_8049C610@l(r21)
    lwz r10, 0x4(r27)
    lwz r8, 0x8(r27)
    lwz r0, 0xc(r27)
    lwz r9, 0x0(r29)
    stw r0, 0xc(r9)
    stw r11, 0x0(r9)
    stw r10, 0x4(r9)
    stw r8, 0x8(r9)
    lwz r11, 0x0(r29)
    lwz r9, 0x8(r29)
    addi r11, r11, 0x10
    subi r9, r9, 0x10
    stw r11, 0x0(r29)
    stw r9, 0x8(r29)
    b L_80176D58
L_80176D0C:
    lwz r3, 0x0(r29)
    addi r4, r25, lbl_8049C610@l
    crclr 6
    bl memcpy
    lwz r0, 0x0(r29)
    lwz r9, 0x8(r29)
    stw r24, 0x8(r29)
    add r0, r0, r9
    stw r0, 0x0(r29)
    b L_80176D58
L_80176D34:
    lwz r0, 0xc(r29)
    cmpwi r0, 0x0
    bne L_80176D44
    sth r26, 0xe(r29)
L_80176D44:
    lha r3, 0xe(r29)
    addi r4, r25, lbl_8049C610@l
    li r5, 0x10
    li r6, 0x0
    bl _vfiwrite
L_80176D58:
    subi r30, r30, 0x10
    cmpwi r30, 0x10
    bgt L_80176CB4
L_80176D64:
    lhz r0, 0xc(r29)
    andi. r9, r0, 0x200
    beq L_80176DD4
    lwz r5, 0x8(r29)
    cmpw r5, r30
    ble L_80176DAC
    lwz r3, 0x0(r29)
    addi r4, r25, lbl_8049C610@l
    mr r5, r30
    crclr 6
    bl memcpy
    lwz r0, 0x0(r29)
    lwz r9, 0x8(r29)
    add r0, r0, r30
    subf r9, r30, r9
    stw r0, 0x0(r29)
    stw r9, 0x8(r29)
    b L_80176DFC
L_80176DAC:
    lwz r3, 0x0(r29)
    addi r4, r25, lbl_8049C610@l
    crclr 6
    bl memcpy
    lwz r0, 0x0(r29)
    lwz r9, 0x8(r29)
    stw r16, 0x8(r29)
    add r0, r0, r9
    stw r0, 0x0(r29)
    b L_80176DFC
L_80176DD4:
    lwz r0, 0xc(r29)
    cmpwi r0, 0x0
    bne L_80176DE8
    li r0, 0x1
    sth r0, 0xe(r29)
L_80176DE8:
    lha r3, 0xe(r29)
    addi r4, r25, lbl_8049C610@l
    mr r5, r30
    li r6, 0x0
    bl _vfiwrite
L_80176DFC:
    mr r0, r23
    cmpw r0, r17
    bge L_80176E0C
    mr r0, r17
L_80176E0C:
    add r14, r14, r0
    b L_80175820
L_80176E14:
    lhz r0, 0xc(r29)
    andi. r9, r0, 0x200
    bne L_80176E34
    lha r3, 0xe(r29)
    li r4, 0x0
    li r5, 0x0
    li r6, 0x1
    bl _vfiwrite
L_80176E34:
    mr r3, r14
    lwz r0, 0xa4(r1)
    lwz r12, 0x54(r1)
    mtlr r0
    lmw r14, 0x58(r1)
    mtcrf 8, r12
    addi r1, r1, 0xa0
    blr
    // clang-format on
}
