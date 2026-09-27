void SNSelect(void);
void SNDeselect(void);
void SNWiggleSelect(void);
int SNRead8(void);
void SNWrite8(int arg);
int SNRead32(void);

asm int SNQueryData(void)
{
    // clang-format off
    nofralloc
    mflr    r0
    stw     r0, 0x4(r1)
    stwu    r1, -0x8(r1)
    bl      SNSelect
L_wait0:
    bl      SNRead8
    cmpwi   r3, 0x0
    beq     L_wait0
L_skip0:
    bl      SNWiggleSelect
    bl      SNRead8
    cmpwi   r3, 0xff
    beq     L_skip0
    bl      SNWiggleSelect
    li      r3, 0x1
    bl      SNWrite8
    bl      SNWiggleSelect
L_wait1:
    bl      SNRead8
    cmpwi   r3, 0x0
    beq     L_wait1
L_skip1:
    bl      SNWiggleSelect
    bl      SNRead8
    cmpwi   r3, 0xff
    beq     L_skip1
    bl      SNWiggleSelect
    bl      SNRead32
    mr      r5, r3
    li      r3, 0xf
    mtctr   r3
L_spin:
    bdnz    L_spin
    bl      SNDeselect
    mr      r3, r5
    lwz     r0, 0xc(r1)
    addi    r1, r1, 0x8
    mtlr    r0
    blr
    // clang-format on
}
