extern void __ashldi3(void);

asm void __shl2i(void)
{
    // clang-format off
    nofralloc
    b       __ashldi3
    // clang-format on
}
