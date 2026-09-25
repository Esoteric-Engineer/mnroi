void fn_8016B130(void);
int fn_8016B16C(void);

asm void fn_8016B29C(void)
{
    // clang-format off
    nofralloc
    mflr    r0
    stwu    r1, -0x18(r1)
    stw     r0, 0x1c(r1)
    stmw    r28, 8(r1)
    mr      r31, r4
    mr      r30, r3
    bl      fn_8016B130
L_8016B2B8:
    bl      fn_8016B16C
    cmpwi   r3, 0
    beq     L_8016B2B8
L_8016B2C4:
    bl      fn_8016B130
    bl      fn_8016B16C
    cmpwi   r3, 0xff
    beq     L_8016B2C4
    bl      fn_8016B130
    lis     r29, 0xcc00
    stw     r30, 0x682c(r29)
    stw     r31, 0x6830(r29)
    li      r3, 3
    stw     r3, 0x6834(r29)
    lwz     r3, 0x6828(r29)
    ori     r3, r3, 0xc
    stw     r3, 0x6828(r29)
    lwz     r0, 0x1c(r1)
    mtlr    r0
    lmw     r28, 8(r1)
    addi    r1, r1, 0x18
    blr
    // clang-format on
}
