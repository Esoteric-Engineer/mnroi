extern char lbl_8057BEE0[];
void fn_8016BF28(void);
void fn_8016BFB0(void);

asm void fn_8016BFF4(int arg)
{
    // clang-format off
    nofralloc
    stwu    r1, -8(r1)
    mflr    r0
    stw     r0, 0xc(r1)
    lis     r9, (lbl_8057BEE0+0x88)@ha
    addi    r3, r3, 0x1f
    lwz     r0, (lbl_8057BEE0+0x88)@l(r9)
    clrrwi  r8, r3, 5
    cmpw    r8, r0
    bne     L_else
    lis     r10, (lbl_8057BEE0+0x84)@ha
    lis     r11, (lbl_8057BEE0+0x80)@ha
    lwz     r0, (lbl_8057BEE0+0x84)@l(r10)
    li      r9, 0
    lis     r3, (lbl_8057BEE0+0x60)@ha
    stw     r9, (lbl_8057BEE0+0x80)@l(r11)
    add     r0, r0, r8
    addi    r3, r3, (lbl_8057BEE0+0x60)@l
    stw     r0, (lbl_8057BEE0+0x84)@l(r10)
    bl      fn_8016BF28
    b       L_end
L_else:
    lis     r0, 3
    lis     r10, (lbl_8057BEE0+0x84)@ha
    li      r9, -1
    lis     r11, (lbl_8057BEE0+0x80)@ha
    ori     r0, r0, 0x1100
    stw     r9, (lbl_8057BEE0+0x84)@l(r10)
    stw     r0, (lbl_8057BEE0+0x80)@l(r11)
    bl      fn_8016BFB0
L_end:
    lwz     r0, 0xc(r1)
    mtlr    r0
    addi    r1, r1, 8
    blr
    // clang-format on
}
