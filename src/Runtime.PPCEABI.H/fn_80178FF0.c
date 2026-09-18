extern int lbl_804825A0;

asm void fn_80178FF0(void)
{
    // clang-format off
    nofralloc
    stwu    r1, -16(r1)
    mflr    r0
    stmw    r30, 8(r1)
    stw     r0, 20(r1)
    lis     r9, lbl_804825A0@ha
    lwz     r11, lbl_804825A0@l(r9)
    addi    r10, r9, lbl_804825A0@l
    cmpwi   r11, -1
    bne     have_count
    lwz     r0, 4(r10)
    li      r11, 0
    cmpwi   r0, 0
    beq     have_count
    addi    r9, r10, 4
count_loop:
    lwzu    r0, 4(r9)
    addi    r11, r11, 1
    cmpwi   r0, 0
    bne     count_loop
have_count:
    mr.     r0, r11
    beq     epilogue
    lis     r9, lbl_804825A0@ha
    slwi    r0, r0, 2
    addi    r9, r9, lbl_804825A0@l
    mr      r30, r9
    add     r31, r0, r9
call_loop:
    lwz     r9, 0(r31)
    addi    r31, r31, -4
    mtlr    r9
    blrl
    cmpw    r31, r30
    bne     call_loop
epilogue:
    lwz     r0, 20(r1)
    mtlr    r0
    lmw     r30, 8(r1)
    addi    r1, r1, 16
    blr
    // clang-format on
}
