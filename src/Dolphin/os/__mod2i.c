extern void __moddi3(void);

asm void __mod2i(void)
{
    // clang-format off
    nofralloc
    b       __moddi3
    // clang-format on
}
