extern char lbl_804CFE6C[];

asm void SNHandler(void)
{
    // clang-format off
    nofralloc
    mflr    r0
    stw     r0, 0x4(r1)
    stwu    r1, -0x8(r1)
    li      r0, 0x1000
    lis     r5, 0xcc00
    stw     r0, 0x3000(r5)
    lis     r5, (lbl_804CFE6C + 0xB4)@h
    ori     r5, r5, (lbl_804CFE6C + 0xB4)@l
    lwz     r5, 0x0(r5)
    cmpwi   r5, 0x0
    beq     L_end
    mtlr    r5
    lis     r5, (lbl_804CFE6C + 0xBC)@h
    ori     r5, r5, (lbl_804CFE6C + 0xBC)@l
    li      r0, 0x1
    stb     r0, 0x0(r5)
    blrl
L_end:
    lwz     r0, 0xc(r1)
    addi    r1, r1, 0x8
    mtlr    r0
    blr
    // clang-format on
}
