extern int errno;
extern int fn_8017A71C(short request, int arg1, int arg2);

asm int _lseek_r(void* device, short flag, int arg1, int arg2)
{
    // clang-format off
    nofralloc
    stwu    r1, -16(r1)
    mflr    r0
    stw     r31, 12(r1)
    stw     r0, 20(r1)
    mr      r31, r3
    li      r0, 0
    mr      r3, r4
    stw     r0, errno
    mr      r4, r5
    mr      r5, r6
    bl      fn_8017A71C
    cmpwi   r3, -1
    bne     epilogue
    lwz     r0, errno
    cmpwi   r0, 0
    beq     epilogue
    stw     r0, 0(r31)
epilogue:
    lwz     r0, 20(r1)
    mtlr    r0
    lwz     r31, 12(r1)
    addi    r1, r1, 16
    blr
    // clang-format on
}
