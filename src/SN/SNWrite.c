void DCFlushRange(void);
void fn_8016B104(void);
void fn_8016B11C(void);
void fn_8016B130(void);
int SNRead8(void);
void SNWrite8(void);
void SNWrite32(void);
void SNSync(void);

asm int SNWrite(void)
{
    // clang-format off
    nofralloc
    mflr    r0
    stw     r0, 4(r1)
    stwu    r1, -0x18(r1)
    stw     r31, 8(r1)
    stw     r30, 0xc(r1)
    stw     r29, 0x10(r1)
    stw     r28, 0x14(r1)
    mr      r31, r4
    mr      r30, r3
    bl      DCFlushRange
    bl      fn_8016B104
L_8016AF3C:
    bl      SNRead8
    cmpwi   r3, 0
    beq     L_8016AF3C
L_8016AF48:
    bl      fn_8016B130
    bl      SNRead8
    cmpwi   r3, 0xff
    beq     L_8016AF48
    bl      fn_8016B130
    li      r3, 3
    bl      SNWrite8
    srwi    r3, r31, 8
    bl      SNWrite8
    mr      r3, r31
    bl      SNWrite8
    srwi    r28, r31, 9
    cmpwi   r28, 0
    bne     L_8016AF8C
    andi.   r28, r31, 0x1ff
    beq     L_8016B074
    b       L_8016AFE4
L_8016AF8C:
    bl      fn_8016B130
L_8016AF90:
    bl      SNRead8
    cmpwi   r3, 0
    beq     L_8016AF90
L_8016AF9C:
    bl      fn_8016B130
    bl      SNRead8
    cmpwi   r3, 0xff
    beq     L_8016AF9C
    bl      fn_8016B130
    lis     r29, 0xcc00
    stw     r30, 0x682c(r29)
    li      r5, 0x200
    stw     r5, 0x6830(r29)
    li      r3, 7
    stw     r3, 0x6834(r29)
    bl      SNSync
    add     r30, r30, r5
    subi    r28, r28, 1
    cmpwi   r28, 0
    bne     L_8016AF8C
    andi.   r28, r31, 0x1ff
    beq     L_8016B074
L_8016AFE4:
    bl      fn_8016B130
L_8016AFE8:
    bl      SNRead8
    cmpwi   r3, 0
    beq     L_8016AFE8
L_8016AFF4:
    bl      fn_8016B130
    bl      SNRead8
    cmpwi   r3, 0xff
    beq     L_8016AFF4
    bl      fn_8016B130
    andi.   r29, r31, 0x1e0
    beq     L_8016B030
    lis     r28, 0xcc00
    stw     r30, 0x682c(r28)
    stw     r29, 0x6830(r28)
    li      r3, 7
    stw     r3, 0x6834(r28)
    add     r30, r30, r29
    andi.   r29, r29, 0x1f
    bl      SNSync
L_8016B030:
    andi.   r28, r31, 0x1c
    beq     L_8016B054
    li      r29, 0
L_8016B03C:
    lwzx    r3, r30, r29
    bl      SNWrite32
    addi    r29, r29, 4
    cmpw    r29, r28
    blt     L_8016B03C
    add     r30, r30, r29
L_8016B054:
    andi.   r28, r31, 3
    beq     L_8016B074
    li      r29, 0
L_8016B060:
    lbzx    r3, r30, r29
    bl      SNWrite8
    addi    r29, r29, 1
    cmpw    r29, r28
    blt     L_8016B060
L_8016B074:
    li      r3, 0xf
    mtctr   r3
L_8016B07C:
    bdnz    L_8016B07C
    bl      fn_8016B11C
    li      r3, 0
    lwz     r31, 8(r1)
    lwz     r30, 0xc(r1)
    lwz     r29, 0x10(r1)
    lwz     r28, 0x14(r1)
    lwz     r0, 0x1c(r1)
    addi    r1, r1, 0x18
    mtlr    r0
    blr
    // clang-format on
}
