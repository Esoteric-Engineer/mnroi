asm int fn_80178F54(int* out_err, char* mode, int* out_flags)
{
    // clang-format off
    nofralloc
    lbz     r0, 0(r4)
    mr      r9, r3
    extsb   r0, r0
    cmpwi   r0, 'r'
    beq     case_r
    bgt     check_w
    cmpwi   r0, 'a'
    beq     case_a
    b       bad_mode
check_w:
    cmpwi   r0, 'w'
    beq     case_w
    b       bad_mode
case_r:
    li      r3, 4
    li      r9, 0
    li      r11, 0
    b       check_plus
case_w:
    li      r3, 8
    li      r9, 1
    li      r11, 1536
    b       check_plus
case_a:
    li      r3, 264
    li      r9, 1
    li      r11, 520
    b       check_plus
bad_mode:
    li      r0, 22
    li      r3, 0
    stw     r0, 0(r9)
    blr
check_plus:
    lbz     r0, 1(r4)
    cmpwi   r0, '+'
    beq     has_plus
    lbz     r0, 2(r4)
    cmpwi   r0, '+'
    bne     no_plus
has_plus:
    li      r3, 16
    li      r9, 2
no_plus:
    or      r0, r9, r11
    stw     r0, 0(r5)
    blr
    // clang-format on
}
