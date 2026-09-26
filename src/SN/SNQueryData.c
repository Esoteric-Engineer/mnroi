void fn_8016B104(void);
void fn_8016B11C(void);
void fn_8016B130(void);
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
    bl      fn_8016B104
L_wait0:
    bl      SNRead8
    cmpwi   r3, 0x0
    beq     L_wait0
L_skip0:
    bl      fn_8016B130
    bl      SNRead8
    cmpwi   r3, 0xff
    beq     L_skip0
    bl      fn_8016B130
    li      r3, 0x1
    bl      SNWrite8
    bl      fn_8016B130
L_wait1:
    bl      SNRead8
    cmpwi   r3, 0x0
    beq     L_wait1
L_skip1:
    bl      fn_8016B130
    bl      SNRead8
    cmpwi   r3, 0xff
    beq     L_skip1
    bl      fn_8016B130
    bl      SNRead32
    mr      r5, r3
    li      r3, 0xf
    mtctr   r3
L_spin:
    bdnz    L_spin
    bl      fn_8016B11C
    mr      r3, r5
    lwz     r0, 0xc(r1)
    addi    r1, r1, 0x8
    mtlr    r0
    blr
    // clang-format on
}
