void fn_8016B104(void);
void fn_8016B130(void);
int fn_8016B16C(void);
void SNWrite8(int);

asm void fn_8016B24C(void)
{
    // clang-format off
    nofralloc
    mflr    r0
    stwu    r1, -0x18(r1)
    stw     r0, 0x1c(r1)
    stmw    r28, 8(r1)
    bl      fn_8016B104
L_8016B260:
    bl      fn_8016B16C
    cmpwi   r3, 0
    beq     L_8016B260
L_8016B26C:
    bl      fn_8016B130
    bl      fn_8016B16C
    cmpwi   r3, 0xff
    beq     L_8016B26C
    bl      fn_8016B130
    li      r3, 2
    bl      SNWrite8
    lwz     r0, 0x1c(r1)
    mtlr    r0
    lmw     r28, 8(r1)
    addi    r1, r1, 0x18
    blr
    // clang-format on
}
