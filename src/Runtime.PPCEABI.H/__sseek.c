extern int fn_80178DF0(void* reent, short fd, int offset, int whence);

asm int __sseek(void* fp, int offset, int whence)
{
    // clang-format off
    nofralloc
    stwu    r1, -16(r1)
    mflr    r0
    stw     r31, 12(r1)
    stw     r0, 20(r1)
    mr      r0, r4
    mr      r31, r3
    mr      r6, r5
    lwz     r3, 92(r31)
    lha     r4, 14(r31)
    mr      r5, r0
    bl      fn_80178DF0
    cmpwi   r3, -1
    bne     ok
    lhz     r0, 12(r31)
    rlwinm  r0, r0, 0, 20, 18
    b       store
ok:
    lhz     r0, 12(r31)
    stw     r3, 88(r31)
    ori     r0, r0, 0x1000
store:
    sth     r0, 12(r31)
    lwz     r0, 20(r1)
    mtlr    r0
    lwz     r31, 12(r1)
    addi    r1, r1, 16
    blr
    // clang-format on
}
