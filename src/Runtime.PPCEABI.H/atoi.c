extern long fn_80177004(const char* str, char** end, int base);

asm int atoi(const char* str)
{
    // clang-format off
    nofralloc
    stwu    r1, -8(r1)
    mflr    r0
    stw     r0, 12(r1)
    li      r4, 0
    li      r5, 10
    bl      fn_80177004
    lwz     r0, 12(r1)
    mtlr    r0
    addi    r1, r1, 8
    blr
    // clang-format on
}
