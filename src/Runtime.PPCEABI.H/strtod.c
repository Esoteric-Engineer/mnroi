#pragma section R ".rodata.1"
__declspec(section ".rodata.1") const double StrtodZeroConst = 0.0;
__declspec(section ".rodata.1") const double StrtodHiMagicConst = 4503601774854144.0;
__declspec(section ".rodata.1") const double StrtodBillionConst = 1000000000.0;
__declspec(section ".rodata.1") const double StrtodOneConst = 1.0;

double powersOf10[9] = {
    1e1, 1e2, 1e4, 1e8, 1e16, 1e32, 1e64, 1e128, 1e256,
};

extern int lbl_8066C3A8;
extern int isspace(int c);
extern int isdigit(int c);
extern int* __errno(void);

asm double strtod(const char* str, char** end)
{
    // clang-format off
    nofralloc
    stwu    r1, -0x40(r1)
    mflr    r0
    mfcr    r12
    stfd    f31, 0x38(r1)
    stmw    r23, 0x14(r1)
    stw     r0, 0x44(r1)
    stw     r12, 0x10(r1)
    mr      r26, r3
    mr      r24, r4
    li      r25, 0x0
    li      r27, 0x0
    mr      r30, r26
    b       L_80177074
L_80177070:
    addi    r30, r30, 0x1
L_80177074:
    lbz     r3, 0x0(r30)
    crclr   4*cr1+eq
    bl      isspace
    cmpwi   r3, 0x0
    bne     L_80177070
    lbz     r0, 0x0(r30)
    extsb   r0, r0
    cmpwi   r0, 0x2d
    bne     L_801770A4
    li      r0, 0x1
    addi    r30, r30, 0x1
    b       L_801770B4
L_801770A4:
    cmpwi   r0, 0x2b
    bne     L_801770B0
    addi    r30, r30, 0x1
L_801770B0:
    li      r0, 0x0
L_801770B4:
    li      r28, -0x1
    li      r29, 0x0
    cmpwi   cr4, r24, 0x0
    cmpwi   cr3, r0, 0x0
    b       L_801770D4
L_801770C8:
    mr      r28, r29
L_801770CC:
    addi    r30, r30, 0x1
    addi    r29, r29, 0x1
L_801770D4:
    lbz     r0, 0x0(r30)
    extsb   r31, r0
    mr      r3, r31
    crclr   4*cr1+eq
    bl      isdigit
    cmpwi   r3, 0x0
    bne     L_801770CC
    cmpwi   r31, 0x2e
    cmpwi   cr7, r28, 0x0
    bne     L_80177100
    blt     cr7, L_801770C8
L_80177100:
    mr      r23, r30
    subf    r30, r29, r30
    bge     cr7, L_80177114
    mr      r28, r29
    b       L_80177118
L_80177114:
    subi    r29, r29, 0x1
L_80177118:
    cmpwi   r29, 0x12
    ble     L_8017712C
    subi    r28, r28, 0x12
    li      r29, 0x12
    b       L_80177130
L_8017712C:
    subf    r28, r29, r28
L_80177130:
    cmpwi   r29, 0x0
    bne     L_80177148
    lis     r9, StrtodZeroConst@ha
    mr      r30, r26
    lfd     f31, StrtodZeroConst@l(r9)
    b       L_80177330
L_80177148:
    li      r11, 0x0
    cmpwi   r29, 0x9
    ble     L_8017718C
L_80177154:
    lbz     r0, 0x0(r30)
    addi    r30, r30, 0x1
    extsb   r31, r0
    cmpwi   r31, 0x2e
    bne     L_80177174
    lbz     r0, 0x0(r30)
    addi    r30, r30, 0x1
    extsb   r31, r0
L_80177174:
    mulli   r9, r11, 0xa
    subi    r29, r29, 0x1
    cmpwi   r29, 0x9
    subi    r9, r9, 0x30
    add     r11, r9, r31
    bgt     L_80177154
L_8017718C:
    li      r7, 0x0
    cmpwi   r29, 0x0
    ble     L_801771CC
L_80177198:
    lbz     r0, 0x0(r30)
    addi    r30, r30, 0x1
    extsb   r31, r0
    cmpwi   r31, 0x2e
    bne     L_801771B8
    lbz     r0, 0x0(r30)
    addi    r30, r30, 0x1
    extsb   r31, r0
L_801771B8:
    mulli   r9, r7, 0xa
    subic.  r29, r29, 0x1
    subi    r9, r9, 0x30
    add     r7, r9, r31
    bgt     L_80177198
L_801771CC:
    xoris   r0, r11, 0x8000
    lis     r8, 0x4330
    xoris   r7, r7, 0x8000
    stw     r0, 0xc(r1)
    mr      r10, r11
    lis     r9, StrtodHiMagicConst@ha
    mr      r30, r23
    stw     r8, 0x8(r1)
    lfd     f11, StrtodHiMagicConst@l(r9)
    lfd     f13, 0x8(r1)
    lis     r9, StrtodBillionConst@ha
    stw     r7, 0xc(r1)
    lbz     r0, 0x0(r30)
    fsub    f13, f13, f11
    stw     r8, 0x8(r1)
    lfd     f12, StrtodBillionConst@l(r9)
    extsb   r0, r0
    lfd     f0, 0x8(r1)
    cmpwi   r0, 0x45
    fsub    f0, f0, f11
    fmadd   f31, f13, f12, f0
    beq     L_8017722C
    cmpwi   r0, 0x65
    bne     L_801772A0
L_8017722C:
    lbzu    r0, 0x1(r30)
    extsb   r0, r0
    cmpwi   r0, 0x2d
    bne     L_80177248
    li      r25, 0x1
    addi    r30, r30, 0x1
    b       L_80177258
L_80177248:
    cmpwi   r0, 0x2b
    bne     L_80177254
    addi    r30, r30, 0x1
L_80177254:
    li      r25, 0x0
L_80177258:
    lbz     r3, 0x0(r30)
    crclr   4*cr1+eq
    bl      isdigit
    cmpwi   r3, 0x0
    bne     L_8017728C
    mr      r30, r23
    b       L_80177330
L_80177274:
    mulli   r9, r27, 0xa
    lbz     r0, 0x0(r30)
    addi    r30, r30, 0x1
    extsb   r0, r0
    subi    r9, r9, 0x30
    add     r27, r9, r0
L_8017728C:
    lbz     r3, 0x0(r30)
    crclr   4*cr1+eq
    bl      isdigit
    cmpwi   r3, 0x0
    bne     L_80177274
L_801772A0:
    cmpwi   r25, 0x0
    beq     L_801772B0
    subf    r27, r27, r28
    b       L_801772B4
L_801772B0:
    add     r27, r27, r28
L_801772B4:
    cmpwi   r27, 0x0
    bge     L_801772C8
    li      r25, 0x1
    neg     r27, r27
    b       L_801772CC
L_801772C8:
    li      r25, 0x0
L_801772CC:
    lwz     r0, lbl_8066C3A8
    cmpw    r27, r0
    ble     L_801772E8
    mr      r27, r0
    bl      __errno
    li      r0, 0x22
    stw     r0, 0x0(r3)
L_801772E8:
    lis     r9, StrtodOneConst@ha
    lis     r11, powersOf10@ha
    lfd     f13, StrtodOneConst@l(r9)
    addi    r11, r11, powersOf10@l
    cmpwi   cr7, r25, 0x0
    cmpwi   r27, 0x0
    beq     L_80177320
L_80177304:
    andi.   r0, r27, 0x1
    beq     L_80177314
    lfd     f0, 0x0(r11)
    fmul    f13, f13, f0
L_80177314:
    addi    r11, r11, 0x8
    srawi.  r27, r27, 1
    bne     L_80177304
L_80177320:
    beq     cr7, L_8017732C
    fdiv    f31, f31, f13
    b       L_80177330
L_8017732C:
    fmul    f31, f31, f13
L_80177330:
    beq     cr4, L_80177338
    stw     r30, 0x0(r24)
L_80177338:
    bne     cr3, L_80177344
    fmr     f1, f31
    b       L_80177348
L_80177344:
    fneg    f1, f31
L_80177348:
    lwz     r0, 0x44(r1)
    lwz     r12, 0x10(r1)
    mtlr    r0
    lmw     r23, 0x14(r1)
    lfd     f31, 0x38(r1)
    mtcrf   24, r12
    addi    r1, r1, 0x40
    blr
    // clang-format on
}
