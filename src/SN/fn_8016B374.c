void fn_8016B104(void);
void fn_8016B130(void);
int SNRead8(void);
void SNWrite8(int);

asm void fn_8016B374(int arg)
{
    // clang-format off
    nofralloc
    mflr    r0
    stwu    r1, -0x18(r1)
    stw     r0, 0x1c(r1)
    stmw    r28, 8(r1)
    mr      r31, r3
    bl      fn_8016B104
L_8016B38C:
    bl      SNRead8
    cmpwi   r3, 0
    beq     L_8016B38C
L_8016B398:
    bl      fn_8016B130
    bl      SNRead8
    cmpwi   r3, 0xff
    beq     L_8016B398
    bl      fn_8016B130
    li      r3, 3
    bl      SNWrite8
    srwi    r3, r31, 8
    bl      SNWrite8
    mr      r3, r31
    bl      SNWrite8
    lwz     r0, 0x1c(r1)
    mtlr    r0
    lmw     r28, 8(r1)
    addi    r1, r1, 0x18
    blr
    // clang-format on
}
