void fn_8016A408(void);

asm void fn_8016A440(void)
{
    // clang-format off
    nofralloc
    mflr    r30
    lbz     r3, 0x4e4(r31)
    cmpwi   r3, 0x0
    beq     L_8016A7CC
    xori    r3, r3, 0xff
    lwz     r4, 0x370(r31)
    lwz     r4, 0x0(r4)
    srwi    r5, r4, 26
    extrwi  r6, r4, 10, 21
    lwz     r11, 0x438(r31)
    lwz     r8, 0x450(r31)
    clrrwi  r8, r8, 3
    subf    r7, r8, r11
    extrwi. r9, r4, 5, 11
    bne     L_8016A484
    li      r9, 0x0
    b       L_8016A48C
L_8016A484:
    slwi    r9, r9, 3
    lwzx    r9, r9, r31
L_8016A48C:
    extrwi  r10, r4, 5, 16
    slwi    r10, r10, 3
    lwzx    r10, r10, r31
    cmpwi   r5, 0x4
    beq     L_8016A5C0
    cmpwi   r5, 0x1f
    beq     L_8016A608
    extsh   r8, r4
    add     r8, r8, r9
    cmpwi   r5, 0x22
    beq     L_8016A790
    cmpwi   r5, 0x23
    beq     L_8016A790
    cmpwi   r5, 0x26
    beq     L_8016A790
    cmpwi   r5, 0x27
    beq     L_8016A790
    cmpwi   r5, 0x2a
    beq     L_8016A798
    cmpwi   r5, 0x2b
    beq     L_8016A798
    cmpwi   r5, 0x28
    beq     L_8016A798
    cmpwi   r5, 0x29
    beq     L_8016A798
    cmpwi   r5, 0x2c
    beq     L_8016A798
    cmpwi   r5, 0x2d
    beq     L_8016A798
    cmpwi   r5, 0x20
    beq     L_8016A7A0
    cmpwi   r5, 0x21
    beq     L_8016A7A0
    cmpwi   r5, 0x24
    beq     L_8016A7A0
    cmpwi   r5, 0x25
    beq     L_8016A7A0
    cmpwi   r5, 0x30
    beq     L_8016A7A0
    cmpwi   r5, 0x31
    beq     L_8016A7A0
    cmpwi   r5, 0x34
    beq     L_8016A7A0
    cmpwi   r5, 0x35
    beq     L_8016A7A0
    cmpwi   r5, 0x32
    beq     L_8016A7A8
    cmpwi   r5, 0x33
    beq     L_8016A7A8
    cmpwi   r5, 0x36
    beq     L_8016A7A8
    cmpwi   r5, 0x37
    beq     L_8016A7A8
    cmpwi   r5, 0x2e
    beq     L_8016A764
    cmpwi   r5, 0x2f
    beq     L_8016A764
    slwi    r8, r4, 20
    srawi   r8, r8, 20
    add     r8, r8, r9
    extrwi  r9, r4, 3, 17
    slwi    r9, r9, 3
    addi    r9, r9, 0x208
    lwzx    r9, r9, r31
    extrwi  r10, r9, 3, 13
    bl      fn_8016A408
    cmpwi   r5, 0x38
    beq     L_8016A7AC
    cmpwi   r5, 0x39
    beq     L_8016A7AC
    clrlwi  r11, r9, 29
    bl      fn_8016A408
    cmpwi   r5, 0x3c
    beq     L_8016A7AC
    cmpwi   r5, 0x3d
    beq     L_8016A7AC
    b       L_8016A7CC
L_8016A5C0:
    add     r8, r9, r10
    extrwi  r9, r4, 3, 17
    slwi    r9, r9, 3
    addi    r9, r9, 0x208
    lwzx    r9, r9, r31
    extrwi  r10, r9, 3, 13
    bl      fn_8016A408
    cmpwi   r6, 0x6
    beq     L_8016A7AC
    cmpwi   r6, 0x26
    beq     L_8016A7AC
    clrlwi  r11, r9, 29
    bl      fn_8016A408
    cmpwi   r6, 0x7
    beq     L_8016A7AC
    cmpwi   r6, 0x27
    beq     L_8016A7AC
    b       L_8016A7CC
L_8016A608:
    add     r8, r9, r10
    cmpwi   r6, 0x77
    beq     L_8016A790
    cmpwi   r6, 0x57
    beq     L_8016A790
    cmpwi   r6, 0xf7
    beq     L_8016A790
    cmpwi   r6, 0xd7
    beq     L_8016A790
    cmpwi   r6, 0x177
    beq     L_8016A798
    cmpwi   r6, 0x157
    beq     L_8016A798
    cmpwi   r6, 0x137
    beq     L_8016A798
    cmpwi   r6, 0x117
    beq     L_8016A798
    cmpwi   r6, 0x1b7
    beq     L_8016A798
    cmpwi   r6, 0x197
    beq     L_8016A798
    cmpwi   r6, 0x316
    beq     L_8016A798
    cmpwi   r6, 0x396
    beq     L_8016A798
    cmpwi   r6, 0x37
    beq     L_8016A7A0
    cmpwi   r6, 0x17
    beq     L_8016A7A0
    cmpwi   r6, 0xb7
    beq     L_8016A7A0
    cmpwi   r6, 0x97
    beq     L_8016A7A0
    cmpwi   r6, 0x216
    beq     L_8016A7A0
    cmpwi   r6, 0x296
    beq     L_8016A7A0
    cmpwi   r6, 0x237
    beq     L_8016A7A0
    cmpwi   r6, 0x217
    beq     L_8016A7A0
    cmpwi   r6, 0x2b7
    beq     L_8016A7A0
    cmpwi   r6, 0x297
    beq     L_8016A7A0
    cmpwi   r6, 0x3d7
    beq     L_8016A7A0
    cmpwi   r6, 0x14
    beq     L_8016A7A0
    cmpwi   r6, 0x96
    beq     L_8016A7A0
    cmpwi   r6, 0x277
    beq     L_8016A7A8
    cmpwi   r6, 0x257
    beq     L_8016A7A8
    cmpwi   r6, 0x2f7
    beq     L_8016A7A8
    cmpwi   r6, 0x2d7
    beq     L_8016A7A8
    cmpwi   r6, 0x215
    beq     L_8016A72C
    cmpwi   r6, 0x295
    beq     L_8016A72C
    mr      r8, r9
    cmpwi   r6, 0x255
    beq     L_8016A71C
    cmpwi   r6, 0x2d5
    beq     L_8016A71C
    b       L_8016A7CC
L_8016A71C:
    extrwi. r4, r4, 5, 16
    bne     L_8016A734
    li      r4, 0x20
    b       L_8016A734
L_8016A72C:
    lwz     r4, 0x348(r31)
    clrlwi  r5, r4, 25
L_8016A734:
    subf.   r5, r8, r11
    beq     L_8016A744
    subf    r4, r5, r4
    mr      r8, r11
L_8016A744:
    li      r12, 0xff
    cmpwi   r4, 0x8
    bge     L_8016A7AC
    li      r5, 0x8
    subf    r4, r4, r5
    slw     r12, r12, r4
    andi.   r12, r12, 0xff
    b       L_8016A7AC
L_8016A764:
    subf.   r5, r8, r11
    beq     L_8016A7A8
    mr      r8, r11
    extrwi  r6, r4, 5, 6
    li      r4, 0x20
    subf    r4, r6, r4
    slwi    r4, r4, 2
    subf    r4, r5, r4
    cmpwi   r4, 0x4
    beq     L_8016A7A0
    b       L_8016A7A8
L_8016A790:
    li      r12, 0x80
    b       L_8016A7AC
L_8016A798:
    li      r12, 0xc0
    b       L_8016A7AC
L_8016A7A0:
    li      r12, 0xf0
    b       L_8016A7AC
L_8016A7A8:
    li      r12, 0xff
L_8016A7AC:
    subf    r8, r8, r11
    slw     r4, r12, r8
    srw     r4, r4, r7
    and.    r3, r3, r4
    bne     L_8016A7CC
    li      r3, 0x1
    mtlr    r30
    blr
L_8016A7CC:
    li      r3, 0x0
    mtlr    r30
    blr
    opword  0
    opword  0
    // clang-format on
}
