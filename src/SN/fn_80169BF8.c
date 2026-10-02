extern char lbl_80572560[];
extern char lbl_80573680[];
extern char lbl_804CFD6C[];
extern char lbl_804CFC70[];
extern char lbl_804CFD50[];
extern char _SDA2_BASE_[];
extern char _SDA_BASE_[];
void fn_801698E0(void);
void fn_80169720(void);
void fn_80169304(void);
void fn_8016BC70(void);
void fn_801694B8(void);
void fn_8016948C(void);
void fn_801693DC(void);
void fn_8016A7E0(void);
void fn_8016A440(void);
void fn_80168BB0(void);
void OSReport(void);
void lbl_80169CCC(void);

asm void fn_80169BF8(void)
{
    // clang-format off
    nofralloc
    lis     r31, lbl_80573680@h
    ori     r31, r31, lbl_80573680@l
    stw     r0, 0x0(r31)
    stw     r1, 0x8(r31)
    stw     r2, 0x10(r31)
    stw     r3, 0x18(r31)
    stw     r4, 0x20(r31)
    stw     r5, 0x28(r31)
    stw     r6, 0x30(r31)
    stw     r7, 0x38(r31)
    stw     r8, 0x40(r31)
    stw     r9, 0x48(r31)
    stw     r10, 0x50(r31)
    stw     r11, 0x58(r31)
    stw     r12, 0x60(r31)
    stw     r13, 0x68(r31)
    stw     r14, 0x70(r31)
    stw     r15, 0x78(r31)
    stw     r16, 0x80(r31)
    stw     r17, 0x88(r31)
    stw     r18, 0x90(r31)
    stw     r19, 0x98(r31)
    stw     r20, 0xa0(r31)
    stw     r21, 0xa8(r31)
    stw     r22, 0xb0(r31)
    stw     r23, 0xb8(r31)
    stw     r24, 0xc0(r31)
    stw     r25, 0xc8(r31)
    stw     r26, 0xd0(r31)
    stw     r27, 0xd8(r31)
    stw     r28, 0xe0(r31)
    stw     r29, 0xe8(r31)
    stw     r30, 0xf0(r31)
    lis     r1, (lbl_80572560+0x1100)@h
    ori     r1, r1, (lbl_80572560+0x1100)@l
    mfcr    r5
    stw     r5, 0x360(r31)
    mfmsr   r5
    stw     r5, 0x368(r31)
    bl      fn_801698E0
    bl      fn_80169720
    mfmsr   r9
    xori    r0, r9, 0x10
    mtmsr   r0
    sync
    lwz     r4, 0xdf8(r0)
    lwz     r5, 0xdec(r0)
    lwz     r6, 0xdf4(r0)
    lwz     r7, 0xdf0(r0)
    lwz     r8, 0xde8(r0)
    srwi    r8, r8, 8
    mtmsr   r9
    sync
entry lbl_80169CCC
    lis     r2, _SDA2_BASE_@h
    ori     r2, r2, _SDA2_BASE_@l
    lis     r13, _SDA_BASE_@h
    ori     r13, r13, _SDA_BASE_@l
    stw     r4, 0xf8(r31)
    stw     r5, 0x358(r31)
    stw     r6, 0x370(r31)
    ori     r7, r7, 0x600
    xori    r7, r7, 0x600
    stw     r7, 0x378(r31)
    stw     r8, 0x580(r31)
    lis     r4, 0xcc00
    lhz     r5, 0x4010(r4)
    stw     r5, 0x6c8(r31)
    li      r5, 0xff
    sth     r5, 0x4010(r4)
    li      r4, 0x0
    mtspr   1013, r4
    cmpwi   r8, 0xd
    bne     L_80169D6C
    lwz     r4, 0x6f0(r31)
    cmpwi   r4, 0x0
    beq     L_80169D3C
    li      r4, 0x0
    stw     r4, 0x6f0(r31)
    lwz     r4, 0x6f4(r31)
    stw     r4, 0x450(r31)
    b       fn_80169304
L_80169D3C:
    lwz     r4, 0x6c0(r31)
    cmpwi   r4, 0x0
    beq     L_80169E94
    lwz     r4, 0x6c4(r31)
    add     r5, r31, r4
    lwz     r7, 0x0(r5)
    ori     r7, r7, 0x600
    xori    r7, r7, 0x600
    stw     r7, 0x0(r5)
    li      r4, 0x0
    stw     r4, 0x6c0(r31)
    b       L_80169E94
L_80169D6C:
    bl      fn_8016BC70
    lwz     r8, 0x580(r31)
    cmpwi   r8, 0x7
    bne     L_80169E3C
    lwz     r4, 0x370(r31)
    lwz     r3, 0x0(r4)
    cmpwi   r3, 0x5f
    bgt     L_80169E8C
    cmpwi   r3, 0x50
    bge     L_80169E8C
    cmpwi   r3, 0x1
    bne     L_80169DD0
    li      r5, 0x1e
    stw     r5, 0x580(r31)
    addi    r4, r4, 0x4
    stw     r4, 0x370(r31)
    lis     r3, (lbl_804CFD6C+0x39)@h
    ori     r3, r3, (lbl_804CFD6C+0x39)@l
    lwz     r4, 0x6d0(r31)
    cmpwi   r4, 0x0
    bne     L_80169DC8
    bl      OSReport
    b       L_80169DCC
L_80169DC8:
    bl      fn_801694B8
L_80169DCC:
    b       L_80169E8C
L_80169DD0:
    cmpwi   r3, 0x4
    beq     fn_8016948C
    cmpwi   r3, 0x3
    beq     fn_801693DC
    cmpwi   r3, 0x2
    bne     L_80169E10
    addi    r4, r4, 0x4
    stw     r4, 0x370(r31)
    lwz     r0, 0x69c(r31)
    mtlr    r0
    blrl
    cmpwi   r3, 0x0
    beq     fn_80169304
    li      r4, 0x1
    stw     r4, 0x6bc(r31)
    b       L_80169E94
L_80169E10:
    cmpwi   r3, 0x10
    blt     L_80169E8C
    cmpwi   r3, 0x16
    ble     L_80169E34
    lwz     r4, 0x6cc(r31)
    cmpwi   r4, 0x4
    bne     L_80169E8C
    cmpwi   r3, 0x1b
    bgt     L_80169E8C
L_80169E34:
    andi.   r3, r3, 0xf
    b       fn_8016A7E0
L_80169E3C:
    cmpwi   r8, 0x3
    bne     L_80169E8C
    lwz     r5, 0x440(r31)
    extrwi. r5, r5, 1, 9
    beq     L_80169E8C
    bl      fn_8016A440
    cmpwi   r3, 0x0
    beq     L_80169E84
    lwz     r3, 0x378(r31)
    ori     r3, r3, 0x400
    stw     r3, 0x378(r31)
    lwz     r3, 0x450(r31)
    stw     r3, 0x6f4(r31)
    li      r3, 0x0
    stw     r3, 0x450(r31)
    li      r3, 0x1
    stw     r3, 0x6f0(r31)
    b       fn_80169304
L_80169E84:
    li      r5, 0x1f
    stw     r5, 0x580(r31)
L_80169E8C:
    li      r4, 0x0
    stw     r4, 0x6bc(r31)
L_80169E94:
    lis     r5, lbl_804CFC70@h
    ori     r5, r5, lbl_804CFC70@l
    li      r4, 0x1
    stw     r4, 0x0(r5)
    lwz     r4, 0x6bc(r31)
    cmpwi   r4, 0x0
    bne     fn_80168BB0
    lis     r3, lbl_804CFD50@h
    ori     r3, r3, lbl_804CFD50@l
    li      r4, 0x8
    lwz     r0, 0x6a4(r31)
    mtlr    r0
    blrl
    b       fn_80168BB0
    // clang-format on
}
