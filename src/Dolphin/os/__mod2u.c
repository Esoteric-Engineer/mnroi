extern void __umoddi3(void);

asm void __mod2u(void)
{
    // clang-format off
    nofralloc
    b       __umoddi3
    // clang-format on
}
