extern double lbl_8016CBDC(double x);
extern double lbl_8066C300;
extern double lbl_8066C308;
extern double lbl_8066C310;
extern double lbl_8066C318;
extern double lbl_8066C320;
extern double lbl_8066C328;
extern double lbl_8066C330;
extern double lbl_8066C338;
extern const char lbl_806701E0[4];
extern const char lbl_806701F0[4];
extern double scalbn(double x, int n);

asm int __kernel_rem_pio2(double* x, double* y, int e0, int nx, int prec, const int* ipio2)
{
    // clang-format off
    nofralloc
    stwu    r1, -0x280(r1)
    mflr    r0
    mfcr    r12
    stfd    f31, 0x278(r1)
    stmw    r19, 0x244(r1)
    stw     r0, 0x284(r1)
    stw     r12, 0x240(r1)
    lis     r0, 0x2aaa
    subi    r10, r5, 0x3
    ori     r0, r0, 0xaaab
    mr      r20, r7
    mulhw   r0, r10, r0
    slwi    r11, r20, 2
    srawi   r10, r10, 31
    la      r9, lbl_806701E0
    mr      r21, r3
    lwzx    r27, r9, r11
    mr      r26, r4
    srawi   r0, r0, 2
    mr      r19, r8
    subi    r29, r6, 0x1
    subf. r23, r10, r0
    bge     L_8016ECC8
    li      r23, 0x0
L_8016ECC8:
    addi    r0, r23, 0x1
    subf    r6, r29, r23
    mulli   r0, r0, 0x18
    mtctr   r6
    addi    r25, r1, 0x198
    addi    r30, r1, 0x8
    cmpwi   cr3, r20, 0x2
    add. r9, r29, r27
    subf    r28, r0, r5
    blt     L_8016ED58
    slwi    r0, r6, 2
    lfd     f12, lbl_8066C300
    lfd     f13, lbl_8066C308
    add     r10, r0, r19
    addi    r8, r9, 0x1
    lis     r7, 0x4330
    addi    r11, r1, 0x58
L_8016ED0C:
    mfctr   r9
    cmpwi   r9, 0x0
    blt     L_8016ED38
    lwz     r0, 0x0(r10)
    xoris   r0, r0, 0x8000
    stw     r0, 0x23c(r1)
    stw     r7, 0x238(r1)
    lfd     f0, 0x238(r1)
    fsub    f0, f0, f12
    stfd    f0, 0x0(r11)
    b       L_8016ED3C
L_8016ED38:
    stfd    f13, 0x0(r11)
L_8016ED3C:
    mfctr   r5
    addi    r11, r11, 0x8
    addi    r5, r5, 0x1
    addi    r10, r10, 0x4
    mtctr   r5
    subic. r8, r8, 0x1
    bne     L_8016ED0C
L_8016ED58:
    li      r8, 0x0
    cmpwi   cr4, r28, 0x0
    cmpw    r8, r27
    bgt     L_8016EDC8
    lfd     f12, lbl_8066C308
    mr      r10, r25
L_8016ED70:
    fmr     f1, f12
    cmpwi   r29, 0x0
    slwi    r5, r8, 3
    addi    r4, r8, 0x1
    blt     L_8016EDB8
    add     r0, r29, r8
    addi    r9, r1, 0x58
    slwi    r0, r0, 3
    mr      r11, r21
    add     r9, r0, r9
    addi    r0, r29, 0x1
    mtctr   r0
L_8016EDA0:
    lfd     f13, 0x0(r11)
    lfd     f0, 0x0(r9)
    addi    r11, r11, 0x8
    subi    r9, r9, 0x8
    fmadd   f1, f13, f0, f1
    bdnz    L_8016EDA0
L_8016EDB8:
    mr      r8, r4
    stfdx   f1, r10, r5
    cmpw    r8, r27
    ble     L_8016ED70
L_8016EDC8:
    mr      r31, r27
L_8016EDCC:
    slwi    r9, r31, 3
    mtctr   r31
    lfdx    f31, r25, r9
    cmpwi   r31, 0x0
    ble     L_8016EE60
    subi    r0, r9, 0x8
    lfd     f9, lbl_8066C310
    add     r7, r0, r25
    lfd     f10, lbl_8066C300
    lfd     f11, lbl_8066C318
    lis     r0, 0x4330
    mr      r8, r30
L_8016EDFC:
    fmul    f13, f31, f9
    mr      r11, r9
    mr      r10, r9
    fctiwz  f0, f13
    mfctr   r5
    stfd    f0, 0x238(r1)
    subic. r5, r5, 0x1
    mtctr   r5
    lwz     r9, 0x23c(r1)
    xoris   r9, r9, 0x8000
    stw     r9, 0x23c(r1)
    stw     r0, 0x238(r1)
    lfd     f1, 0x238(r1)
    fsub    f1, f1, f10
    fmul    f0, f1, f11
    fsub    f0, f31, f0
    fctiwz  f12, f0
    stfd    f12, 0x238(r1)
    lwz     r10, 0x23c(r1)
    stw     r10, 0x0(r8)
    addi    r8, r8, 0x4
    lfd     f0, 0x0(r7)
    subi    r7, r7, 0x8
    fadd    f31, f0, f1
    bgt     L_8016EDFC
L_8016EE60:
    fmr     f1, f31
    mr      r3, r28
    bl      scalbn
    lfd     f0, lbl_8066C320
    fmr     f31, f1
    fmul    f1, f31, f0
    bl      lbl_8016CBDC
    lfd     f0, lbl_8066C328
    mr      r9, r11
    lis     r10, 0x4330
    fmul    f1, f1, f0
    lfd     f12, lbl_8066C300
    li      r8, 0x0
    fsub    f31, f31, f1
    fctiwz  f13, f31
    stfd    f13, 0x238(r1)
    lwz     r22, 0x23c(r1)
    xoris   r0, r22, 0x8000
    stw     r0, 0x23c(r1)
    stw     r10, 0x238(r1)
    lfd     f0, 0x238(r1)
    fsub    f0, f0, f12
    fsub    f31, f31, f0
    ble     cr4, L_8016EEF0
    subi    r11, r31, 0x1
    subfic  r9, r28, 0x18
    slwi    r11, r11, 2
    subfic  r10, r28, 0x17
    lwzx    r0, r30, r11
    sraw    r8, r0, r9
    slw     r9, r8, r9
    add     r22, r22, r8
    subf    r0, r9, r0
    sraw    r8, r0, r10
    stwx    r0, r30, r11
    b       L_8016EF1C
L_8016EEF0:
    bne     cr4, L_8016EF08
    subi    r0, r31, 0x1
    slwi    r0, r0, 2
    lwzx    r9, r30, r0
    srawi   r8, r9, 23
    b       L_8016EF1C
L_8016EF08:
    lfd     f0, lbl_8066C330
    fcmpu   cr0, f31, f0
    cror    3, 2, 1
    bns     L_8016EF1C
    li      r8, 0x2
L_8016EF1C:
    cmpwi   r8, 0x0
    mfcr    r24
    ble     L_8016EFF0
    cmpwi   cr7, r8, 0x2
    addi    r22, r22, 0x1
    li      r7, 0x0
    cmpwi   r31, 0x0
    ble     L_8016EF90
    lis     r11, 0xff
    mr      r10, r30
    lis     r6, 0x100
    ori     r11, r11, 0xffff
    li      r9, 0x0
    mr      r8, r31
L_8016EF54:
    lwzx    r0, r9, r10
    cmpwi   r7, 0x0
    mtctr   r0
    bne     L_8016EF78
    cmpwi   r0, 0x0
    beq     L_8016EF84
    subf    r0, r0, r6
    li      r7, 0x1
    b       L_8016EF80
L_8016EF78:
    mfctr   r5
    subf    r0, r5, r11
L_8016EF80:
    stwx    r0, r9, r30
L_8016EF84:
    addi    r9, r9, 0x4
    subic. r8, r8, 0x1
    bne     L_8016EF54
L_8016EF90:
    ble     cr4, L_8016EFD0
    cmpwi   r28, 0x1
    beq     L_8016EFA8
    cmpwi   r28, 0x2
    beq     L_8016EFBC
    b       L_8016EFD0
L_8016EFA8:
    subi    r9, r31, 0x1
    slwi    r9, r9, 2
    lwzx    r0, r30, r9
    clrlwi  r0, r0, 9
    b       L_8016EFCC
L_8016EFBC:
    subi    r9, r31, 0x1
    slwi    r9, r9, 2
    lwzx    r0, r30, r9
    clrlwi  r0, r0, 10
L_8016EFCC:
    stwx    r0, r30, r9
L_8016EFD0:
    bne     cr7, L_8016EFF0
    lfd     f1, lbl_8066C338
    cmpwi   r7, 0x0
    fsub    f31, f1, f31
    beq     L_8016EFF0
    mr      r3, r28
    bl      scalbn
    fsub    f31, f31, f1
L_8016EFF0:
    lfd     f0, lbl_8066C308
    fmr     f13, f0
    fcmpu   cr0, f31, f0
    bne     L_8016F130
    subi    r8, r31, 0x1
    li      r0, 0x0
    mtctr   r0
    cmpw    r8, r27
    blt     L_8016F03C
    slwi    r0, r8, 2
    add     r9, r0, r30
L_8016F01C:
    lwz     r0, 0x0(r9)
    mfctr   r5
    subi    r8, r8, 0x1
    subi    r9, r9, 0x4
    or      r5, r5, r0
    cmpw    r8, r27
    mtctr   r5
    bge     L_8016F01C
L_8016F03C:
    mfctr   r6
    cmpwi   r6, 0x0
    bne     L_8016F130
    subi    r0, r27, 0x1
    li      r6, 0x1
    slwi    r0, r0, 2
    addi    r11, r31, 0x1
    lwzx    r9, r30, r0
    cmpwi   r9, 0x0
    bne     L_8016F080
    slwi    r9, r27, 2
    add     r9, r9, r30
    subi    r9, r9, 0x4
L_8016F070:
    lwzu    r0, -0x4(r9)
    addi    r6, r6, 0x1
    cmpwi   r0, 0x0
    beq     L_8016F070
L_8016F080:
    add     r0, r31, r6
    mr      r8, r11
    mr      r6, r0
    cmpw    r8, r0
    bgt     L_8016F128
    addi    r3, r1, 0x58
    lfd     f11, lbl_8066C300
    lfd     f12, lbl_8066C308
    mr      r24, r3
    lis     r31, 0x4330
    mr      r7, r25
    mr      r12, r6
L_8016F0B0:
    add     r0, r23, r8
    slwi    r0, r0, 2
    add     r9, r29, r8
    lwzx    r11, r19, r0
    slwi    r9, r9, 3
    addi    r4, r8, 0x1
    fmr     f1, f12
    xoris   r11, r11, 0x8000
    cmpwi   r29, 0x0
    stw     r11, 0x23c(r1)
    slwi    r5, r8, 3
    stw     r31, 0x238(r1)
    lfd     f0, 0x238(r1)
    fsub    f0, f0, f11
    stfdx   f0, r3, r9
    blt     L_8016F118
    addi    r0, r29, 0x1
    add     r9, r9, r24
    mtctr   r0
    mr      r11, r21
L_8016F100:
    lfd     f13, 0x0(r11)
    lfd     f0, 0x0(r9)
    addi    r11, r11, 0x8
    subi    r9, r9, 0x8
    fmadd   f1, f13, f0, f1
    bdnz    L_8016F100
L_8016F118:
    mr      r8, r4
    stfdx   f1, r7, r5
    cmpw    r8, r12
    ble     L_8016F0B0
L_8016F128:
    mr      r31, r6
    b       L_8016EDCC
L_8016F130:
    fcmpu   cr0, f31, f13
    bne     L_8016F16C
    subi    r31, r31, 0x1
    subi    r28, r28, 0x18
    slwi    r9, r31, 2
    lwzx    r0, r30, r9
    cmpwi   r0, 0x0
    bne     L_8016F218
    add     r9, r9, r30
L_8016F154:
    lwzu    r0, -0x4(r9)
    subi    r31, r31, 0x1
    subi    r28, r28, 0x18
    cmpwi   r0, 0x0
    beq     L_8016F154
    b       L_8016F218
L_8016F16C:
    fmr     f1, f31
    neg     r3, r28
    bl      scalbn
    lfd     f9, lbl_8066C318
    fmr     f31, f1
    fcmpu   cr0, f31, f9
    cror    3, 2, 1
    bns     L_8016F204
    lfd     f0, lbl_8066C310
    mr      r8, r9
    mr      r10, r9
    fmul    f0, f31, f0
    mr      r11, r9
    lis     r0, 0x4330
    lfd     f10, lbl_8066C300
    fctiwz  f13, f0
    slwi    r6, r31, 2
    stfd    f13, 0x238(r1)
    addi    r31, r31, 0x1
    slwi    r7, r31, 2
    addi    r28, r28, 0x18
    lwz     r9, 0x23c(r1)
    xoris   r9, r9, 0x8000
    stw     r9, 0x23c(r1)
    stw     r0, 0x238(r1)
    lfd     f1, 0x238(r1)
    fsub    f1, f1, f10
    fmul    f0, f1, f9
    fsub    f0, f31, f0
    fctiwz  f11, f0
    stfd    f11, 0x238(r1)
    fctiwz  f12, f1
    lwz     r10, 0x23c(r1)
    stfd    f12, 0x238(r1)
    stwx    r10, r30, r6
    lwz     r11, 0x23c(r1)
    stwx    r11, r30, r7
    b       L_8016F218
L_8016F204:
    fctiwz  f0, f31
    stfd    f0, 0x238(r1)
    slwi    r0, r31, 2
    lwz     r9, 0x23c(r1)
    stwx    r9, r30, r0
L_8016F218:
    lfd     f1, lbl_8066C338
    mr      r3, r28
    bl      scalbn
    mr. r8, r31
    blt     L_8016F280
    slwi    r0, r8, 2
    slwi    r9, r8, 3
    lfd     f12, lbl_8066C300
    add     r10, r0, r30
    lfd     f13, lbl_8066C310
    add     r11, r9, r25
    lis     r7, 0x4330
    mr      r8, r25
L_8016F24C:
    lwz     r0, 0x0(r10)
    subi    r10, r10, 0x4
    xoris   r0, r0, 0x8000
    stw     r0, 0x23c(r1)
    stw     r7, 0x238(r1)
    lfd     f0, 0x238(r1)
    fsub    f0, f0, f12
    fmul    f0, f1, f0
    stfd    f0, 0x0(r11)
    fmul    f1, f1, f13
    subi    r11, r11, 0x8
    cmpw    r11, r8
    bge     L_8016F24C
L_8016F280:
    mr. r8, r31
    blt     L_8016F2F8
    mr      r3, r25
L_8016F28C:
    li      r6, 0x0
    lfd     f1, lbl_8066C308
    cmpw    r6, r27
    subi    r4, r8, 0x1
    subf    r11, r8, r31
    addi    r7, r1, 0xf8
    bgt     L_8016F2E8
    mr      r5, r11
    cmpw    r6, r11
    bgt     L_8016F2E8
    slwi    r0, r8, 3
    la      r10, lbl_806701F0
    add     r9, r0, r3
L_8016F2C0:
    lfd     f13, 0x0(r10)
    addi    r6, r6, 0x1
    lfd     f0, 0x0(r9)
    addi    r10, r10, 0x8
    addi    r9, r9, 0x8
    cmpw    r6, r27
    fmadd   f1, f13, f0, f1
    bgt     L_8016F2E8
    cmpw    r6, r5
    ble     L_8016F2C0
L_8016F2E8:
    slwi    r0, r11, 3
    mr. r8, r4
    stfdx   f1, r7, r0
    bge     L_8016F28C
L_8016F2F8:
    bgt     cr3, L_8016F310
    cmpwi   r20, 0x1
    bge     L_8016F360
    cmpwi   r20, 0x0
    beq     L_8016F31C
    b       L_8016F4CC
L_8016F310:
    cmpwi   r20, 0x3
    beq     L_8016F3E0
    b       L_8016F4CC
L_8016F31C:
    lfd     f1, lbl_8066C308
    mr. r8, r31
    blt     L_8016F348
    addi    r9, r1, 0xf8
    slwi    r0, r8, 3
    add     r9, r9, r0
L_8016F334:
    lfd     f0, 0x0(r9)
    subic. r8, r8, 0x1
    subi    r9, r9, 0x8
    fadd    f1, f1, f0
    bge     L_8016F334
L_8016F348:
    stfd    f1, 0x0(r26)
    mtcrf   128, r24
    beq     L_8016F4CC
    fneg    f0, f1
    stfd    f0, 0x0(r26)
    b       L_8016F4CC
L_8016F360:
    lfd     f1, lbl_8066C308
    mr. r8, r31
    blt     L_8016F38C
    addi    r9, r1, 0xf8
    slwi    r0, r8, 3
    add     r9, r9, r0
L_8016F378:
    lfd     f0, 0x0(r9)
    subic. r8, r8, 0x1
    subi    r9, r9, 0x8
    fadd    f1, f1, f0
    bge     L_8016F378
L_8016F38C:
    stfd    f1, 0x0(r26)
    mtcrf   128, r24
    beq     L_8016F3A0
    fneg    f0, f1
    stfd    f0, 0x0(r26)
L_8016F3A0:
    lfd     f0, 0xf8(r1)
    cmpwi   r31, 0x0
    fsub    f1, f0, f1
    ble     L_8016F3CC
    mr      r8, r31
    addi    r9, r1, 0x100
L_8016F3B8:
    lfd     f0, 0x0(r9)
    subic. r8, r8, 0x1
    addi    r9, r9, 0x8
    fadd    f1, f1, f0
    bne     L_8016F3B8
L_8016F3CC:
    stfd    f1, 0x8(r26)
    mtcrf   128, r24
    beq     L_8016F4CC
    fneg    f0, f1
    b       L_8016F4C8
L_8016F3E0:
    mr. r8, r31
    ble     L_8016F41C
    addi    r9, r1, 0xf0
    slwi    r0, r8, 3
    add     r9, r9, r0
L_8016F3F4:
    lfd     f13, 0x0(r9)
    subic. r8, r8, 0x1
    lfd     f0, 0x8(r9)
    fadd    f1, f13, f0
    fsub    f13, f13, f1
    stfd    f1, 0x0(r9)
    fadd    f0, f0, f13
    stfd    f0, 0x8(r9)
    subi    r9, r9, 0x8
    bgt     L_8016F3F4
L_8016F41C:
    mr      r8, r31
    cmpwi   r8, 0x1
    ble     L_8016F460
    addi    r9, r1, 0xf0
    slwi    r0, r8, 3
    add     r9, r9, r0
L_8016F434:
    lfd     f13, 0x0(r9)
    subi    r8, r8, 0x1
    lfd     f0, 0x8(r9)
    cmpwi   r8, 0x1
    fadd    f1, f13, f0
    fsub    f13, f13, f1
    stfd    f1, 0x0(r9)
    fadd    f0, f0, f13
    stfd    f0, 0x8(r9)
    subi    r9, r9, 0x8
    bgt     L_8016F434
L_8016F460:
    mr      r8, r31
    lfd     f1, lbl_8066C308
    cmpwi   r8, 0x1
    lfd     f13, 0xf8(r1)
    ble     L_8016F498
    addi    r9, r1, 0xf8
    slwi    r0, r8, 3
    add     r9, r9, r0
L_8016F480:
    lfd     f0, 0x0(r9)
    subi    r8, r8, 0x1
    subi    r9, r9, 0x8
    cmpwi   r8, 0x1
    fadd    f1, f1, f0
    bgt     L_8016F480
L_8016F498:
    mtcrf   128, r24
    bne     L_8016F4B0
    lfd     f0, 0x100(r1)
    stfd    f1, 0x10(r26)
    stfd    f13, 0x0(r26)
    b       L_8016F4C8
L_8016F4B0:
    lfd     f0, 0x100(r1)
    fneg    f13, f13
    fneg    f12, f1
    stfd    f13, 0x0(r26)
    fneg    f0, f0
    stfd    f12, 0x10(r26)
L_8016F4C8:
    stfd    f0, 0x8(r26)
L_8016F4CC:
    clrlwi  r3, r22, 29
    lwz     r0, 0x284(r1)
    lwz     r12, 0x240(r1)
    mtlr    r0
    lmw     r19, 0x244(r1)
    lfd     f31, 0x278(r1)
    mtcrf   24, r12
    addi    r1, r1, 0x280
    blr
    // clang-format on
}
