extern void __udivdi3(void);

asm void __div2u(void)
{
    // clang-format off
    nofralloc
    b       __udivdi3
    // clang-format on
}
