void SNDeselect(void);
void SNWiggleSelect(void);
int SNRead8(void);
void SNWrite8(void);
void SNWrite32(void);

asm void fn_8016B4B0(void)
{
    // clang-format off
    nofralloc
    mflr    r0
    stwu    r1, -0x18(r1)
    stw     r0, 0x1c(r1)
    stmw    r28, 8(r1)
    mr      r31, r4
    mr      r30, r3
    bl      SNWiggleSelect
L_8016B4CC:
    bl      SNRead8
    cmpwi   r3, 0
    beq     L_8016B4CC
L_8016B4D8:
    bl      SNWiggleSelect
    bl      SNRead8
    cmpwi   r3, 0xff
    beq     L_8016B4D8
    bl      SNWiggleSelect
    andi.   r28, r31, 0x1c
    beq     L_8016B510
    li      r29, 0
L_8016B4F8:
    lwzx    r3, r30, r29
    bl      SNWrite32
    addi    r29, r29, 4
    cmpw    r29, r28
    blt     L_8016B4F8
    add     r30, r30, r29
L_8016B510:
    andi.   r28, r31, 3
    beq     L_8016B530
    li      r29, 0
L_8016B51C:
    lbzx    r3, r30, r29
    bl      SNWrite8
    addi    r29, r29, 1
    cmpw    r29, r28
    blt     L_8016B51C
L_8016B530:
    li      r3, 0xf
    mtctr   r3
L_8016B538:
    bdnz    L_8016B538
    bl      SNDeselect
    lwz     r0, 0x1c(r1)
    mtlr    r0
    lmw     r28, 8(r1)
    addi    r1, r1, 0x18
    blr
    // clang-format on
}
