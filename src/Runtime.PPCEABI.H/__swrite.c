extern int _lseek_r(void* reent, short fd, int offset, int whence);
extern int _write_r(void* reent, short fd, const char* buf, int n);

asm int __swrite(void* fp, const char* buf, int n)
{
    // clang-format off
    nofralloc
    stwu    r1, -24(r1)
    mflr    r0
    stmw    r29, 12(r1)
    stw     r0, 28(r1)
    mr      r31, r3
    mr      r30, r4
    lhz     r0, 12(r31)
    mr      r29, r5
    andi.   r9, r0, 0x100
    beq     noappend
    lwz     r3, 92(r31)
    li      r5, 0
    lha     r4, 14(r31)
    li      r6, 2
    bl      _lseek_r
noappend:
    lhz     r0, 12(r31)
    mr      r5, r30
    lha     r4, 14(r31)
    mr      r6, r29
    rlwinm  r0, r0, 0, 20, 18
    lwz     r3, 92(r31)
    sth     r0, 12(r31)
    bl      _write_r
    lwz     r0, 28(r1)
    mtlr    r0
    lmw     r29, 12(r1)
    addi    r1, r1, 24
    blr
    // clang-format on
}
