extern void __divdi3(void);

asm void __div2i(void)
{
    // clang-format off
    nofralloc
    b       __divdi3
    // clang-format on
}
