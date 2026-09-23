extern int _fstat_r(void* reent, short fd, void* st);
extern int __sseek(void* fp, int offset, int whence);

asm void __smakebuf(void* fp)
{
    // clang-format off
    nofralloc
    stwu    r1, -0x50(r1)
    mflr    r0
    stw     r31, 0x4c(r1)
    stw     r0, 0x54(r1)
    mr      r31, r3
    lhz     r0, 0xc(r31)
    andi.   r9, r0, 0x2
    beq     unbuffered
    addi    r9, r31, 0x4a
    li      r0, 1
    stw     r0, 0x14(r31)
    stw     r9, 0x10(r31)
    stw     r9, 0(r31)
    b       epilogue
unbuffered:
    lha     r4, 0xe(r31)
    cmpwi   r4, 0
    blt     nopt
    lwz     r3, 0x5c(r31)
    addi    r5, r1, 8
    bl      _fstat_r
    cmpwi   r3, 0
    blt     nopt
    lwz     r9, 0xc(r1)
    li      r0, 0
    ori     r0, r0, 0x8000
    rlwinm  r9, r9, 0, 16, 19
    cmpw    r9, r0
    bne     nopt
    lwz     r0, 0x28(r31)
    lis     r9, __sseek@ha
    addi    r9, r9, __sseek@l
    cmpw    r0, r9
    bne     nopt
    lhz     r0, 0xc(r31)
    li      r9, 0x400
    stw     r9, 0x54(r31)
    ori     r0, r0, 0x400
    b       setflags
nopt:
    lhz     r0, 0xc(r31)
    ori     r0, r0, 0x800
setflags:
    sth     r0, 0xc(r31)
    lhz     r0, 0xc(r31)
    addi    r11, r31, 0x4a
    li      r9, 1
    stw     r11, 0x10(r31)
    ori     r0, r0, 2
    stw     r9, 0x14(r31)
    sth     r0, 0xc(r31)
    stw     r11, 0(r31)
epilogue:
    lwz     r0, 0x54(r1)
    mtlr    r0
    lwz     r31, 0x4c(r1)
    addi    r1, r1, 0x50
    blr
    // clang-format on
}
