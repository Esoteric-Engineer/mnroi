asm int strround(char* s, int i)
{
    // clang-format off
    nofralloc
    mr.     r4, r4
    ble     L_ret1
    subi    r4, r4, 1
    lbzx    r0, r3, r4
    extsb   r0, r0
    cmpwi   r0, 0x34
    ble     L_ret1
    li      r9, 0x30
L_loop:
    stbx    r9, r3, r4
    subic.  r4, r4, 1
    ble     L_chk
    lbzx    r0, r3, r4
    cmpwi   r0, 0x39
    beq     L_loop
L_chk:
    lbzx    r9, r3, r4
    cmpwi   r9, 0x39
    bne     L_inc
    li      r3, 0
    blr
L_inc:
    addi    r0, r9, 1
    stbx    r0, r3, r4
L_ret1:
    li      r3, 1
    blr
    // clang-format on
}
