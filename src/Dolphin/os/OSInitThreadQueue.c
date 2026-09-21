asm void OSInitThreadQueue(register void* p)
{
    // clang-format off
    nofralloc
    li      r0, 0
    stw     r0, 4(r3)
    stw     r0, 0(r3)
    blr
    // clang-format on
}
