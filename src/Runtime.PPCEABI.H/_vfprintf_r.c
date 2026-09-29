extern char lbl_8049C600[];
extern char lbl_8049C608[];
extern int __mb_cur_max;
extern int lbl_8066C3B0;
extern char lbl_8049C580[];
extern char lbl_8049C590[];
extern char lbl_8049C5A0[];
extern char lbl_8049C5B4[];
extern char lbl_8049C5BC[];
extern char lbl_8049C5D0[];
extern char lbl_8049C5F0[];
extern char lbl_8049C5F8[];
extern void __group_digits(void);
extern void _vfwrite(void);
extern void _mbtowc_r(void);
extern void memchr(void);
extern void memcpy(void);
extern void strlen(void);
extern void __udivdi3(void);
extern void __umoddi3(void);
extern void fftoa(void);
extern void __ieee754_log10(void);
extern void localeconv(void);

// _vfprintf_r(reent, fp, fmt, ap): Newlib printf body with float support (GCC output).
asm int _vfprintf_r(void* reent, void* fp, const char* fmt, void* ap)
{
    // clang-format off
    nofralloc
    stwu r1, -0x1f8(r1)
    mflr r0
    mfcr r12
    stfd f31, 0x1f0(r1)
    stmw r14, 0x1a8(r1)
    stw r0, 0x1fc(r1)
    stw r12, 0x1a4(r1)
    mr r28, r4
    mr r29, r6
    mr r22, r5
    li r14, 0x0
    bl localeconv
    li r16, 0x0
    li r0, 0x0
    addi r9, r1, 0x170
    addi r11, r1, 0x174
    stw r9, 0x184(r1)
    stw r0, 0x174(r1)
    li r18, 0x8
    stw r11, 0x188(r1)
L_80173DDC:
    mr r27, r22
L_80173DE0:
    lwz r3, lbl_8066C3B0
    mr r5, r22
    lwz r4, 0x184(r1)
    lwz r6, __mb_cur_max
    lwz r7, 0x188(r1)
    bl _mbtowc_r
    mr. r30, r3
    ble L_80173E14
    lhz r0, 0x170(r1)
    add r22, r22, r30
    cmpwi r0, 0x25
    bne L_80173DE0
    subi r22, r22, 0x1
L_80173E14:
    subf. r31, r27, r22
    beq L_80173EB8
    lhz r0, 0xc(r28)
    andi. r9, r0, 0x200
    beq L_80173E8C
    lwz r5, 0x8(r28)
    cmpw r5, r31
    ble L_80173E64
    lwz r3, 0x0(r28)
    mr r4, r27
    mr r5, r31
    crclr 6
    bl memcpy
    lwz r0, 0x0(r28)
    lwz r9, 0x8(r28)
    add r0, r0, r31
    subf r9, r31, r9
    stw r0, 0x0(r28)
    stw r9, 0x8(r28)
    b L_80173EB4
L_80173E64:
    lwz r3, 0x0(r28)
    mr r4, r27
    crclr 6
    bl memcpy
    lwz r0, 0x0(r28)
    lwz r9, 0x8(r28)
    stw r16, 0x8(r28)
    add r0, r0, r9
    stw r0, 0x0(r28)
    b L_80173EB4
L_80173E8C:
    lwz r0, 0xc(r28)
    cmpwi r0, 0x0
    bne L_80173EA0
    li r0, 0x1
    sth r0, 0xe(r28)
L_80173EA0:
    lha r3, 0xe(r28)
    mr r4, r27
    mr r5, r31
    li r6, 0x0
    bl _vfwrite
L_80173EB4:
    add r14, r14, r31
L_80173EB8:
    cmpwi r30, 0x0
    ble L_80175538
    lwz r0, 0x8(r28)
    cmpwi r0, 0x0
    bgt L_80173ED8
    lhz r0, 0xc(r28)
    andi. r9, r0, 0x200
    bne L_80175558
L_80173ED8:
    li r17, 0x0
    addi r22, r22, 0x1
    stb r17, 0x172(r1)
    li r24, 0x0
    li r15, 0x0
L_80173EEC:
    li r25, -0x1
L_80173EF0:
    lbz r0, 0x0(r22)
    addi r22, r22, 0x1
    extsb r26, r0
L_80173EFC:
    cmpwi r26, 0x63
    beq L_801741E8
    bgt L_80173FC0
    cmpwi r26, 0x44
    beq L_8017424C
    bgt L_80173F7C
    cmpwi r26, 0x2e
    beq L_801740C4
    bgt L_80173F64
    cmpwi r26, 0x27
    beq L_80174058
    bgt L_80173F40
    cmpwi r26, 0x20
    beq L_8017403C
    cmpwi r26, 0x23
    beq L_80174050
    b L_80174D34
L_80173F40:
    cmpwi r26, 0x2b
    beq L_80174048
    bgt L_80173F58
    cmpwi r26, 0x2a
    beq L_80174060
    b L_80174D34
L_80173F58:
    cmpwi r26, 0x2d
    beq L_801740BC
    b L_80174D34
L_80173F64:
    cmpwi r26, 0x30
    beq L_80174180
    blt L_80174D34
    cmpwi r26, 0x39
    bgt L_80174D34
    b L_80174188
L_80173F7C:
    cmpwi r26, 0x4c
    beq L_801741B8
    bgt L_80173F9C
    cmpwi r26, 0x45
    beq L_801743CC
    cmpwi r26, 0x47
    beq L_801743CC
    b L_80174D34
L_80173F9C:
    cmpwi r26, 0x55
    beq L_801748D0
    bgt L_80173FB4
    cmpwi r26, 0x4f
    beq L_80174654
    b L_80174D34
L_80173FB4:
    cmpwi r26, 0x58
    beq L_80174A34
    b L_80174D34
L_80173FC0:
    cmpwi r26, 0x6e
    beq L_80174500
    bgt L_80173FF8
    cmpwi r26, 0x67
    bgt L_80173FE0
    cmpwi r26, 0x65
    bge L_801743CC
    b L_80174250
L_80173FE0:
    cmpwi r26, 0x69
    beq L_80174250
    blt L_801741C0
    cmpwi r26, 0x6c
    beq L_801741C8
    b L_80174D34
L_80173FF8:
    cmpwi r26, 0x71
    beq L_801741D8
    bgt L_80174018
    cmpwi r26, 0x6f
    beq L_80174658
    cmpwi r26, 0x70
    beq L_801747B8
    b L_80174D34
L_80174018:
    cmpwi r26, 0x75
    beq L_801748D4
    bgt L_80174030
    cmpwi r26, 0x73
    beq L_80174828
    b L_80174D34
L_80174030:
    cmpwi r26, 0x78
    beq L_80174A40
    b L_80174D34
L_8017403C:
    lbz r0, 0x172(r1)
    cmpwi r0, 0x0
    bne L_80173EF0
L_80174048:
    stb r26, 0x172(r1)
    b L_80173EF0
L_80174050:
    ori r24, r24, 0x1
    b L_80173EF0
L_80174058:
    ori r24, r24, 0x200
    b L_80173EF0
L_80174060:
    lbz r11, 0x0(r29)
    extsb r9, r11
    addi r0, r9, 0x1
    cmplwi r0, 0x8
    bgt L_8017408C
    lwz r0, 0x8(r29)
    slwi r9, r9, 2
    addi r11, r11, 0x1
    add r9, r0, r9
    stb r11, 0x0(r29)
    b L_801740AC
L_8017408C:
    cmpwi r9, 0x7
    bgt L_801740A0
    lwz r9, 0x4(r29)
    stb r18, 0x0(r29)
    b L_801740A4
L_801740A0:
    lwz r9, 0x4(r29)
L_801740A4:
    addi r0, r9, 0x4
    stw r0, 0x4(r29)
L_801740AC:
    lwz r17, 0x0(r9)
    cmpwi r17, 0x0
    bge L_80173EF0
    neg r17, r17
L_801740BC:
    ori r24, r24, 0x4
    b L_80173EF0
L_801740C4:
    lbz r0, 0x0(r22)
    addi r22, r22, 0x1
    extsb r26, r0
    cmpwi r26, 0x2a
    bne L_80174138
    lbz r11, 0x0(r29)
    extsb r9, r11
    addi r0, r9, 0x1
    cmplwi r0, 0x8
    bgt L_80174104
    lwz r0, 0x8(r29)
    slwi r9, r9, 2
    addi r11, r11, 0x1
    add r3, r0, r9
    stb r11, 0x0(r29)
    b L_80174124
L_80174104:
    cmpwi r9, 0x7
    bgt L_80174118
    lwz r3, 0x4(r29)
    stb r18, 0x0(r29)
    b L_8017411C
L_80174118:
    lwz r3, 0x4(r29)
L_8017411C:
    addi r0, r3, 0x4
    stw r0, 0x4(r29)
L_80174124:
    lwz r30, 0x0(r3)
    mr r25, r30
    cmpwi r25, -0x1
    bge L_80173EF0
    b L_80173EEC
L_80174138:
    subi r0, r26, 0x30
    li r30, 0x0
    cmplwi r0, 0x9
    bgt L_8017416C
L_80174148:
    mulli r9, r30, 0xa
    lbz r11, 0x0(r22)
    addi r22, r22, 0x1
    subi r9, r9, 0x30
    add r30, r9, r26
    extsb r26, r11
    subi r0, r26, 0x30
    cmplwi r0, 0x9
    ble L_80174148
L_8017416C:
    mr r25, r30
    cmpwi r25, -0x1
    bge L_80173EFC
    li r25, -0x1
    b L_80173EFC
L_80174180:
    ori r24, r24, 0x80
    b L_80173EF0
L_80174188:
    li r30, 0x0
L_8017418C:
    mulli r9, r30, 0xa
    lbz r11, 0x0(r22)
    addi r22, r22, 0x1
    subi r9, r9, 0x30
    add r30, r9, r26
    extsb r26, r11
    subi r0, r26, 0x30
    cmplwi r0, 0x9
    ble L_8017418C
    mr r17, r30
    b L_80173EFC
L_801741B8:
    ori r24, r24, 0x8
    b L_80173EF0
L_801741C0:
    ori r24, r24, 0x40
    b L_80173EF0
L_801741C8:
    lbz r0, 0x0(r22)
    cmpwi r0, 0x6c
    bne L_801741E0
    addi r22, r22, 0x1
L_801741D8:
    ori r24, r24, 0x20
    b L_80173EF0
L_801741E0:
    ori r24, r24, 0x10
    b L_80173EF0
L_801741E8:
    lbz r11, 0x0(r29)
    addi r27, r1, 0x10
    extsb r9, r11
    addi r0, r9, 0x1
    cmplwi r0, 0x8
    bgt L_80174218
    lwz r0, 0x8(r29)
    slwi r9, r9, 2
    addi r11, r11, 0x1
    add r9, r0, r9
    stb r11, 0x0(r29)
    b L_80174238
L_80174218:
    cmpwi r9, 0x7
    bgt L_8017422C
    lwz r9, 0x4(r29)
    stb r18, 0x0(r29)
    b L_80174230
L_8017422C:
    lwz r9, 0x4(r29)
L_80174230:
    addi r0, r9, 0x4
    stw r0, 0x4(r29)
L_80174238:
    lbz r0, 0x3(r9)
    li r9, 0x1
    stb r0, 0x0(r27)
    stw r9, 0x178(r1)
    b L_80174D4C
L_8017424C:
    ori r24, r24, 0x10
L_80174250:
    andi. r11, r24, 0x20
    beq L_801742C8
    lbz r9, 0x0(r29)
    extsb r11, r9
    addi r0, r11, 0x2
    cmplwi r0, 0x8
    bgt L_8017429C
    andi. r0, r9, 0x1
    beq L_8017427C
    addi r0, r9, 0x1
    stb r0, 0x0(r29)
L_8017427C:
    lbz r9, 0x0(r29)
    lwz r11, 0x8(r29)
    extsb r0, r9
    addi r9, r9, 0x2
    slwi r0, r0, 2
    stb r9, 0x0(r29)
    add r3, r11, r0
    b L_801742BC
L_8017429C:
    cmpwi r11, 0x7
    bgt L_801742B0
    lwz r3, 0x4(r29)
    stb r18, 0x0(r29)
    b L_801742B4
L_801742B0:
    lwz r3, 0x4(r29)
L_801742B4:
    addi r0, r3, 0x8
    stw r0, 0x4(r29)
L_801742BC:
    lwz r30, 0x0(r3)
    lwz r31, 0x4(r3)
    b L_801743AC
L_801742C8:
    andi. r9, r24, 0x10
    beq L_801742F8
    lbz r11, 0x0(r29)
    extsb r9, r11
    addi r0, r9, 0x1
    cmplwi r0, 0x8
    ble L_80174368
    cmpwi r9, 0x7
    bgt L_80174394
    lwz r9, 0x4(r29)
    stb r18, 0x0(r29)
    b L_80174398
L_801742F8:
    andi. r11, r24, 0x40
    beq L_80174354
    lbz r11, 0x0(r29)
    extsb r9, r11
    addi r0, r9, 0x1
    cmplwi r0, 0x8
    bgt L_8017432C
    lwz r0, 0x8(r29)
    slwi r9, r9, 2
    addi r11, r11, 0x1
    add r9, r0, r9
    stb r11, 0x0(r29)
    b L_8017434C
L_8017432C:
    cmpwi r9, 0x7
    bgt L_80174340
    lwz r9, 0x4(r29)
    stb r18, 0x0(r29)
    b L_80174344
L_80174340:
    lwz r9, 0x4(r29)
L_80174344:
    addi r0, r9, 0x4
    stw r0, 0x4(r29)
L_8017434C:
    lha r0, 0x2(r9)
    b L_801743A4
L_80174354:
    lbz r11, 0x0(r29)
    extsb r9, r11
    addi r0, r9, 0x1
    cmplwi r0, 0x8
    bgt L_80174380
L_80174368:
    lwz r0, 0x8(r29)
    slwi r9, r9, 2
    addi r11, r11, 0x1
    add r9, r0, r9
    stb r11, 0x0(r29)
    b L_801743A0
L_80174380:
    cmpwi r9, 0x7
    bgt L_80174394
    lwz r9, 0x4(r29)
    stb r18, 0x0(r29)
    b L_80174398
L_80174394:
    lwz r9, 0x4(r29)
L_80174398:
    addi r0, r9, 0x4
    stw r0, 0x4(r29)
L_801743A0:
    lwz r0, 0x0(r9)
L_801743A4:
    mr r31, r0
    srawi r30, r0, 31
L_801743AC:
    cmpwi r30, 0x0
    bge L_801743C4
    li r0, 0x2d
    subfic r31, r31, 0x0
    subfze r30, r30
    stb r0, 0x172(r1)
L_801743C4:
    li r0, 0x1
    b L_80174BC0
L_801743CC:
    li r5, 0x0
    cmpwi r25, -0x1
    bne L_801743DC
    li r25, 0x6
L_801743DC:
    lbz r10, 0x1(r29)
    extsb r9, r10
    cmpwi r9, 0x7
    bgt L_80174408
    slwi r9, r9, 3
    lwz r11, 0x8(r29)
    addi r9, r9, 0x20
    addi r0, r10, 0x1
    add r9, r11, r9
    stb r0, 0x1(r29)
    b L_80174414
L_80174408:
    lwz r9, 0x4(r29)
    addi r0, r9, 0x8
    stw r0, 0x4(r29)
L_80174414:
    lfd f31, 0x0(r9)
    cmpwi cr4, r26, 0x67
    beq cr4, L_80174428
    cmpwi r26, 0x47
    bne L_801744AC
L_80174428:
    lis r9, lbl_8049C5F0@ha
    lfd f0, lbl_8049C5F0@l(r9)
    fcmpu cr0, f31, f0
    beq L_8017444C
    fmr f1, f31
    bge L_80174444
    fneg f1, f31
L_80174444:
    bl __ieee754_log10
    b L_80174454
L_8017444C:
    lis r9, lbl_8049C5F8@ha
    lfd f1, lbl_8049C5F8@l(r9)
L_80174454:
    lis r9, lbl_8049C600@ha
    lfd f0, lbl_8049C600@l(r9)
    fcmpu cr0, f1, f0
    blt L_80174490
    xoris r0, r25, 0x8000
    stw r0, 0x19c(r1)
    lis r9, 0x4330
    lis r11, lbl_8049C608@ha
    stw r9, 0x198(r1)
    lfd f13, lbl_8049C608@l(r11)
    lfd f0, 0x198(r1)
    fsub f0, f0, f13
    fcmpu cr0, f1, f0
    cror 3, 2, 1
    bns L_801744A4
L_80174490:
    li r0, 0x45
    bne cr4, L_8017449C
    li r0, 0x65
L_8017449C:
    mr r26, r0
    b L_801744A8
L_801744A4:
    li r26, 0x66
L_801744A8:
    li r5, 0x1
L_801744AC:
    andi. r0, r24, 0x1
    beq L_801744C4
    cmpwi r25, 0x0
    bne L_801744C0
    li r25, 0x1
L_801744C0:
    li r5, 0x0
L_801744C4:
    fmr f1, f31
    extsb r4, r26
    addi r6, r1, 0x172
    mr r3, r25
    bl fftoa
    mr r27, r3
    bl strlen
    stw r3, 0x178(r1)
    andi. r0, r24, 0x200
    beq L_80174D50
    add r5, r27, r3
    addi r6, r1, 0x178
    mr r3, r27
    mr r4, r3
    b L_80174D18
L_80174500:
    andi. r0, r24, 0x20
    beq L_8017456C
    lbz r11, 0x0(r29)
    extsb r9, r11
    addi r0, r9, 0x1
    cmplwi r0, 0x8
    bgt L_80174534
    lwz r0, 0x8(r29)
    slwi r9, r9, 2
    addi r11, r11, 0x1
    add r8, r0, r9
    stb r11, 0x0(r29)
    b L_80174554
L_80174534:
    cmpwi r9, 0x7
    bgt L_80174548
    lwz r8, 0x4(r29)
    stb r18, 0x0(r29)
    b L_8017454C
L_80174548:
    lwz r8, 0x4(r29)
L_8017454C:
    addi r0, r8, 0x4
    stw r0, 0x4(r29)
L_80174554:
    mr r10, r14
    lwz r11, 0x0(r8)
    srawi r9, r14, 31
    stw r9, 0x0(r11)
    stw r10, 0x4(r11)
    b L_80173DDC
L_8017456C:
    andi. r9, r24, 0x10
    beq L_8017459C
    lbz r11, 0x0(r29)
    extsb r9, r11
    addi r0, r9, 0x1
    cmplwi r0, 0x8
    ble L_80174610
    cmpwi r9, 0x7
    bgt L_8017463C
    lwz r9, 0x4(r29)
    stb r18, 0x0(r29)
    b L_80174640
L_8017459C:
    andi. r11, r24, 0x40
    beq L_801745FC
    lbz r11, 0x0(r29)
    extsb r9, r11
    addi r0, r9, 0x1
    cmplwi r0, 0x8
    bgt L_801745D0
    lwz r0, 0x8(r29)
    slwi r9, r9, 2
    addi r11, r11, 0x1
    add r9, r0, r9
    stb r11, 0x0(r29)
    b L_801745F0
L_801745D0:
    cmpwi r9, 0x7
    bgt L_801745E4
    lwz r9, 0x4(r29)
    stb r18, 0x0(r29)
    b L_801745E8
L_801745E4:
    lwz r9, 0x4(r29)
L_801745E8:
    addi r0, r9, 0x4
    stw r0, 0x4(r29)
L_801745F0:
    lwz r9, 0x0(r9)
    sth r14, 0x0(r9)
    b L_80173DDC
L_801745FC:
    lbz r11, 0x0(r29)
    extsb r9, r11
    addi r0, r9, 0x1
    cmplwi r0, 0x8
    bgt L_80174628
L_80174610:
    lwz r0, 0x8(r29)
    slwi r9, r9, 2
    addi r11, r11, 0x1
    add r9, r0, r9
    stb r11, 0x0(r29)
    b L_80174648
L_80174628:
    cmpwi r9, 0x7
    bgt L_8017463C
    lwz r9, 0x4(r29)
    stb r18, 0x0(r29)
    b L_80174640
L_8017463C:
    lwz r9, 0x4(r29)
L_80174640:
    addi r0, r9, 0x4
    stw r0, 0x4(r29)
L_80174648:
    lwz r9, 0x0(r9)
    stw r14, 0x0(r9)
    b L_80173DDC
L_80174654:
    ori r24, r24, 0x10
L_80174658:
    andi. r0, r24, 0x20
    beq L_801746D0
    lbz r9, 0x0(r29)
    extsb r11, r9
    addi r0, r11, 0x2
    cmplwi r0, 0x8
    bgt L_801746A4
    andi. r11, r9, 0x1
    beq L_80174684
    addi r0, r9, 0x1
    stb r0, 0x0(r29)
L_80174684:
    lbz r9, 0x0(r29)
    lwz r11, 0x8(r29)
    extsb r0, r9
    addi r9, r9, 0x2
    slwi r0, r0, 2
    stb r9, 0x0(r29)
    add r3, r11, r0
    b L_801746C4
L_801746A4:
    cmpwi r11, 0x7
    bgt L_801746B8
    lwz r3, 0x4(r29)
    stb r18, 0x0(r29)
    b L_801746BC
L_801746B8:
    lwz r3, 0x4(r29)
L_801746BC:
    addi r0, r3, 0x8
    stw r0, 0x4(r29)
L_801746C4:
    lwz r30, 0x0(r3)
    lwz r31, 0x4(r3)
    b L_801747B0
L_801746D0:
    andi. r0, r24, 0x10
    beq L_80174700
    lbz r11, 0x0(r29)
    extsb r9, r11
    addi r0, r9, 0x1
    cmplwi r0, 0x8
    ble L_80174770
    cmpwi r9, 0x7
    bgt L_8017479C
    lwz r9, 0x4(r29)
    stb r18, 0x0(r29)
    b L_801747A0
L_80174700:
    andi. r9, r24, 0x40
    beq L_8017475C
    lbz r11, 0x0(r29)
    extsb r9, r11
    addi r0, r9, 0x1
    cmplwi r0, 0x8
    bgt L_80174734
    lwz r0, 0x8(r29)
    slwi r9, r9, 2
    addi r11, r11, 0x1
    add r9, r0, r9
    stb r11, 0x0(r29)
    b L_80174754
L_80174734:
    cmpwi r9, 0x7
    bgt L_80174748
    lwz r9, 0x4(r29)
    stb r18, 0x0(r29)
    b L_8017474C
L_80174748:
    lwz r9, 0x4(r29)
L_8017474C:
    addi r0, r9, 0x4
    stw r0, 0x4(r29)
L_80174754:
    lhz r31, 0x2(r9)
    b L_801747AC
L_8017475C:
    lbz r11, 0x0(r29)
    extsb r9, r11
    addi r0, r9, 0x1
    cmplwi r0, 0x8
    bgt L_80174788
L_80174770:
    lwz r0, 0x8(r29)
    slwi r9, r9, 2
    addi r11, r11, 0x1
    add r9, r0, r9
    stb r11, 0x0(r29)
    b L_801747A8
L_80174788:
    cmpwi r9, 0x7
    bgt L_8017479C
    lwz r9, 0x4(r29)
    stb r18, 0x0(r29)
    b L_801747A0
L_8017479C:
    lwz r9, 0x4(r29)
L_801747A0:
    addi r0, r9, 0x4
    stw r0, 0x4(r29)
L_801747A8:
    lwz r31, 0x0(r9)
L_801747AC:
    li r30, 0x0
L_801747B0:
    li r0, 0x0
    b L_80174BBC
L_801747B8:
    lbz r11, 0x0(r29)
    extsb r9, r11
    addi r0, r9, 0x1
    cmplwi r0, 0x8
    bgt L_801747E4
    lwz r0, 0x8(r29)
    slwi r9, r9, 2
    addi r11, r11, 0x1
    add r10, r0, r9
    stb r11, 0x0(r29)
    b L_80174804
L_801747E4:
    cmpwi r9, 0x7
    bgt L_801747F8
    lwz r10, 0x4(r29)
    stb r18, 0x0(r29)
    b L_801747FC
L_801747F8:
    lwz r10, 0x4(r29)
L_801747FC:
    addi r0, r10, 0x4
    stw r0, 0x4(r29)
L_80174804:
    lwz r31, 0x0(r10)
    lis r9, lbl_8049C5A0@ha
    addi r9, r9, lbl_8049C5A0@l
    li r0, 0x2
    stw r9, 0x180(r1)
    ori r24, r24, 0x2
    li r30, 0x0
    li r26, 0x78
    b L_80174BBC
L_80174828:
    lbz r11, 0x0(r29)
    extsb r9, r11
    addi r0, r9, 0x1
    cmplwi r0, 0x8
    bgt L_80174854
    lwz r0, 0x8(r29)
    slwi r9, r9, 2
    addi r11, r11, 0x1
    add r3, r0, r9
    stb r11, 0x0(r29)
    b L_80174874
L_80174854:
    cmpwi r9, 0x7
    bgt L_80174868
    lwz r3, 0x4(r29)
    stb r18, 0x0(r29)
    b L_8017486C
L_80174868:
    lwz r3, 0x4(r29)
L_8017486C:
    addi r0, r3, 0x4
    stw r0, 0x4(r29)
L_80174874:
    lwz r27, 0x0(r3)
    cmpwi r27, 0x0
    bne L_80174888
    lis r9, lbl_8049C5B4@ha
    addi r27, r9, lbl_8049C5B4@l
L_80174888:
    cmpwi r25, 0x0
    blt L_801748C0
    mr r3, r27
    li r4, 0x0
    mr r5, r25
    bl memchr
    mr. r3, r3
    beq L_801748B8
    subf r0, r27, r3
    cmpw r0, r25
    stw r0, 0x178(r1)
    ble L_80174D4C
L_801748B8:
    stw r25, 0x178(r1)
    b L_80174D4C
L_801748C0:
    mr r3, r27
    bl strlen
    stw r3, 0x178(r1)
    b L_80174D4C
L_801748D0:
    ori r24, r24, 0x10
L_801748D4:
    andi. r0, r24, 0x20
    beq L_8017494C
    lbz r9, 0x0(r29)
    extsb r11, r9
    addi r0, r11, 0x2
    cmplwi r0, 0x8
    bgt L_80174920
    andi. r11, r9, 0x1
    beq L_80174900
    addi r0, r9, 0x1
    stb r0, 0x0(r29)
L_80174900:
    lbz r9, 0x0(r29)
    lwz r11, 0x8(r29)
    extsb r0, r9
    addi r9, r9, 0x2
    slwi r0, r0, 2
    stb r9, 0x0(r29)
    add r3, r11, r0
    b L_80174940
L_80174920:
    cmpwi r11, 0x7
    bgt L_80174934
    lwz r3, 0x4(r29)
    stb r18, 0x0(r29)
    b L_80174938
L_80174934:
    lwz r3, 0x4(r29)
L_80174938:
    addi r0, r3, 0x8
    stw r0, 0x4(r29)
L_80174940:
    lwz r30, 0x0(r3)
    lwz r31, 0x4(r3)
    b L_80174A2C
L_8017494C:
    andi. r0, r24, 0x10
    beq L_8017497C
    lbz r11, 0x0(r29)
    extsb r9, r11
    addi r0, r9, 0x1
    cmplwi r0, 0x8
    ble L_801749EC
    cmpwi r9, 0x7
    bgt L_80174A18
    lwz r9, 0x4(r29)
    stb r18, 0x0(r29)
    b L_80174A1C
L_8017497C:
    andi. r9, r24, 0x40
    beq L_801749D8
    lbz r11, 0x0(r29)
    extsb r9, r11
    addi r0, r9, 0x1
    cmplwi r0, 0x8
    bgt L_801749B0
    lwz r0, 0x8(r29)
    slwi r9, r9, 2
    addi r11, r11, 0x1
    add r9, r0, r9
    stb r11, 0x0(r29)
    b L_801749D0
L_801749B0:
    cmpwi r9, 0x7
    bgt L_801749C4
    lwz r9, 0x4(r29)
    stb r18, 0x0(r29)
    b L_801749C8
L_801749C4:
    lwz r9, 0x4(r29)
L_801749C8:
    addi r0, r9, 0x4
    stw r0, 0x4(r29)
L_801749D0:
    lhz r31, 0x2(r9)
    b L_80174A28
L_801749D8:
    lbz r11, 0x0(r29)
    extsb r9, r11
    addi r0, r9, 0x1
    cmplwi r0, 0x8
    bgt L_80174A04
L_801749EC:
    lwz r0, 0x8(r29)
    slwi r9, r9, 2
    addi r11, r11, 0x1
    add r9, r0, r9
    stb r11, 0x0(r29)
    b L_80174A24
L_80174A04:
    cmpwi r9, 0x7
    bgt L_80174A18
    lwz r9, 0x4(r29)
    stb r18, 0x0(r29)
    b L_80174A1C
L_80174A18:
    lwz r9, 0x4(r29)
L_80174A1C:
    addi r0, r9, 0x4
    stw r0, 0x4(r29)
L_80174A24:
    lwz r31, 0x0(r9)
L_80174A28:
    li r30, 0x0
L_80174A2C:
    li r0, 0x1
    b L_80174BBC
L_80174A34:
    lis r9, lbl_8049C5BC@ha
    addi r9, r9, lbl_8049C5BC@l
    b L_80174A48
L_80174A40:
    lis r9, lbl_8049C5A0@ha
    addi r9, r9, lbl_8049C5A0@l
L_80174A48:
    stw r9, 0x180(r1)
    andi. r11, r24, 0x20
    beq L_80174AC4
    lbz r9, 0x0(r29)
    extsb r11, r9
    addi r0, r11, 0x2
    cmplwi r0, 0x8
    bgt L_80174A98
    andi. r0, r9, 0x1
    beq L_80174A78
    addi r0, r9, 0x1
    stb r0, 0x0(r29)
L_80174A78:
    lbz r9, 0x0(r29)
    lwz r11, 0x8(r29)
    extsb r0, r9
    addi r9, r9, 0x2
    slwi r0, r0, 2
    stb r9, 0x0(r29)
    add r3, r11, r0
    b L_80174AB8
L_80174A98:
    cmpwi r11, 0x7
    bgt L_80174AAC
    lwz r3, 0x4(r29)
    stb r18, 0x0(r29)
    b L_80174AB0
L_80174AAC:
    lwz r3, 0x4(r29)
L_80174AB0:
    addi r0, r3, 0x8
    stw r0, 0x4(r29)
L_80174AB8:
    lwz r30, 0x0(r3)
    lwz r31, 0x4(r3)
    b L_80174BA4
L_80174AC4:
    andi. r9, r24, 0x10
    beq L_80174AF4
    lbz r11, 0x0(r29)
    extsb r9, r11
    addi r0, r9, 0x1
    cmplwi r0, 0x8
    ble L_80174B64
    cmpwi r9, 0x7
    bgt L_80174B90
    lwz r9, 0x4(r29)
    stb r18, 0x0(r29)
    b L_80174B94
L_80174AF4:
    andi. r11, r24, 0x40
    beq L_80174B50
    lbz r11, 0x0(r29)
    extsb r9, r11
    addi r0, r9, 0x1
    cmplwi r0, 0x8
    bgt L_80174B28
    lwz r0, 0x8(r29)
    slwi r9, r9, 2
    addi r11, r11, 0x1
    add r9, r0, r9
    stb r11, 0x0(r29)
    b L_80174B48
L_80174B28:
    cmpwi r9, 0x7
    bgt L_80174B3C
    lwz r9, 0x4(r29)
    stb r18, 0x0(r29)
    b L_80174B40
L_80174B3C:
    lwz r9, 0x4(r29)
L_80174B40:
    addi r0, r9, 0x4
    stw r0, 0x4(r29)
L_80174B48:
    lhz r31, 0x2(r9)
    b L_80174BA0
L_80174B50:
    lbz r11, 0x0(r29)
    extsb r9, r11
    addi r0, r9, 0x1
    cmplwi r0, 0x8
    bgt L_80174B7C
L_80174B64:
    lwz r0, 0x8(r29)
    slwi r9, r9, 2
    addi r11, r11, 0x1
    add r9, r0, r9
    stb r11, 0x0(r29)
    b L_80174B9C
L_80174B7C:
    cmpwi r9, 0x7
    bgt L_80174B90
    lwz r9, 0x4(r29)
    stb r18, 0x0(r29)
    b L_80174B94
L_80174B90:
    lwz r9, 0x4(r29)
L_80174B94:
    addi r0, r9, 0x4
    stw r0, 0x4(r29)
L_80174B9C:
    lwz r31, 0x0(r9)
L_80174BA0:
    li r30, 0x0
L_80174BA4:
    li r0, 0x2
    andi. r9, r24, 0x1
    beq L_80174BBC
    or. r11, r30, r31
    beq L_80174BBC
    ori r24, r24, 0x2
L_80174BBC:
    stb r16, 0x172(r1)
L_80174BC0:
    mr. r15, r25
    mcrf cr7, cr0
    blt cr7, L_80174BD0
    rlwinm r24, r24, 0, 25, 23
L_80174BD0:
    addi r27, r1, 0x16c
    or. r9, r30, r31
    mr r25, r27
    bne L_80174BE8
    cmpwi cr4, r0, 0x1
    beq cr7, L_80174CFC
L_80174BE8:
    cmpwi cr4, r0, 0x1
    beq cr4, L_80174C8C
    cmplwi r0, 0x1
    blt L_80174C04
    cmpwi r0, 0x2
    beq L_80174CB0
    b L_80174CE4
L_80174C04:
    srwi r0, r31, 3
    slwi r8, r30, 29
    or r10, r8, r0
    clrlwi r11, r31, 29
    srwi r9, r30, 3
    addi r11, r11, 0x30
    mr r30, r9
    mr r31, r10
    stbu r11, -0x1(r27)
    or. r0, r30, r31
    bne L_80174C04
    andi. r9, r24, 0x1
    beq L_80174CFC
    cmpwi r11, 0x30
    beq L_80174CFC
    li r0, 0x30
    stbu r0, -0x1(r27)
    b L_80174CFC
L_80174C4C:
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
    stbu r0, -0x1(r27)
    li r6, 0xa
    crclr 6
    bl __udivdi3
    mr r30, r3
    mr r31, r4
L_80174C8C:
    cmplwi r30, 0x0
    bgt L_80174C4C
    cmpwi r30, 0x0
    bne L_80174CA4
    cmplwi r31, 0x9
    bgt L_80174C4C
L_80174CA4:
    addi r0, r31, 0x30
    stbu r0, -0x1(r27)
    b L_80174CFC
L_80174CB0:
    srwi r11, r31, 4
    slwi r7, r30, 28
    or r10, r7, r11
    clrlwi r0, r31, 28
    lwz r11, 0x180(r1)
    srwi r9, r30, 4
    mr r30, r9
    mr r31, r10
    lbzx r8, r11, r0
    or. r0, r30, r31
    stbu r8, -0x1(r27)
    bne L_80174CB0
    b L_80174CFC
L_80174CE4:
    lis r9, lbl_8049C5D0@ha
    addi r27, r9, lbl_8049C5D0@l
    mr r3, r27
    bl strlen
    stw r3, 0x178(r1)
    b L_80174D50
L_80174CFC:
    bne cr4, L_80174D24
    andi. r0, r24, 0x200
    beq L_80174D24
    mr r4, r27
    mr r5, r25
    addi r3, r1, 0x10
    addi r6, r1, 0x178
L_80174D18:
    bl __group_digits
    mr r27, r3
    b L_80174D50
L_80174D24:
    subf r9, r27, r1
    addi r9, r9, 0x16c
    stw r9, 0x178(r1)
    b L_80174D50
L_80174D34:
    cmpwi r26, 0x0
    beq L_80175538
    li r0, 0x1
    stb r26, 0x10(r1)
    stw r0, 0x178(r1)
    addi r27, r1, 0x10
L_80174D4C:
    stb r16, 0x172(r1)
L_80174D50:
    lwz r23, 0x178(r1)
    cmpw r23, r15
    bge L_80174D60
    mr r23, r15
L_80174D60:
    lbz r0, 0x172(r1)
    cmpwi r0, 0x0
    beq L_80174D74
    addi r23, r23, 0x1
    b L_80174D80
L_80174D74:
    andi. r0, r24, 0x2
    beq L_80174D80
    addi r23, r23, 0x2
L_80174D80:
    andi. r9, r24, 0x84
    bne L_80174EF4
    subf. r30, r23, r17
    ble L_80174EF4
    cmpwi r30, 0x10
    lis r25, lbl_8049C580@ha
    ble L_80174E5C
    lis r19, lbl_8049C580@ha
    addi r31, r25, lbl_8049C580@l
    li r20, 0x0
    li r21, 0x1
L_80174DAC:
    lhz r0, 0xc(r28)
    andi. r11, r0, 0x200
    beq L_80174E2C
    lwz r5, 0x8(r28)
    cmpwi r5, 0x10
    ble L_80174E04
    lwz r11, lbl_8049C580@l(r19)
    lwz r10, 0x4(r31)
    lwz r8, 0x8(r31)
    lwz r0, 0xc(r31)
    lwz r9, 0x0(r28)
    stw r0, 0xc(r9)
    stw r11, 0x0(r9)
    stw r10, 0x4(r9)
    stw r8, 0x8(r9)
    lwz r11, 0x0(r28)
    lwz r9, 0x8(r28)
    addi r11, r11, 0x10
    subi r9, r9, 0x10
    stw r11, 0x0(r28)
    stw r9, 0x8(r28)
    b L_80174E50
L_80174E04:
    lwz r3, 0x0(r28)
    addi r4, r25, lbl_8049C580@l
    crclr 6
    bl memcpy
    lwz r0, 0x0(r28)
    lwz r9, 0x8(r28)
    stw r20, 0x8(r28)
    add r0, r0, r9
    stw r0, 0x0(r28)
    b L_80174E50
L_80174E2C:
    lwz r0, 0xc(r28)
    cmpwi r0, 0x0
    bne L_80174E3C
    sth r21, 0xe(r28)
L_80174E3C:
    lha r3, 0xe(r28)
    addi r4, r25, lbl_8049C580@l
    li r5, 0x10
    li r6, 0x0
    bl _vfwrite
L_80174E50:
    subi r30, r30, 0x10
    cmpwi r30, 0x10
    bgt L_80174DAC
L_80174E5C:
    lhz r0, 0xc(r28)
    andi. r9, r0, 0x200
    beq L_80174ECC
    lwz r5, 0x8(r28)
    cmpw r5, r30
    ble L_80174EA4
    lwz r3, 0x0(r28)
    addi r4, r25, lbl_8049C580@l
    mr r5, r30
    crclr 6
    bl memcpy
    lwz r0, 0x0(r28)
    lwz r9, 0x8(r28)
    add r0, r0, r30
    subf r9, r30, r9
    stw r0, 0x0(r28)
    stw r9, 0x8(r28)
    b L_80174EF4
L_80174EA4:
    lwz r3, 0x0(r28)
    addi r4, r25, lbl_8049C580@l
    crclr 6
    bl memcpy
    lwz r0, 0x0(r28)
    lwz r9, 0x8(r28)
    stw r16, 0x8(r28)
    add r0, r0, r9
    stw r0, 0x0(r28)
    b L_80174EF4
L_80174ECC:
    lwz r0, 0xc(r28)
    cmpwi r0, 0x0
    bne L_80174EE0
    li r0, 0x1
    sth r0, 0xe(r28)
L_80174EE0:
    lha r3, 0xe(r28)
    addi r4, r25, lbl_8049C580@l
    mr r5, r30
    li r6, 0x0
    bl _vfwrite
L_80174EF4:
    lbz r11, 0x172(r1)
    extsb r30, r11
    cmpwi r30, 0x0
    beq L_80174F84
    lhz r0, 0xc(r28)
    andi. r9, r0, 0x200
    beq L_80174F58
    lwz r5, 0x8(r28)
    cmpwi r5, 0x1
    ble L_80174F38
    lwz r9, 0x0(r28)
    stb r11, 0x0(r9)
    lwz r11, 0x0(r28)
    lwz r9, 0x8(r28)
    addi r11, r11, 0x1
    subi r9, r9, 0x1
    b L_80174FC8
L_80174F38:
    lwz r3, 0x0(r28)
    addi r4, r1, 0x172
    crclr 6
    bl memcpy
    lwz r0, 0x0(r28)
    lwz r9, 0x8(r28)
    stw r16, 0x8(r28)
    b L_80174FF0
L_80174F58:
    lwz r0, 0xc(r28)
    cmpwi r0, 0x0
    bne L_80174F6C
    li r0, 0x1
    sth r0, 0xe(r28)
L_80174F6C:
    lha r3, 0xe(r28)
    addi r4, r1, 0x172
    li r5, 0x1
    li r6, 0x0
    bl _vfwrite
    b L_80175024
L_80174F84:
    andi. r0, r24, 0x2
    beq L_80175024
    lhz r9, 0xc(r28)
    clrlwi r0, r26, 24
    ori r0, r0, 0x3000
    sth r0, 0x17c(r1)
    andi. r11, r9, 0x200
    beq L_80174FFC
    lwz r5, 0x8(r28)
    cmpwi r5, 0x2
    ble L_80174FD4
    lwz r9, 0x0(r28)
    sth r0, 0x0(r9)
    lwz r11, 0x0(r28)
    lwz r9, 0x8(r28)
    addi r11, r11, 0x2
    subi r9, r9, 0x2
L_80174FC8:
    stw r11, 0x0(r28)
    stw r9, 0x8(r28)
    b L_80175024
L_80174FD4:
    lwz r3, 0x0(r28)
    addi r4, r1, 0x17c
    crclr 6
    bl memcpy
    lwz r0, 0x0(r28)
    lwz r9, 0x8(r28)
    stw r30, 0x8(r28)
L_80174FF0:
    add r0, r0, r9
    stw r0, 0x0(r28)
    b L_80175024
L_80174FFC:
    lwz r0, 0xc(r28)
    cmpwi r0, 0x0
    bne L_80175010
    li r0, 0x1
    sth r0, 0xe(r28)
L_80175010:
    lha r3, 0xe(r28)
    addi r4, r1, 0x17c
    li r5, 0x2
    li r6, 0x0
    bl _vfwrite
L_80175024:
    andi. r0, r24, 0x84
    cmpwi r0, 0x80
    bne L_8017519C
    subf. r30, r23, r17
    ble L_8017519C
    cmpwi r30, 0x10
    lis r25, lbl_8049C590@ha
    ble L_80175104
    lis r19, lbl_8049C590@ha
    addi r26, r25, lbl_8049C590@l
    li r20, 0x0
    li r21, 0x1
L_80175054:
    lhz r0, 0xc(r28)
    andi. r9, r0, 0x200
    beq L_801750D4
    lwz r5, 0x8(r28)
    cmpwi r5, 0x10
    ble L_801750AC
    lwz r11, lbl_8049C590@l(r19)
    lwz r10, 0x4(r26)
    lwz r8, 0x8(r26)
    lwz r0, 0xc(r26)
    lwz r9, 0x0(r28)
    stw r0, 0xc(r9)
    stw r11, 0x0(r9)
    stw r10, 0x4(r9)
    stw r8, 0x8(r9)
    lwz r11, 0x0(r28)
    lwz r9, 0x8(r28)
    addi r11, r11, 0x10
    subi r9, r9, 0x10
    stw r11, 0x0(r28)
    stw r9, 0x8(r28)
    b L_801750F8
L_801750AC:
    lwz r3, 0x0(r28)
    addi r4, r25, lbl_8049C590@l
    crclr 6
    bl memcpy
    lwz r0, 0x0(r28)
    lwz r9, 0x8(r28)
    stw r20, 0x8(r28)
    add r0, r0, r9
    stw r0, 0x0(r28)
    b L_801750F8
L_801750D4:
    lwz r0, 0xc(r28)
    cmpwi r0, 0x0
    bne L_801750E4
    sth r21, 0xe(r28)
L_801750E4:
    lha r3, 0xe(r28)
    addi r4, r25, lbl_8049C590@l
    li r5, 0x10
    li r6, 0x0
    bl _vfwrite
L_801750F8:
    subi r30, r30, 0x10
    cmpwi r30, 0x10
    bgt L_80175054
L_80175104:
    lhz r0, 0xc(r28)
    andi. r9, r0, 0x200
    beq L_80175174
    lwz r5, 0x8(r28)
    cmpw r5, r30
    ble L_8017514C
    lwz r3, 0x0(r28)
    addi r4, r25, lbl_8049C590@l
    mr r5, r30
    crclr 6
    bl memcpy
    lwz r0, 0x0(r28)
    lwz r9, 0x8(r28)
    add r0, r0, r30
    subf r9, r30, r9
    stw r0, 0x0(r28)
    stw r9, 0x8(r28)
    b L_8017519C
L_8017514C:
    lwz r3, 0x0(r28)
    addi r4, r25, lbl_8049C590@l
    crclr 6
    bl memcpy
    lwz r0, 0x0(r28)
    lwz r9, 0x8(r28)
    stw r16, 0x8(r28)
    add r0, r0, r9
    stw r0, 0x0(r28)
    b L_8017519C
L_80175174:
    lwz r0, 0xc(r28)
    cmpwi r0, 0x0
    bne L_80175188
    li r0, 0x1
    sth r0, 0xe(r28)
L_80175188:
    lha r3, 0xe(r28)
    addi r4, r25, lbl_8049C590@l
    mr r5, r30
    li r6, 0x0
    bl _vfwrite
L_8017519C:
    lwz r0, 0x178(r1)
    subf. r30, r0, r15
    ble L_8017530C
    cmpwi r30, 0x10
    lis r25, lbl_8049C590@ha
    ble L_80175274
    lis r19, lbl_8049C590@ha
    addi r26, r25, lbl_8049C590@l
    li r20, 0x0
    li r21, 0x1
L_801751C4:
    lhz r0, 0xc(r28)
    andi. r9, r0, 0x200
    beq L_80175244
    lwz r5, 0x8(r28)
    cmpwi r5, 0x10
    ble L_8017521C
    lwz r11, lbl_8049C590@l(r19)
    lwz r10, 0x4(r26)
    lwz r8, 0x8(r26)
    lwz r0, 0xc(r26)
    lwz r9, 0x0(r28)
    stw r0, 0xc(r9)
    stw r11, 0x0(r9)
    stw r10, 0x4(r9)
    stw r8, 0x8(r9)
    lwz r11, 0x0(r28)
    lwz r9, 0x8(r28)
    addi r11, r11, 0x10
    subi r9, r9, 0x10
    stw r11, 0x0(r28)
    stw r9, 0x8(r28)
    b L_80175268
L_8017521C:
    lwz r3, 0x0(r28)
    addi r4, r25, lbl_8049C590@l
    crclr 6
    bl memcpy
    lwz r0, 0x0(r28)
    lwz r9, 0x8(r28)
    stw r20, 0x8(r28)
    add r0, r0, r9
    stw r0, 0x0(r28)
    b L_80175268
L_80175244:
    lwz r0, 0xc(r28)
    cmpwi r0, 0x0
    bne L_80175254
    sth r21, 0xe(r28)
L_80175254:
    lha r3, 0xe(r28)
    addi r4, r25, lbl_8049C590@l
    li r5, 0x10
    li r6, 0x0
    bl _vfwrite
L_80175268:
    subi r30, r30, 0x10
    cmpwi r30, 0x10
    bgt L_801751C4
L_80175274:
    lhz r0, 0xc(r28)
    andi. r9, r0, 0x200
    beq L_801752E4
    lwz r5, 0x8(r28)
    cmpw r5, r30
    ble L_801752BC
    lwz r3, 0x0(r28)
    addi r4, r25, lbl_8049C590@l
    mr r5, r30
    crclr 6
    bl memcpy
    lwz r0, 0x0(r28)
    lwz r9, 0x8(r28)
    add r0, r0, r30
    subf r9, r30, r9
    stw r0, 0x0(r28)
    stw r9, 0x8(r28)
    b L_8017530C
L_801752BC:
    lwz r3, 0x0(r28)
    addi r4, r25, lbl_8049C590@l
    crclr 6
    bl memcpy
    lwz r0, 0x0(r28)
    lwz r9, 0x8(r28)
    stw r16, 0x8(r28)
    add r0, r0, r9
    stw r0, 0x0(r28)
    b L_8017530C
L_801752E4:
    lwz r0, 0xc(r28)
    cmpwi r0, 0x0
    bne L_801752F8
    li r0, 0x1
    sth r0, 0xe(r28)
L_801752F8:
    lha r3, 0xe(r28)
    addi r4, r25, lbl_8049C590@l
    mr r5, r30
    li r6, 0x0
    bl _vfwrite
L_8017530C:
    lhz r0, 0xc(r28)
    andi. r9, r0, 0x200
    beq L_80175384
    lwz r0, 0x8(r28)
    lwz r5, 0x178(r1)
    cmpw r0, r5
    ble L_80175358
    lwz r3, 0x0(r28)
    mr r4, r27
    crclr 6
    bl memcpy
    lwz r11, 0x178(r1)
    lwz r0, 0x0(r28)
    lwz r9, 0x8(r28)
    add r0, r0, r11
    subf r9, r11, r9
    stw r0, 0x0(r28)
    stw r9, 0x8(r28)
    b L_801753AC
L_80175358:
    lwz r3, 0x0(r28)
    mr r5, r0
    mr r4, r27
    crclr 6
    bl memcpy
    lwz r0, 0x0(r28)
    lwz r9, 0x8(r28)
    stw r16, 0x8(r28)
    add r0, r0, r9
    stw r0, 0x0(r28)
    b L_801753AC
L_80175384:
    lwz r0, 0xc(r28)
    cmpwi r0, 0x0
    bne L_80175398
    li r0, 0x1
    sth r0, 0xe(r28)
L_80175398:
    lha r3, 0xe(r28)
    mr r4, r27
    lwz r5, 0x178(r1)
    li r6, 0x0
    bl _vfwrite
L_801753AC:
    andi. r0, r24, 0x4
    beq L_80175520
    subf. r30, r23, r17
    ble L_80175520
    cmpwi r30, 0x10
    lis r25, lbl_8049C580@ha
    ble L_80175488
    lis r21, lbl_8049C580@ha
    addi r27, r25, lbl_8049C580@l
    li r24, 0x0
    li r26, 0x1
L_801753D8:
    lhz r0, 0xc(r28)
    andi. r9, r0, 0x200
    beq L_80175458
    lwz r5, 0x8(r28)
    cmpwi r5, 0x10
    ble L_80175430
    lwz r11, lbl_8049C580@l(r21)
    lwz r10, 0x4(r27)
    lwz r8, 0x8(r27)
    lwz r0, 0xc(r27)
    lwz r9, 0x0(r28)
    stw r0, 0xc(r9)
    stw r11, 0x0(r9)
    stw r10, 0x4(r9)
    stw r8, 0x8(r9)
    lwz r11, 0x0(r28)
    lwz r9, 0x8(r28)
    addi r11, r11, 0x10
    subi r9, r9, 0x10
    stw r11, 0x0(r28)
    stw r9, 0x8(r28)
    b L_8017547C
L_80175430:
    lwz r3, 0x0(r28)
    addi r4, r25, lbl_8049C580@l
    crclr 6
    bl memcpy
    lwz r0, 0x0(r28)
    lwz r9, 0x8(r28)
    stw r24, 0x8(r28)
    add r0, r0, r9
    stw r0, 0x0(r28)
    b L_8017547C
L_80175458:
    lwz r0, 0xc(r28)
    cmpwi r0, 0x0
    bne L_80175468
    sth r26, 0xe(r28)
L_80175468:
    lha r3, 0xe(r28)
    addi r4, r25, lbl_8049C580@l
    li r5, 0x10
    li r6, 0x0
    bl _vfwrite
L_8017547C:
    subi r30, r30, 0x10
    cmpwi r30, 0x10
    bgt L_801753D8
L_80175488:
    lhz r0, 0xc(r28)
    andi. r9, r0, 0x200
    beq L_801754F8
    lwz r5, 0x8(r28)
    cmpw r5, r30
    ble L_801754D0
    lwz r3, 0x0(r28)
    addi r4, r25, lbl_8049C580@l
    mr r5, r30
    crclr 6
    bl memcpy
    lwz r0, 0x0(r28)
    lwz r9, 0x8(r28)
    add r0, r0, r30
    subf r9, r30, r9
    stw r0, 0x0(r28)
    stw r9, 0x8(r28)
    b L_80175520
L_801754D0:
    lwz r3, 0x0(r28)
    addi r4, r25, lbl_8049C580@l
    crclr 6
    bl memcpy
    lwz r0, 0x0(r28)
    lwz r9, 0x8(r28)
    stw r16, 0x8(r28)
    add r0, r0, r9
    stw r0, 0x0(r28)
    b L_80175520
L_801754F8:
    lwz r0, 0xc(r28)
    cmpwi r0, 0x0
    bne L_8017550C
    li r0, 0x1
    sth r0, 0xe(r28)
L_8017550C:
    lha r3, 0xe(r28)
    addi r4, r25, lbl_8049C580@l
    mr r5, r30
    li r6, 0x0
    bl _vfwrite
L_80175520:
    mr r0, r23
    cmpw r0, r17
    bge L_80175530
    mr r0, r17
L_80175530:
    add r14, r14, r0
    b L_80173DDC
L_80175538:
    lhz r0, 0xc(r28)
    andi. r9, r0, 0x200
    bne L_80175558
    lha r3, 0xe(r28)
    li r4, 0x0
    li r5, 0x0
    li r6, 0x1
    bl _vfwrite
L_80175558:
    mr r3, r14
    lwz r0, 0x1fc(r1)
    lwz r12, 0x1a4(r1)
    mtlr r0
    lmw r14, 0x1a8(r1)
    lfd f31, 0x1f0(r1)
    mtcrf 8, r12
    addi r1, r1, 0x1f8
    blr
    // clang-format on
}
