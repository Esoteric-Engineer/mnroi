extern char lbl_8057BD88[];
void DCInvalidateRange(void);
void fn_8016B104(void);
void fn_8016B11C(void);
void fn_8016B130(void);
int SNRead8(void);
int SNRead32(void);
void SNWrite8(void);
void SNSync(void);

asm int SNRead(void)
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
    bl      DCInvalidateRange
    bl      fn_8016B104
L_8016AD80:
    bl      SNRead8
    cmpwi   r3, 0
    beq     L_8016AD80
L_8016AD8C:
    bl      fn_8016B130
    bl      SNRead8
    cmpwi   r3, 0xff
    beq     L_8016AD8C
    bl      fn_8016B130
    li      r3, 2
    bl      SNWrite8
    lis     r3, (lbl_8057BD88+0x138)@h
    ori     r3, r3, (lbl_8057BD88+0x138)@l
    lwz     r4, 0(r3)
    srw     r28, r31, r4
    cmpwi   r28, 0
    bne     L_8016ADD0
    lwz     r4, 8(r3)
    and.    r28, r31, r4
    beq     L_8016AEDC
    b       L_8016AE3C
L_8016ADD0:
    bl      fn_8016B130
L_8016ADD4:
    bl      SNRead8
    cmpwi   r3, 0
    beq     L_8016ADD4
L_8016ADE0:
    bl      fn_8016B130
    bl      SNRead8
    cmpwi   r3, 0xff
    beq     L_8016ADE0
    bl      fn_8016B130
    lis     r5, (lbl_8057BD88+0x138)@h
    ori     r5, r5, (lbl_8057BD88+0x138)@l
    lwz     r5, 4(r5)
    lis     r29, 0xcc00
    stw     r30, 0x682c(r29)
    stw     r5, 0x6830(r29)
    li      r3, 3
    stw     r3, 0x6834(r29)
    bl      SNSync
    add     r30, r30, r5
    subi    r28, r28, 1
    cmpwi   r28, 0
    bne     L_8016ADD0
    lis     r5, (lbl_8057BD88+0x138)@h
    ori     r5, r5, (lbl_8057BD88+0x138)@l
    lwz     r5, 8(r5)
    and.    r28, r31, r5
    beq     L_8016AEDC
L_8016AE3C:
    bl      fn_8016B130
L_8016AE40:
    bl      SNRead8
    cmpwi   r3, 0
    beq     L_8016AE40
L_8016AE4C:
    bl      fn_8016B130
    bl      SNRead8
    cmpwi   r3, 0xff
    beq     L_8016AE4C
    bl      fn_8016B130
    lis     r5, (lbl_8057BD88+0x138)@h
    ori     r5, r5, (lbl_8057BD88+0x138)@l
    lwz     r5, 0xc(r5)
    and     r29, r31, r5
    andi.   r29, r29, 0xffe0
    beq     L_8016AE98
    lis     r28, 0xcc00
    stw     r30, 0x682c(r28)
    stw     r29, 0x6830(r28)
    li      r3, 3
    stw     r3, 0x6834(r28)
    add     r30, r30, r29
    andi.   r29, r29, 0x1f
    bl      SNSync
L_8016AE98:
    andi.   r28, r31, 0x1c
    beq     L_8016AEBC
    li      r29, 0
L_8016AEA4:
    bl      SNRead32
    stwx    r3, r30, r29
    addi    r29, r29, 4
    cmpw    r29, r28
    blt     L_8016AEA4
    add     r30, r30, r29
L_8016AEBC:
    andi.   r28, r31, 3
    beq     L_8016AEDC
    li      r29, 0
L_8016AEC8:
    bl      SNRead8
    stbx    r3, r30, r29
    addi    r29, r29, 1
    cmpw    r29, r28
    blt     L_8016AEC8
L_8016AEDC:
    li      r3, 0xf
    mtctr   r3
L_8016AEE4:
    bdnz    L_8016AEE4
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
