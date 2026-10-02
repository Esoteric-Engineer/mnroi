extern int _read_r(void* reent, short fd, char* buf, int n);

asm int __sread(void* fp, char* buf, int n)
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
    bl      _read_r
    mr.     r3, r3
    blt     fail
    lwz     r0, 88(r31)
    add     r0, r0, r3
    stw     r0, 88(r31)
    b       epilogue
fail:
    lhz     r0, 12(r31)
    rlwinm  r0, r0, 0, 20, 18
    sth     r0, 12(r31)
epilogue:
    lwz     r0, 20(r1)
    mtlr    r0
    lwz     r31, 12(r1)
    addi    r1, r1, 16
    blr
    // clang-format on
}
