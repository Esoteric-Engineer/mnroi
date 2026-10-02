extern char lbl_80572560[];
extern char lbl_80573680[];
void fn_801687E8(void);
void fn_801698E0(void);
void fn_80169720(void);
void lbl_80169CCC(void);
void lbl_8016A0EC(void);

asm void fn_8016A094(void)
{
    // clang-format off
    nofralloc
    mfcr    r31
    mtsprg  3, r31
    lis     r31, lbl_80573680@h
    ori     r31, r31, lbl_80573680@l
    lwz     r31, 0x6ec(r31)
    cmplwi  r31, 0
    beq     L_8016A0CC
    mfsprg  r31, 3
    mtcrf   255, r31
    lis     r31, fn_801687E8@h
    ori     r31, r31, fn_801687E8@l
    mtsrr0  r31
    mfsprg  r31, 1
    rfi
L_8016A0CC:
    mfsprg  r31, 3
    mtcrf   255, r31
    mfsprg  r31, 0
    mtsrr0  r31
    li      r31, 3
    mtsprg  2, r31
    lis     r31, lbl_80573680@h
    ori     r31, r31, lbl_80573680@l
entry lbl_8016A0EC
    stw     r0, 0(r31)
    stw     r1, 8(r31)
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
    stw     r20, 0xA0(r31)
    stw     r21, 0xA8(r31)
    stw     r22, 0xB0(r31)
    stw     r23, 0xB8(r31)
    stw     r24, 0xC0(r31)
    stw     r25, 0xC8(r31)
    stw     r26, 0xD0(r31)
    stw     r27, 0xD8(r31)
    stw     r28, 0xE0(r31)
    stw     r29, 0xE8(r31)
    stw     r30, 0xF0(r31)
    lis     r1, (lbl_80572560 + 0x1100)@h
    ori     r1, r1, (lbl_80572560 + 0x1100)@l
    mflr    r28
    mfcr    r5
    stw     r5, 0x360(r31)
    mfmsr   r5
    stw     r5, 0x368(r31)
    bl      fn_801698E0
    bl      fn_80169720
    mfsprg  r4, 1
    mr      r5, r28
    mfsrr0  r6
    mfsrr1  r7
    mfsprg  r8, 2
    b       lbl_80169CCC
    // clang-format on
}
