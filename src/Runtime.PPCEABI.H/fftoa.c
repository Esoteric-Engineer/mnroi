#pragma section R ".rodata.1"
__declspec(section ".rodata.1") const char FftoaNegInfStr[8] = "-Inf";
__declspec(section ".rodata.1") const char FftoaInfStr[4] = "Inf";
__declspec(section ".rodata.1") const char FftoaNanStr[4] = "NaN";
__declspec(section ".rodata.1") const double FftoaZeroConst = 0.0;
__declspec(section ".rodata.1") const double FftoaOneConst = 1.0;
__declspec(section ".rodata.1") const double FftoaTenConst = 10.0;
__declspec(section ".rodata.1") const double FftoaCvtConst = 4503601774854144.0; /* MWCC's (double)k magic */
__declspec(section ".rodata.1") const double FftoaEpsConst = 5.551115123125783e-17;
__declspec(section ".rodata.1") const double FftoaHalfConst = 0.5;

extern char lbl_8057BF80[];
extern double floor(double);
extern double __ieee754_fmod(double, double);
extern int strround(char* s, int i);
extern char* itoa(int value, char* str, int base);

asm char* fftoa(double x, int prec, int fmt, int flag, char* sign)
{
    // clang-format off
    nofralloc
    stwu r1, -0x60(r1)
    mflr r0
    mfcr r12
    stfd f27, 0x38(r1)
    stfd f28, 0x40(r1)
    stfd f29, 0x48(r1)
    stfd f30, 0x50(r1)
    stfd f31, 0x58(r1)
    stmw r25, 0x1c(r1)
    stw r0, 0x64(r1)
    stw r12, 0x18(r1)
    fmr f30, f1
    mr r26, r3
    mr r25, r4
    fmr f0, f30
    stfd f0, 0x8(r1)
    lwz r9, 0x8(r1)
    lwz r10, 0xc(r1)
    mr r11, r10
    clrlwi r0, r9, 12
    srwi r9, r9, 20
    rlwinm r10, r9, 0, 20, 20
    clrlwi r9, r9, 21
    cmpwi r9, 0x7ff
    bne L_801737BC
    cmpwi r0, 0x0
    bne L_801737A8
    cmpwi r11, 0x0
    bne L_801737A8
    cmpwi r10, 0x0
    beq L_80173798
    lis r9, FftoaNegInfStr@ha
    lis r8, lbl_8057BF80@ha
    lwz r0, FftoaNegInfStr@l(r9)
    addi r11, r9, FftoaNegInfStr@l
    lbz r10, 0x4(r11)
    addi r9, r8, lbl_8057BF80@l
    stw r0, lbl_8057BF80@l(r8)
    stb r10, 0x4(r9)
    b L_80173BA8
L_80173798:
    lis r9, FftoaInfStr@ha
    lis r11, 0x8058
    lwz r0, FftoaInfStr@l(r9)
    b L_801737B4
L_801737A8:
    lis r9, FftoaNanStr@ha
    lis r11, lbl_8057BF80@ha
    lwz r0, FftoaNanStr@l(r9)
L_801737B4:
    stw r0, lbl_8057BF80@l(r11)
    b L_80173BA8
L_801737BC:
    lis r9, FftoaZeroConst@ha
    mr r27, r26
    lfd f0, FftoaZeroConst@l(r9)
    li r29, 0x0
    fcmpu cr0, f30, f0
    bge L_8017380C
    cmpwi r6, 0x0
    beq L_801737F0
    li r0, 0x2d
    lis r9, lbl_8057BF80@ha
    stb r0, 0x0(r6)
    addi r28, r9, lbl_8057BF80@l
    b L_80173804
L_801737F0:
    lis r9, lbl_8057BF80@ha
    li r0, 0x2d
    stb r0, lbl_8057BF80@l(r9)
    addi r9, r9, lbl_8057BF80@l
    addi r28, r9, 0x1
L_80173804:
    fneg f30, f30
    b L_80173814
L_8017380C:
    lis r9, lbl_8057BF80@ha
    addi r28, r9, lbl_8057BF80@l
L_80173814:
    lis r9, FftoaOneConst@ha
    cmpwi cr2, r5, 0x0
    lfd f31, FftoaOneConst@l(r9)
    lis r31, FftoaTenConst@ha
    cmpwi cr4, r25, 0x66
    fcmpu cr0, f30, f31
    cmpwi cr3, r26, 0x0
    cror 3, 2, 1
    bns L_801738E8
    fmr f1, f30
    lis r30, FftoaTenConst@ha
    bl floor
    fmr f27, f31
    lis r9, FftoaCvtConst@ha
    lfd f28, FftoaTenConst@l(r31)
    fmr f31, f1
    lfd f29, FftoaCvtConst@l(r9)
    fsub f30, f30, f31
    lis r31, 0x4330
L_80173860:
    cmpwi r29, 0xa2
    bgt L_801738B8
    lfd f2, FftoaTenConst@l(r30)
    fmr f1, f31
    bl __ieee754_fmod
    fctiwz f0, f1
    stfd f0, 0x10(r1)
    mr r11, r9
    lwz r10, 0x14(r1)
    xoris r0, r10, 0x8000
    addi r9, r10, 0x30
    stw r0, 0x14(r1)
    stbx r9, r28, r29
    stw r31, 0x10(r1)
    addi r29, r29, 0x1
    lfd f0, 0x10(r1)
    fsub f0, f0, f29
    fsub f31, f31, f0
    fdiv f31, f31, f28
    fcmpu cr0, f31, f27
    cror 3, 2, 1
    bso L_80173860
L_801738B8:
    li r10, 0x0
    subi r11, r29, 0x1
    cmpw r10, r11
    bge L_801738E8
L_801738C8:
    lbzx r0, r28, r11
    lbzx r9, r28, r10
    stbx r0, r28, r10
    stbx r9, r28, r11
    addi r10, r10, 0x1
    subi r11, r11, 0x1
    cmpw r10, r11
    blt L_801738C8
L_801738E8:
    mr. r30, r29
    bne L_80173978
    beq cr4, L_8017396C
    lis r9, FftoaZeroConst@ha
    lfd f0, FftoaZeroConst@l(r9)
    fcmpu cr0, f30, f0
    beq L_80173944
    lis r9, FftoaTenConst@ha
    lis r11, FftoaOneConst@ha
    lfd f0, FftoaTenConst@l(r9)
    lfd f13, FftoaOneConst@l(r11)
    fmul f30, f30, f0
    fcmpu cr0, f30, f13
    bge L_80173940
    fmr f12, f0
    fmr f0, f13
L_80173928:
    fmul f30, f30, f12
    subi r30, r30, 0x1
    fcmpu cr0, f30, f0
    bge L_80173940
    cmpwi r30, -0x3fd
    bgt L_80173928
L_80173940:
    subi r30, r30, 0x1
L_80173944:
    lis r9, FftoaOneConst@ha
    lfd f0, FftoaOneConst@l(r9)
    fcmpu cr0, f30, f0
    cror 3, 2, 1
    bns L_80173978
    lis r9, FftoaTenConst@ha
    addi r27, r26, 0x1
    lfd f0, FftoaTenConst@l(r9)
    fdiv f30, f30, f0
    b L_80173978
L_8017396C:
    li r0, 0x30
    li r29, 0x1
    stbx r0, r28, r30
L_80173978:
    cmpwi r30, 0x0
    bge L_80173988
    mr r31, r27
    b L_801739A8
L_80173988:
    bne cr4, L_801739A4
    mr r9, r30
    cmpwi r30, 0x1
    bge L_8017399C
    li r9, 0x1
L_8017399C:
    add r31, r27, r9
    b L_801739A8
L_801739A4:
    addi r31, r27, 0x1
L_801739A8:
    lis r9, FftoaTenConst@ha
    lis r10, FftoaEpsConst@ha
    lfd f12, FftoaTenConst@l(r9)
    lis r11, FftoaCvtConst@ha
    lis r9, FftoaOneConst@ha
    lfd f10, FftoaCvtConst@l(r11)
    lfd f11, FftoaOneConst@l(r9)
    addi r27, r31, 0x1
    lfd f13, FftoaEpsConst@l(r10)
    lis r8, 0x4330
L_801739D0:
    fmul f30, f30, f12
    mr r9, r11
    cmpw r29, r31
    fctiwz f0, f30
    stfd f0, 0x10(r1)
    fmul f13, f13, f12
    lwz r10, 0x14(r1)
    xoris r0, r10, 0x8000
    stw r0, 0x14(r1)
    stw r8, 0x10(r1)
    lfd f0, 0x10(r1)
    fsub f0, f0, f10
    fsub f30, f30, f0
    bge L_80173A34
    fcmpu cr0, f30, f13
    cror 3, 2, 1
    bns L_80173A34
    fsub f0, f11, f13
    fcmpu cr0, f30, f0
    cror 3, 2, 0
    bns L_80173A34
    addi r0, r10, 0x30
    stbx r0, r28, r29
    addi r29, r29, 0x1
    b L_801739D0
L_80173A34:
    lis r9, FftoaHalfConst@ha
    lfd f0, FftoaHalfConst@l(r9)
    fcmpu cr0, f30, f0
    cror 3, 2, 1
    bns L_80173A4C
    addi r10, r10, 0x1
L_80173A4C:
    addi r0, r10, 0x30
    stbx r0, r28, r29
    addi r29, r29, 0x1
    cmpw r29, r31
    bgt L_80173A74
    li r0, 0x30
L_80173A64:
    stbx r0, r28, r29
    addi r29, r29, 0x1
    cmpw r29, r31
    ble L_80173A64
L_80173A74:
    mr r3, r28
    mr r4, r27
    bl strround
    cmpwi r3, 0x0
    bne L_80173A98
    li r0, 0x31
    mr r31, r27
    stb r0, 0x0(r28)
    addi r30, r30, 0x1
L_80173A98:
    beq cr3, L_80173AEC
    bne cr4, L_80173AB4
    cmpwi r30, 0x0
    li r11, 0x1
    ble L_80173AB8
    mr r11, r30
    b L_80173AB8
L_80173AB4:
    li r11, 0x1
L_80173AB8:
    mr r29, r31
    cmpw r31, r11
    ble L_80173AE0
    add r9, r31, r28
L_80173AC8:
    lbz r0, -0x1(r9)
    subi r29, r29, 0x1
    cmpw r29, r11
    stb r0, 0x0(r9)
    subi r9, r9, 0x1
    bgt L_80173AC8
L_80173AE0:
    li r0, 0x2e
    stbx r0, r28, r11
    b L_80173AF0
L_80173AEC:
    subi r31, r31, 0x1
L_80173AF0:
    beq cr2, L_80173B20
    cmpwi r31, 0x0
    b L_80173B00
L_80173AFC:
    subic. r31, r31, 0x1
L_80173B00:
    beq L_80173B10
    lbzx r0, r28, r31
    cmpwi r0, 0x30
    beq L_80173AFC
L_80173B10:
    lbzx r0, r28, r31
    cmpwi r0, 0x2e
    bne L_80173B20
    subi r31, r31, 0x1
L_80173B20:
    beq cr4, L_80173B9C
    addi r31, r31, 0x1
    cmpwi r30, 0x0
    stbx r25, r28, r31
    blt L_80173B60
    addi r31, r31, 0x1
    li r0, 0x2b
    stbx r0, r28, r31
    beq L_80173B48
    subi r30, r30, 0x1
L_80173B48:
    cmpwi r30, 0x9
    bgt L_80173B84
    addi r31, r31, 0x1
    li r0, 0x30
    stbx r0, r28, r31
    b L_80173B84
L_80173B60:
    addi r31, r31, 0x1
    li r0, 0x2d
    stbx r0, r28, r31
    cmpwi r30, -0xa
    ble L_80173B80
    addi r31, r31, 0x1
    li r0, 0x30
    stbx r0, r28, r31
L_80173B80:
    neg r30, r30
L_80173B84:
    addi r31, r31, 0x1
    mr r3, r30
    add r4, r28, r31
    li r5, 0xa
    bl itoa
    b L_80173BA8
L_80173B9C:
    add r9, r31, r28
    li r0, 0x0
    stb r0, 0x1(r9)
L_80173BA8:
    lis r3, lbl_8057BF80@ha
    addi r3, r3, lbl_8057BF80@l
    lwz r0, 0x64(r1)
    lwz r12, 0x18(r1)
    mtlr r0
    lmw r25, 0x1c(r1)
    lfd f27, 0x38(r1)
    lfd f28, 0x40(r1)
    lfd f29, 0x48(r1)
    lfd f30, 0x50(r1)
    lfd f31, 0x58(r1)
    mtcrf 56, r12
    addi r1, r1, 0x60
    blr
    // clang-format on
}
