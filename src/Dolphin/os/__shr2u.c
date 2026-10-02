extern void __lshrdi3(void);

asm void __shr2u(void)
{
    // clang-format off
    nofralloc
    b       __lshrdi3
    // clang-format on
}
