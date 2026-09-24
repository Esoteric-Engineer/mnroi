extern char lbl_8049C4E0[];
extern char lbl_8049C510[];
extern void div(void);

asm long validate_structure(void* tim_p)
{
    // clang-format off
    nofralloc
    stwu    r1, -0x30(r1)
    mflr    r0
    stmw    r30, 0x28(r1)
    stw     r0, 0x34(r1)
    mr      r31, r3
    li      r30, 0x1c
    lwz     r4, 0x0(r31)
    cmplwi  r4, 0x3b
    ble     L_8017305C
    addi    r3, r1, 0x8
    li      r5, 0x3c
    crclr   4*cr1+eq
    bl      div
    lwz     r9, 0x8(r1)
    lwz     r10, 0xc(r1)
    lwz     r0, 0x4(r31)
    mr.     r11, r10
    stw     r10, 0x0(r31)
    add     r9, r0, r9
    stw     r9, 0x4(r31)
    bge     L_8017305C
    addi    r0, r11, 0x3c
    subi    r9, r9, 0x1
    stw     r0, 0x0(r31)
    stw     r9, 0x4(r31)
L_8017305C:
    lwz     r4, 0x4(r31)
    cmplwi  r4, 0x3b
    ble     L_801730A8
    addi    r3, r1, 0x10
    li      r5, 0x3c
    crclr   4*cr1+eq
    bl      div
    lwz     r9, 0x10(r1)
    lwz     r10, 0x14(r1)
    lwz     r0, 0x8(r31)
    mr.     r11, r10
    stw     r10, 0x4(r31)
    add     r9, r0, r9
    stw     r9, 0x8(r31)
    bge     L_801730A8
    addi    r0, r11, 0x3c
    subi    r9, r9, 0x1
    stw     r0, 0x4(r31)
    stw     r9, 0x8(r31)
L_801730A8:
    lwz     r4, 0x8(r31)
    cmplwi  r4, 0x17
    ble     L_801730F4
    addi    r3, r1, 0x18
    li      r5, 0x18
    crclr   4*cr1+eq
    bl      div
    lwz     r9, 0x18(r1)
    lwz     r10, 0x1c(r1)
    lwz     r0, 0xc(r31)
    mr.     r11, r10
    stw     r10, 0x8(r31)
    add     r9, r0, r9
    stw     r9, 0xc(r31)
    bge     L_801730F4
    addi    r0, r11, 0x18
    subi    r9, r9, 0x1
    stw     r0, 0x8(r31)
    stw     r9, 0xc(r31)
L_801730F4:
    lwz     r4, 0x10(r31)
    cmpwi   r4, 0xb
    ble     L_80173140
    addi    r3, r1, 0x20
    li      r5, 0xc
    crclr   4*cr1+eq
    bl      div
    lwz     r9, 0x20(r1)
    lwz     r10, 0x24(r1)
    lwz     r0, 0x14(r31)
    mr.     r11, r10
    stw     r10, 0x10(r31)
    add     r9, r0, r9
    stw     r9, 0x14(r31)
    bge     L_80173140
    addi    r0, r11, 0xc
    subi    r9, r9, 0x1
    stw     r0, 0x10(r31)
    stw     r9, 0x14(r31)
L_80173140:
    lwz     r11, 0x14(r31)
    andi.   r0, r11, 0x3
    bne     L_80173194
    lis     r10, 0x51eb
    srawi   r9, r11, 31
    ori     r10, r10, 0x851f
    mulhw   r0, r11, r10
    srawi   r0, r0, 5
    subf    r0, r9, r0
    mulli   r0, r0, 0x64
    cmpw    r11, r0
    bne     L_80173190
    addi    r0, r11, 0x76c
    mulhw   r9, r0, r10
    srawi   r11, r0, 31
    srawi   r9, r9, 7
    subf    r9, r11, r9
    mulli   r9, r9, 0x190
    cmpw    r0, r9
    bne     L_80173194
L_80173190:
    li      r30, 0x1d
L_80173194:
    lwz     r0, 0xc(r31)
    cmpwi   r0, 0x0
    bgt     L_8017325C
    lis     r9, lbl_8049C4E0@ha
    li      r6, 0xb
    addi    r7, r9, lbl_8049C4E0@l
L_801731AC:
    lwz     r9, 0x10(r31)
    subi    r9, r9, 0x1
    cmpwi   r9, -0x1
    stw     r9, 0x10(r31)
    bne     L_80173228
    lwz     r8, 0x14(r31)
    stw     r6, 0x10(r31)
    subi    r11, r8, 0x1
    stw     r11, 0x14(r31)
    andi.   r0, r11, 0x3
    bne     L_80173224
    lis     r10, 0x51eb
    srawi   r9, r11, 31
    ori     r10, r10, 0x851f
    mulhw   r0, r11, r10
    srawi   r0, r0, 5
    subf    r0, r9, r0
    mulli   r0, r0, 0x64
    cmpw    r11, r0
    bne     L_8017321C
    addi    r0, r8, 0x76b
    mulhw   r9, r0, r10
    srawi   r11, r0, 31
    srawi   r9, r9, 7
    subf    r9, r11, r9
    mulli   r9, r9, 0x190
    cmpw    r0, r9
    bne     L_80173224
L_8017321C:
    li      r30, 0x1d
    b       L_80173228
L_80173224:
    li      r30, 0x1c
L_80173228:
    lwz     r0, 0x10(r31)
    lwz     r11, 0xc(r31)
    cmpwi   r0, 0x1
    beq     L_80173248
    slwi    r0, r0, 2
    lwzx    r9, r7, r0
    add     r0, r11, r9
    b       L_8017324C
L_80173248:
    add     r0, r11, r30
L_8017324C:
    cmpwi   r0, 0x0
    stw     r0, 0xc(r31)
    ble     L_801731AC
    b       L_80173338
L_8017325C:
    lis     r9, lbl_8049C4E0@ha
    li      r6, 0x0
    addi    r7, r9, lbl_8049C4E0@l
    b       L_80173310
L_8017326C:
    lwz     r0, 0x10(r31)
    lwz     r11, 0xc(r31)
    cmpwi   r0, 0x1
    beq     L_8017328C
    slwi    r0, r0, 2
    lwzx    r9, r7, r0
    subf    r0, r9, r11
    b       L_80173290
L_8017328C:
    subf    r0, r30, r11
L_80173290:
    lwz     r9, 0x10(r31)
    stw     r0, 0xc(r31)
    addi    r9, r9, 0x1
    cmpwi   r9, 0xc
    stw     r9, 0x10(r31)
    bne     L_80173310
    lwz     r8, 0x14(r31)
    stw     r6, 0x10(r31)
    addi    r11, r8, 0x1
    stw     r11, 0x14(r31)
    andi.   r0, r11, 0x3
    bne     L_8017330C
    lis     r10, 0x51eb
    srawi   r9, r11, 31
    ori     r10, r10, 0x851f
    mulhw   r0, r11, r10
    srawi   r0, r0, 5
    subf    r0, r9, r0
    mulli   r0, r0, 0x64
    cmpw    r11, r0
    bne     L_80173304
    addi    r0, r8, 0x76d
    mulhw   r9, r0, r10
    srawi   r11, r0, 31
    srawi   r9, r9, 7
    subf    r9, r11, r9
    mulli   r9, r9, 0x190
    cmpw    r0, r9
    bne     L_8017330C
L_80173304:
    li      r30, 0x1d
    b       L_80173310
L_8017330C:
    li      r30, 0x1c
L_80173310:
    lwz     r0, 0x10(r31)
    lwz     r11, 0xc(r31)
    cmpwi   r0, 0x1
    beq     L_80173330
    slwi    r0, r0, 2
    lwzx    r9, r7, r0
    cmpw    r11, r9
    b       L_80173334
L_80173330:
    cmpw    r11, r30
L_80173334:
    bgt     L_8017326C
L_80173338:
    lwz     r0, 0x34(r1)
    mtlr    r0
    lmw     r30, 0x28(r1)
    addi    r1, r1, 0x30
    blr
    // clang-format on
}

asm long mktime(void* tim_p)
{
    // clang-format off
    nofralloc
    stwu    r1, -0x10(r1)
    mflr    r0
    stw     r31, 0xc(r1)
    stw     r0, 0x14(r1)
    mr      r31, r3
    crclr   4*cr1+eq
    bl      validate_structure
    lwz     r10, 0x4(r31)
    lis     r11, lbl_8049C510@ha
    lwz     r8, 0x8(r31)
    addi    r11, r11, lbl_8049C510@l
    lwz     r5, 0x10(r31)
    mulli   r10, r10, 0x3c
    lwz     r9, 0x0(r31)
    mulli   r8, r8, 0xe10
    slwi    r0, r5, 2
    lwz     r7, 0xc(r31)
    cmpwi   r5, 0x1
    lwzx    r6, r11, r0
    add     r9, r9, r10
    subi    r7, r7, 0x1
    add     r5, r9, r8
    add     r7, r7, r6
    ble     L_80173400
    lwz     r11, 0x14(r31)
    andi.   r0, r11, 0x3
    bne     L_80173400
    lis     r10, 0x51eb
    srawi   r9, r11, 31
    ori     r10, r10, 0x851f
    mulhw   r0, r11, r10
    srawi   r0, r0, 5
    subf    r0, r9, r0
    mulli   r0, r0, 0x64
    cmpw    r11, r0
    bne     L_801733FC
    addi    r0, r11, 0x76c
    mulhw   r9, r0, r10
    srawi   r11, r0, 31
    srawi   r9, r9, 7
    subf    r9, r11, r9
    mulli   r9, r9, 0x190
    cmpw    r0, r9
    bne     L_80173400
L_801733FC:
    addi    r7, r7, 0x1
L_80173400:
    lwz     r9, 0x14(r31)
    stw     r7, 0x1c(r31)
    addi    r0, r9, 0x2710
    cmplwi  r0, 0x4e20
    ble     L_8017341C
    li      r3, -0x1
    b       L_801735C0
L_8017341C:
    cmpwi   r9, 0x46
    ble     L_8017349C
    li      r10, 0x46
    cmpw    r10, r9
    bge     L_80173570
    mr      r8, r9
L_80173434:
    andi.   r0, r10, 0x3
    bne     L_80173488
    lis     r11, 0x51eb
    srawi   r9, r10, 31
    ori     r11, r11, 0x851f
    mulhw   r0, r10, r11
    srawi   r0, r0, 5
    subf    r0, r9, r0
    mulli   r0, r0, 0x64
    cmpw    r10, r0
    bne     L_80173480
    addi    r0, r10, 0x76c
    mulhw   r9, r0, r11
    srawi   r11, r0, 31
    srawi   r9, r9, 7
    subf    r9, r11, r9
    mulli   r9, r9, 0x190
    cmpw    r0, r9
    bne     L_80173488
L_80173480:
    addi    r7, r7, 0x16e
    b       L_8017348C
L_80173488:
    addi    r7, r7, 0x16d
L_8017348C:
    addi    r10, r10, 0x1
    cmpw    r10, r8
    blt     L_80173434
    b       L_80173570
L_8017349C:
    cmpwi   r9, 0x45
    bgt     L_80173570
    li      r10, 0x45
    cmpw    r10, r9
    ble     L_80173518
    mr      r8, r9
L_801734B4:
    andi.   r0, r10, 0x3
    bne     L_80173508
    lis     r11, 0x51eb
    srawi   r9, r10, 31
    ori     r11, r11, 0x851f
    mulhw   r0, r10, r11
    srawi   r0, r0, 5
    subf    r0, r9, r0
    mulli   r0, r0, 0x64
    cmpw    r10, r0
    bne     L_80173500
    addi    r0, r10, 0x76c
    mulhw   r9, r0, r11
    srawi   r11, r0, 31
    srawi   r9, r9, 7
    subf    r9, r11, r9
    mulli   r9, r9, 0x190
    cmpw    r0, r9
    bne     L_80173508
L_80173500:
    subi    r7, r7, 0x16e
    b       L_8017350C
L_80173508:
    subi    r7, r7, 0x16d
L_8017350C:
    subi    r10, r10, 0x1
    cmpw    r10, r8
    bgt     L_801734B4
L_80173518:
    andi.   r0, r10, 0x3
    bne     L_8017356C
    lis     r11, 0x51eb
    srawi   r9, r10, 31
    ori     r11, r11, 0x851f
    mulhw   r0, r10, r11
    srawi   r0, r0, 5
    subf    r0, r9, r0
    mulli   r0, r0, 0x64
    cmpw    r10, r0
    bne     L_80173564
    addi    r0, r10, 0x76c
    mulhw   r9, r0, r11
    srawi   r11, r0, 31
    srawi   r9, r9, 7
    subf    r9, r11, r9
    mulli   r9, r9, 0x190
    cmpw    r0, r9
    bne     L_8017356C
L_80173564:
    subi    r7, r7, 0x16e
    b       L_80173570
L_8017356C:
    subi    r7, r7, 0x16d
L_80173570:
    lis     r0, 0x9249
    addi    r11, r7, 0x4
    ori     r0, r0, 0x2493
    srawi   r10, r11, 31
    mulhw   r0, r11, r0
    add     r0, r0, r11
    srawi   r0, r0, 2
    subf    r0, r10, r0
    slwi    r9, r0, 3
    subf    r9, r0, r9
    subf    r11, r9, r11
    stw     r11, 0x18(r31)
    cmpwi   r11, 0x0
    bge     L_801735B0
    addi    r0, r11, 0x7
    stw     r0, 0x18(r31)
L_801735B0:
    lis     r3, 0x1
    ori     r3, r3, 0x5180
    mullw   r3, r7, r3
    add     r3, r5, r3
L_801735C0:
    lwz     r0, 0x14(r1)
    mtlr    r0
    lwz     r31, 0xc(r1)
    addi    r1, r1, 0x10
    blr
    // clang-format on
}
