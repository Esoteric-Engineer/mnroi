extern void fn_801712D4(void);
extern void __srefill(void);
extern void ungetc(void);
extern void fread(void);
extern void atof(void);
extern void strtol(void);
extern void strtoul(void);
extern void __sccl(void);
extern void* lbl_8066C3AC;
extern void* lbl_8066C3B0;
extern char lbl_8049C6A1[];
extern char lbl_8049C1E8[];

asm int __svfscanf(void* fp, const char* fmt, void* ap)
{
    // clang-format off
    nofralloc
    stwu    r1, -0x2c0(r1)
    mflr    r0
    stmw    r14, 0x278(r1)
    stw     r0, 0x2c4(r1)
    li      r18, 0x0
    addi    r0, r1, 0x26c
    lis     r9, lbl_8049C6A1@ha
    stw     r18, 0x26c(r1)
    stw     r0, 0x270(r1)
    addi    r15, r9, lbl_8049C6A1@l
    mr      r28, r3
    mr      r29, r5
    mr      r22, r4
    li      r23, 0x0
    li      r20, 0x0
    li      r24, 0x0
    addi    r14, r1, 0x268
    li      r21, 0x8
    lis     r16, lbl_8049C6A1@ha
    lis     r17, strtoul@ha
L_80170200:
    lwz     r3, lbl_8066C3B0
    mr      r5, r22
    lwz     r6, lbl_8066C3AC
    mr      r4, r14
    lwz     r7, 0x270(r1)
    bl      fn_801712D4
    lhz     r0, 0x268(r1)
    mr      r25, r3
    add     r22, r22, r25
    cmpwi   r0, 0x0
    beq     L_80170F9C
    cmpwi   r25, 0x1
    bne     L_80170294
    lbzx    r0, r15, r0
    andi.   r9, r0, 0x8
    beq     L_80170294
    addi    r30, r16, lbl_8049C6A1@l
    b       L_80170260
L_80170248:
    lwz     r9, 0x4(r28)
    addi    r0, r11, 0x1
    stw     r0, 0x0(r28)
    addi    r24, r24, 0x1
    subi    r9, r9, 0x1
    stw     r9, 0x4(r28)
L_80170260:
    lwz     r0, 0x4(r28)
    cmpwi   r0, 0x0
    bgt     L_8017027C
    mr      r3, r28
    bl      __srefill
    cmpwi   r3, 0x0
    bne     L_80170F9C
L_8017027C:
    lwz     r11, 0x0(r28)
    lbz     r0, 0x0(r11)
    lbzx    r9, r30, r0
    andi.   r0, r9, 0x8
    bne     L_80170248
    b       L_80170200
L_80170294:
    lhz     r0, 0x268(r1)
    cmpwi   r0, 0x25
    bne     L_801703A8
    li      r26, 0x0
    li      r30, 0x0
L_801702A8:
    lbz     r0, 0x0(r22)
    addi    r22, r22, 0x1
    extsb   r31, r0
    cmpwi   r31, 0x64
    beq     L_801705D8
    bgt     L_80170348
    cmpwi   r31, 0x47
    beq     L_80170480
    bgt     L_80170314
    cmpwi   r31, 0x39
    bgt     L_80170300
    cmpwi   r31, 0x30
    bge     L_80170434
    cmpwi   r31, 0x25
    beq     L_801703A8
    bgt     L_801702F4
    cmpwi   r31, 0x0
    beq     L_801705C0
    b       L_801705C8
L_801702F4:
    cmpwi   r31, 0x2a
    beq     L_80170414
    b       L_801705C8
L_80170300:
    cmpwi   r31, 0x44
    beq     L_801705D4
    cmpwi   r31, 0x45
    beq     L_80170480
    b       L_801705C8
L_80170314:
    cmpwi   r31, 0x58
    beq     L_80170478
    bgt     L_80170334
    cmpwi   r31, 0x4c
    beq     L_80170424
    cmpwi   r31, 0x4f
    beq     L_80170458
    b       L_801705C8
L_80170334:
    cmpwi   r31, 0x5b
    beq     L_80170490
    cmpwi   r31, 0x63
    beq     L_801704B0
    b       L_801705C8
L_80170348:
    cmpwi   r31, 0x6e
    beq     L_801704D0
    bgt     L_80170374
    cmpwi   r31, 0x68
    beq     L_8017042C
    blt     L_80170480
    cmpwi   r31, 0x69
    beq     L_80170444
    cmpwi   r31, 0x6c
    beq     L_8017041C
    b       L_801705C8
L_80170374:
    cmpwi   r31, 0x73
    beq     L_80170488
    bgt     L_80170394
    cmpwi   r31, 0x6f
    beq     L_8017045C
    cmpwi   r31, 0x70
    beq     L_801704BC
    b       L_801705C8
L_80170394:
    cmpwi   r31, 0x75
    beq     L_8017046C
    cmpwi   r31, 0x78
    beq     L_80170478
    b       L_801705C8
L_801703A8:
    li      r30, 0x0
    subf    r27, r25, r22
    cmpw    r30, r25
    bge     L_80170200
L_801703B8:
    lwz     r0, 0x4(r28)
    cmpwi   r0, 0x0
    bgt     L_801703D4
    mr      r3, r28
    bl      __srefill
    cmpwi   r3, 0x0
    bne     L_80170F88
L_801703D4:
    lwz     r11, 0x0(r28)
    lbz     r9, 0x0(r27)
    lbz     r0, 0x0(r11)
    cmpw    r0, r9
    bne     L_80170F9C
    lwz     r9, 0x4(r28)
    addi    r0, r11, 0x1
    addi    r30, r30, 0x1
    stw     r0, 0x0(r28)
    subi    r9, r9, 0x1
    addi    r24, r24, 0x1
    stw     r9, 0x4(r28)
    addi    r27, r27, 0x1
    cmpw    r30, r25
    blt     L_801703B8
    b       L_80170200
L_80170414:
    ori     r30, r30, 0x8
    b       L_801702A8
L_8017041C:
    ori     r30, r30, 0x1
    b       L_801702A8
L_80170424:
    ori     r30, r30, 0x2
    b       L_801702A8
L_8017042C:
    ori     r30, r30, 0x4
    b       L_801702A8
L_80170434:
    mulli   r9, r26, 0xa
    add     r9, r9, r31
    subi    r26, r9, 0x30
    b       L_801702A8
L_80170444:
    lis     r9, strtol@ha
    li      r31, 0x3
    addi    r18, r9, strtol@l
    li      r23, 0x0
    b       L_801705E8
L_80170458:
    ori     r30, r30, 0x1
L_8017045C:
    li      r31, 0x3
    addi    r18, r17, strtoul@l
    li      r23, 0x8
    b       L_801705E8
L_8017046C:
    li      r31, 0x3
    addi    r18, r17, strtoul@l
    b       L_801705E4
L_80170478:
    ori     r30, r30, 0x100
    b       L_801704C0
L_80170480:
    li      r31, 0x4
    b       L_801705E8
L_80170488:
    li      r31, 0x2
    b       L_801705E8
L_80170490:
    mr      r4, r22
    addi    r3, r1, 0x8
    crclr   4*cr1+eq
    bl      __sccl
    ori     r30, r30, 0x20
    mr      r22, r3
    li      r31, 0x1
    b       L_801705E8
L_801704B0:
    ori     r30, r30, 0x20
    li      r31, 0x0
    b       L_801705E8
L_801704BC:
    ori     r30, r30, 0x110
L_801704C0:
    li      r31, 0x3
    addi    r18, r17, strtoul@l
    li      r23, 0x10
    b       L_801705E8
L_801704D0:
    andi.   r0, r30, 0x8
    bne     L_80170200
    andi.   r9, r30, 0x4
    beq     L_80170538
    lbz     r11, 0x0(r29)
    extsb   r9, r11
    addi    r0, r9, 0x1
    cmplwi  r0, 0x8
    bgt     L_8017050C
    lwz     r0, 0x8(r29)
    slwi    r9, r9, 2
    addi    r11, r11, 0x1
    add     r9, r0, r9
    stb     r11, 0x0(r29)
    b       L_8017052C
L_8017050C:
    cmpwi   r9, 0x7
    bgt     L_80170520
    lwz     r9, 0x4(r29)
    stb     r21, 0x0(r29)
    b       L_80170524
L_80170520:
    lwz     r9, 0x4(r29)
L_80170524:
    addi    r0, r9, 0x4
    stw     r0, 0x4(r29)
L_8017052C:
    lwz     r9, 0x0(r9)
    sth     r24, 0x0(r9)
    b       L_80170200
L_80170538:
    andi.   r0, r30, 0x1
    beq     L_80170568
    lbz     r11, 0x0(r29)
    extsb   r9, r11
    addi    r0, r9, 0x1
    cmplwi  r0, 0x8
    ble     L_8017057C
    cmpwi   r9, 0x7
    bgt     L_801705A8
    lwz     r9, 0x4(r29)
    stb     r21, 0x0(r29)
    b       L_801705AC
L_80170568:
    lbz     r11, 0x0(r29)
    extsb   r9, r11
    addi    r0, r9, 0x1
    cmplwi  r0, 0x8
    bgt     L_80170594
L_8017057C:
    lwz     r0, 0x8(r29)
    slwi    r9, r9, 2
    addi    r11, r11, 0x1
    add     r9, r0, r9
    stb     r11, 0x0(r29)
    b       L_801705B4
L_80170594:
    cmpwi   r9, 0x7
    bgt     L_801705A8
    lwz     r9, 0x4(r29)
    stb     r21, 0x0(r29)
    b       L_801705AC
L_801705A8:
    lwz     r9, 0x4(r29)
L_801705AC:
    addi    r0, r9, 0x4
    stw     r0, 0x4(r29)
L_801705B4:
    lwz     r9, 0x0(r9)
    stw     r24, 0x0(r9)
    b       L_80170200
L_801705C0:
    li      r3, -0x1
    b       L_80170FA0
L_801705C8:
    lbzx    r0, r31, r15
    andi.   r9, r0, 0x1
    beq     L_801705D8
L_801705D4:
    ori     r30, r30, 0x1
L_801705D8:
    lis     r9, strtol@ha
    li      r31, 0x3
    addi    r18, r9, strtol@l
L_801705E4:
    li      r23, 0xa
L_801705E8:
    lwz     r0, 0x4(r28)
    cmpwi   r0, 0x0
    bgt     L_80170604
    mr      r3, r28
    bl      __srefill
    cmpwi   r3, 0x0
    bne     L_80170F88
L_80170604:
    andi.   r0, r30, 0x20
    bne     L_8017066C
    lwz     r11, 0x0(r28)
    lbz     r0, 0x0(r11)
    lbzx    r9, r15, r0
    andi.   r0, r9, 0x8
    beq     L_8017066C
    addi    r27, r16, lbl_8049C6A1@l
L_80170624:
    lwz     r9, 0x4(r28)
    addi    r24, r24, 0x1
    subi    r9, r9, 0x1
    cmpwi   r9, 0x0
    stw     r9, 0x4(r28)
    ble     L_80170648
    addi    r0, r11, 0x1
    stw     r0, 0x0(r28)
    b       L_80170658
L_80170648:
    mr      r3, r28
    bl      __srefill
    cmpwi   r3, 0x0
    bne     L_80170F88
L_80170658:
    lwz     r11, 0x0(r28)
    lbz     r0, 0x0(r11)
    lbzx    r9, r27, r0
    andi.   r0, r9, 0x8
    bne     L_80170624
L_8017066C:
    cmpwi   r31, 0x2
    beq     L_801708F0
    bgt     L_8017068C
    cmpwi   r31, 0x0
    beq     L_801706A0
    cmpwi   r31, 0x1
    beq     L_80170788
    b       L_80170200
L_8017068C:
    cmpwi   r31, 0x3
    beq     L_80170A2C
    cmpwi   r31, 0x4
    beq     L_80170D18
    b       L_80170200
L_801706A0:
    cmpwi   r26, 0x0
    bne     L_801706AC
    li      r26, 0x1
L_801706AC:
    andi.   r9, r30, 0x8
    beq     L_80170714
    li      r31, 0x0
L_801706B8:
    lwz     r30, 0x4(r28)
    cmplw   r30, r26
    bge     L_801706F4
    lwz     r0, 0x0(r28)
    mr      r3, r28
    add     r31, r31, r30
    subf    r26, r30, r26
    add     r0, r0, r30
    stw     r0, 0x0(r28)
    bl      __srefill
    cmpwi   r3, 0x0
    beq     L_801706B8
    cmpwi   r31, 0x0
    beq     L_80170F88
    b       L_8017070C
L_801706F4:
    lwz     r9, 0x0(r28)
    subf    r0, r26, r30
    stw     r0, 0x4(r28)
    add     r31, r31, r26
    add     r9, r9, r26
    stw     r9, 0x0(r28)
L_8017070C:
    add     r24, r24, r31
    b       L_80170200
L_80170714:
    lbz     r11, 0x0(r29)
    extsb   r9, r11
    addi    r0, r9, 0x1
    cmplwi  r0, 0x8
    bgt     L_80170740
    lwz     r0, 0x8(r29)
    slwi    r9, r9, 2
    addi    r11, r11, 0x1
    add     r3, r0, r9
    stb     r11, 0x0(r29)
    b       L_80170760
L_80170740:
    cmpwi   r9, 0x7
    bgt     L_80170754
    lwz     r3, 0x4(r29)
    stb     r21, 0x0(r29)
    b       L_80170758
L_80170754:
    lwz     r3, 0x4(r29)
L_80170758:
    addi    r0, r3, 0x4
    stw     r0, 0x4(r29)
L_80170760:
    lwz     r3, 0x0(r3)
    mr      r5, r26
    li      r4, 0x1
    mr      r6, r28
    bl      fread
    mr.     r3, r3
    beq     L_80170F88
    add     r24, r24, r3
    addi    r20, r20, 0x1
    b       L_80170200
L_80170788:
    cmpwi   r26, 0x0
    bne     L_80170794
    li      r26, -0x1
L_80170794:
    andi.   r0, r30, 0x8
    beq     L_80170804
    li      r30, 0x0
    addi    r31, r1, 0x8
L_801707A4:
    lwz     r11, 0x0(r28)
    lbz     r0, 0x0(r11)
    lbzx    r9, r31, r0
    cmpwi   r9, 0x0
    beq     L_801707F8
    lwz     r9, 0x4(r28)
    addi    r0, r11, 0x1
    stw     r0, 0x0(r28)
    addi    r30, r30, 0x1
    subi    r9, r9, 0x1
    subic.  r26, r26, 0x1
    stw     r9, 0x4(r28)
    beq     L_801707F8
    cmpwi   r9, 0x0
    bgt     L_801707A4
    mr      r3, r28
    bl      __srefill
    cmpwi   r3, 0x0
    beq     L_801707A4
    cmpwi   r30, 0x0
    beq     L_80170F88
L_801707F8:
    cmpwi   r30, 0x0
    beq     L_80170F9C
    b       L_80170958
L_80170804:
    lbz     r11, 0x0(r29)
    extsb   r9, r11
    addi    r0, r9, 0x1
    cmplwi  r0, 0x8
    bgt     L_80170830
    lwz     r0, 0x8(r29)
    slwi    r9, r9, 2
    addi    r11, r11, 0x1
    add     r9, r0, r9
    stb     r11, 0x0(r29)
    b       L_80170850
L_80170830:
    cmpwi   r9, 0x7
    bgt     L_80170844
    lwz     r9, 0x4(r29)
    stb     r21, 0x0(r29)
    b       L_80170848
L_80170844:
    lwz     r9, 0x4(r29)
L_80170848:
    addi    r0, r9, 0x4
    stw     r0, 0x4(r29)
L_80170850:
    lwz     r10, 0x0(r28)
    addi    r11, r1, 0x8
    lwz     r27, 0x0(r9)
    mr      r31, r11
    lbz     r9, 0x0(r10)
    mr      r30, r27
    lbzx    r0, r11, r9
    cmpwi   r0, 0x0
    b       L_801708AC
L_80170874:
    lwz     r0, 0x4(r28)
    cmpwi   r0, 0x0
    bgt     L_8017089C
    mr      r3, r28
    bl      __srefill
    cmpwi   r3, 0x0
    beq     L_8017089C
    cmpw    r27, r30
    beq     L_80170F88
    b       L_801708D8
L_8017089C:
    lwz     r10, 0x0(r28)
    lbz     r0, 0x0(r10)
    lbzx    r9, r31, r0
    cmpwi   r9, 0x0
L_801708AC:
    beq     L_801708D8
    lwz     r9, 0x4(r28)
    addi    r11, r10, 0x1
    subic.  r26, r26, 0x1
    subi    r9, r9, 0x1
    stw     r9, 0x4(r28)
    lbz     r0, 0x0(r10)
    stb     r0, 0x0(r27)
    stw     r11, 0x0(r28)
    addi    r27, r27, 0x1
    bne     L_80170874
L_801708D8:
    subf.   r30, r30, r27
    beq     L_80170F9C
    li      r0, 0x0
    addi    r20, r20, 0x1
    stb     r0, 0x0(r27)
    b       L_80170958
L_801708F0:
    cmpwi   r26, 0x0
    bne     L_801708FC
    li      r26, -0x1
L_801708FC:
    andi.   r0, r30, 0x8
    beq     L_80170960
    li      r30, 0x0
    addi    r27, r16, lbl_8049C6A1@l
L_8017090C:
    lwz     r11, 0x0(r28)
    lbz     r0, 0x0(r11)
    lbzx    r9, r27, r0
    andi.   r0, r9, 0x8
    bne     L_80170958
    lwz     r9, 0x4(r28)
    addi    r0, r11, 0x1
    stw     r0, 0x0(r28)
    addi    r30, r30, 0x1
    subi    r9, r9, 0x1
    subic.  r26, r26, 0x1
    stw     r9, 0x4(r28)
    beq     L_80170958
    cmpwi   r9, 0x0
    bgt     L_8017090C
    mr      r3, r28
    bl      __srefill
    cmpwi   r3, 0x0
    beq     L_8017090C
L_80170958:
    add     r24, r24, r30
    b       L_80170200
L_80170960:
    lbz     r11, 0x0(r29)
    extsb   r9, r11
    addi    r0, r9, 0x1
    cmplwi  r0, 0x8
    bgt     L_8017098C
    lwz     r0, 0x8(r29)
    slwi    r9, r9, 2
    addi    r11, r11, 0x1
    add     r9, r0, r9
    stb     r11, 0x0(r29)
    b       L_801709AC
L_8017098C:
    cmpwi   r9, 0x7
    bgt     L_801709A0
    lwz     r9, 0x4(r29)
    stb     r21, 0x0(r29)
    b       L_801709A4
L_801709A0:
    lwz     r9, 0x4(r29)
L_801709A4:
    addi    r0, r9, 0x4
    stw     r0, 0x4(r29)
L_801709AC:
    lwz     r27, 0x0(r9)
    addi    r25, r20, 0x1
    addi    r31, r16, lbl_8049C6A1@l
    mr      r30, r27
L_801709BC:
    lwz     r10, 0x0(r28)
    lbz     r0, 0x0(r10)
    lbzx    r9, r31, r0
    andi.   r0, r9, 0x8
    bne     L_80170A14
    lwz     r9, 0x4(r28)
    addi    r11, r10, 0x1
    subic.  r26, r26, 0x1
    subi    r9, r9, 0x1
    stw     r9, 0x4(r28)
    lbz     r0, 0x0(r10)
    stb     r0, 0x0(r27)
    stw     r11, 0x0(r28)
    addi    r27, r27, 0x1
    beq     L_80170A14
    lwz     r0, 0x4(r28)
    cmpwi   r0, 0x0
    bgt     L_801709BC
    mr      r3, r28
    bl      __srefill
    cmpwi   r3, 0x0
    beq     L_801709BC
L_80170A14:
    subf    r9, r30, r27
    li      r0, 0x0
    stb     r0, 0x0(r27)
    add     r24, r24, r9
    mr      r20, r25
    b       L_80170200
L_80170A2C:
    subi    r26, r26, 0x1
    cmplwi  r26, 0x15c
    ble     L_80170A3C
    li      r26, 0x15c
L_80170A3C:
    addi    r27, r1, 0x108
    ori     r30, r30, 0x2c0
    mr      r19, r27
    addic.  r26, r26, 0x1
    beq     L_80170B90
    lis     r9, lbl_8049C1E8@ha
    addi    r25, r9, lbl_8049C1E8@l
L_80170A58:
    lwz     r9, 0x0(r28)
    lbz     r31, 0x0(r9)
    cmpwi   r31, 0x39
    bgt     L_80170A90
    cmpwi   r31, 0x38
    bge     L_80170B00
    cmpwi   r31, 0x30
    beq     L_80170ACC
    bgt     L_80170AF0
    cmpwi   r31, 0x2b
    beq     L_80170B20
    cmpwi   r31, 0x2d
    beq     L_80170B20
    b       L_80170B90
L_80170A90:
    cmpwi   r31, 0x58
    beq     L_80170B30
    bgt     L_80170AB0
    cmpwi   r31, 0x46
    bgt     L_80170B90
    cmpwi   r31, 0x41
    blt     L_80170B90
    b       L_80170B10
L_80170AB0:
    cmpwi   r31, 0x61
    blt     L_80170B90
    cmpwi   r31, 0x66
    ble     L_80170B10
    cmpwi   r31, 0x78
    beq     L_80170B30
    b       L_80170B90
L_80170ACC:
    cmpwi   r23, 0x0
    bne     L_80170ADC
    li      r23, 0x8
    ori     r30, r30, 0x100
L_80170ADC:
    andi.   r0, r30, 0x200
    beq     L_80170B18
    li      r0, -0x2c1
    and     r30, r30, r0
    b       L_80170B4C
L_80170AF0:
    add     r0, r23, r23
    rlwinm  r30, r30, 0, 26, 22
    lhax    r23, r25, r0
    b       L_80170B4C
L_80170B00:
    add     r0, r23, r23
    lhax    r23, r25, r0
    cmpwi   r23, 0x8
    b       L_80170B14
L_80170B10:
    cmpwi   r23, 0xa
L_80170B14:
    ble     L_80170B90
L_80170B18:
    rlwinm  r30, r30, 0, 26, 22
    b       L_80170B4C
L_80170B20:
    andi.   r9, r30, 0x40
    beq     L_80170B90
    rlwinm  r30, r30, 0, 26, 24
    b       L_80170B4C
L_80170B30:
    andi.   r0, r30, 0x100
    beq     L_80170B90
    addi    r0, r1, 0x109
    cmpw    r27, r0
    bne     L_80170B90
    li      r23, 0x10
    rlwinm  r30, r30, 0, 24, 22
L_80170B4C:
    stb     r31, 0x0(r27)
    addi    r27, r27, 0x1
    lwz     r9, 0x4(r28)
    subi    r9, r9, 0x1
    cmpwi   r9, 0x0
    stw     r9, 0x4(r28)
    ble     L_80170B78
    lwz     r9, 0x0(r28)
    addi    r9, r9, 0x1
    stw     r9, 0x0(r28)
    b       L_80170B88
L_80170B78:
    mr      r3, r28
    bl      __srefill
    cmpwi   r3, 0x0
    bne     L_80170B90
L_80170B88:
    subic.  r26, r26, 0x1
    bne     L_80170A58
L_80170B90:
    andi.   r0, r30, 0x80
    beq     L_80170BB4
    cmplw   r27, r19
    ble     L_80170F9C
    lbz     r3, -0x1(r27)
    mr      r4, r28
    extsb   r3, r3
    bl      ungetc
    b       L_80170F9C
L_80170BB4:
    lbz     r0, -0x1(r27)
    extsb   r31, r0
    cmpwi   r31, 0x78
    beq     L_80170BCC
    cmpwi   r31, 0x58
    bne     L_80170BDC
L_80170BCC:
    mr      r3, r31
    subi    r27, r27, 0x1
    mr      r4, r28
    bl      ungetc
L_80170BDC:
    andi.   r0, r30, 0x8
    bne     L_80170F7C
    mr      r3, r19
    li      r4, 0x0
    mr      r5, r23
    mtlr    r18
    stb     r0, 0x0(r27)
    crclr   4*cr1+eq
    blrl
    andi.   r0, r30, 0x10
    beq     L_80170C30
    lbz     r11, 0x0(r29)
    extsb   r9, r11
    addi    r0, r9, 0x1
    cmplwi  r0, 0x8
    ble     L_80170CD4
    cmpwi   r9, 0x7
    bgt     L_80170D00
    lwz     r9, 0x4(r29)
    stb     r21, 0x0(r29)
    b       L_80170D04
L_80170C30:
    andi.   r9, r30, 0x4
    beq     L_80170C90
    lbz     r11, 0x0(r29)
    extsb   r9, r11
    addi    r0, r9, 0x1
    cmplwi  r0, 0x8
    bgt     L_80170C64
    lwz     r0, 0x8(r29)
    slwi    r9, r9, 2
    addi    r11, r11, 0x1
    add     r9, r0, r9
    stb     r11, 0x0(r29)
    b       L_80170C84
L_80170C64:
    cmpwi   r9, 0x7
    bgt     L_80170C78
    lwz     r9, 0x4(r29)
    stb     r21, 0x0(r29)
    b       L_80170C7C
L_80170C78:
    lwz     r9, 0x4(r29)
L_80170C7C:
    addi    r0, r9, 0x4
    stw     r0, 0x4(r29)
L_80170C84:
    lwz     r9, 0x0(r9)
    sth     r3, 0x0(r9)
    b       L_80170F78
L_80170C90:
    andi.   r0, r30, 0x1
    beq     L_80170CC0
    lbz     r11, 0x0(r29)
    extsb   r9, r11
    addi    r0, r9, 0x1
    cmplwi  r0, 0x8
    ble     L_80170CD4
    cmpwi   r9, 0x7
    bgt     L_80170D00
    lwz     r9, 0x4(r29)
    stb     r21, 0x0(r29)
    b       L_80170D04
L_80170CC0:
    lbz     r11, 0x0(r29)
    extsb   r9, r11
    addi    r0, r9, 0x1
    cmplwi  r0, 0x8
    bgt     L_80170CEC
L_80170CD4:
    lwz     r0, 0x8(r29)
    slwi    r9, r9, 2
    addi    r11, r11, 0x1
    add     r9, r0, r9
    stb     r11, 0x0(r29)
    b       L_80170D0C
L_80170CEC:
    cmpwi   r9, 0x7
    bgt     L_80170D00
    lwz     r9, 0x4(r29)
    stb     r21, 0x0(r29)
    b       L_80170D04
L_80170D00:
    lwz     r9, 0x4(r29)
L_80170D04:
    addi    r0, r9, 0x4
    stw     r0, 0x4(r29)
L_80170D0C:
    lwz     r9, 0x0(r9)
    stw     r3, 0x0(r9)
    b       L_80170F78
L_80170D18:
    subi    r26, r26, 0x1
    cmplwi  r26, 0x15c
    ble     L_80170D28
    li      r26, 0x15c
L_80170D28:
    addi    r27, r1, 0x108
    ori     r30, r30, 0x3c0
    mr      r19, r27
    addic.  r26, r26, 0x1
    beq     L_80170E10
    li      r25, -0x141
L_80170D40:
    lwz     r9, 0x0(r28)
    lbz     r31, 0x0(r9)
    cmpwi   r31, 0x39
    bgt     L_80170D7C
    cmpwi   r31, 0x30
    bge     L_80170D90
    cmpwi   r31, 0x2d
    beq     L_80170D98
    bgt     L_80170D70
    cmpwi   r31, 0x2b
    beq     L_80170D98
    b       L_80170E10
L_80170D70:
    cmpwi   r31, 0x2e
    beq     L_80170DA8
    b       L_80170E10
L_80170D7C:
    cmpwi   r31, 0x45
    beq     L_80170DB8
    cmpwi   r31, 0x65
    beq     L_80170DB8
    b       L_80170E10
L_80170D90:
    rlwinm  r30, r30, 0, 26, 23
    b       L_80170DCC
L_80170D98:
    andi.   r9, r30, 0x40
    beq     L_80170E10
    rlwinm  r30, r30, 0, 26, 24
    b       L_80170DCC
L_80170DA8:
    andi.   r0, r30, 0x100
    beq     L_80170E10
    and     r30, r30, r25
    b       L_80170DCC
L_80170DB8:
    andi.   r0, r30, 0x280
    cmpwi   r0, 0x200
    bne     L_80170E10
    rlwinm  r0, r30, 0, 24, 21
    ori     r30, r0, 0xc0
L_80170DCC:
    stb     r31, 0x0(r27)
    addi    r27, r27, 0x1
    lwz     r9, 0x4(r28)
    subi    r9, r9, 0x1
    cmpwi   r9, 0x0
    stw     r9, 0x4(r28)
    ble     L_80170DF8
    lwz     r9, 0x0(r28)
    addi    r9, r9, 0x1
    stw     r9, 0x0(r28)
    b       L_80170E08
L_80170DF8:
    mr      r3, r28
    bl      __srefill
    cmpwi   r3, 0x0
    bne     L_80170E10
L_80170E08:
    subic.  r26, r26, 0x1
    bne     L_80170D40
L_80170E10:
    andi.   r0, r30, 0x80
    beq     L_80170E7C
    andi.   r9, r30, 0x200
    beq     L_80170E44
    cmplw   r27, r19
    ble     L_80170F9C
L_80170E28:
    lbzu    r3, -0x1(r27)
    mr      r4, r28
    extsb   r3, r3
    bl      ungetc
    cmplw   r27, r19
    bgt     L_80170E28
    b       L_80170F9C
L_80170E44:
    lbzu    r0, -0x1(r27)
    extsb   r31, r0
    cmpwi   r31, 0x65
    beq     L_80170E70
    cmpwi   r31, 0x45
    beq     L_80170E70
    mr      r3, r31
    mr      r4, r28
    bl      ungetc
    lbzu    r0, -0x1(r27)
    extsb   r31, r0
L_80170E70:
    mr      r3, r31
    mr      r4, r28
    bl      ungetc
L_80170E7C:
    andi.   r0, r30, 0x8
    bne     L_80170F7C
    stb     r0, 0x0(r27)
    mr      r3, r19
    bl      atof
    andi.   r0, r30, 0x1
    beq     L_80170EC0
    lbz     r11, 0x0(r29)
    extsb   r9, r11
    addi    r0, r9, 0x1
    cmplwi  r0, 0x8
    ble     L_80170EDC
    cmpwi   r9, 0x7
    bgt     L_80170F08
    lwz     r9, 0x4(r29)
    stb     r21, 0x0(r29)
    b       L_80170F0C
L_80170EC0:
    andi.   r9, r30, 0x2
    beq     L_80170F20
    lbz     r11, 0x0(r29)
    extsb   r9, r11
    addi    r0, r9, 0x1
    cmplwi  r0, 0x8
    bgt     L_80170EF4
L_80170EDC:
    lwz     r0, 0x8(r29)
    slwi    r9, r9, 2
    addi    r11, r11, 0x1
    add     r9, r0, r9
    stb     r11, 0x0(r29)
    b       L_80170F14
L_80170EF4:
    cmpwi   r9, 0x7
    bgt     L_80170F08
    lwz     r9, 0x4(r29)
    stb     r21, 0x0(r29)
    b       L_80170F0C
L_80170F08:
    lwz     r9, 0x4(r29)
L_80170F0C:
    addi    r0, r9, 0x4
    stw     r0, 0x4(r29)
L_80170F14:
    lwz     r9, 0x0(r9)
    stfd    f1, 0x0(r9)
    b       L_80170F78
L_80170F20:
    lbz     r11, 0x0(r29)
    extsb   r9, r11
    addi    r0, r9, 0x1
    cmplwi  r0, 0x8
    bgt     L_80170F4C
    lwz     r0, 0x8(r29)
    slwi    r9, r9, 2
    addi    r11, r11, 0x1
    add     r9, r0, r9
    stb     r11, 0x0(r29)
    b       L_80170F6C
L_80170F4C:
    cmpwi   r9, 0x7
    bgt     L_80170F60
    lwz     r9, 0x4(r29)
    stb     r21, 0x0(r29)
    b       L_80170F64
L_80170F60:
    lwz     r9, 0x4(r29)
L_80170F64:
    addi    r0, r9, 0x4
    stw     r0, 0x4(r29)
L_80170F6C:
    lwz     r9, 0x0(r9)
    frsp    f0, f1
    stfs    f0, 0x0(r9)
L_80170F78:
    addi    r20, r20, 0x1
L_80170F7C:
    subf    r0, r19, r27
    add     r24, r24, r0
    b       L_80170200
L_80170F88:
    mr      r3, r20
    cmpwi   r3, 0x0
    bne     L_80170FA0
    li      r3, -0x1
    b       L_80170FA0
L_80170F9C:
    mr      r3, r20
L_80170FA0:
    lwz     r0, 0x2c4(r1)
    mtlr    r0
    lmw     r14, 0x278(r1)
    addi    r1, r1, 0x2c0
    blr
    // clang-format on
}
