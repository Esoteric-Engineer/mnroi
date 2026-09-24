extern void __ashrdi3(void);

asm void __shr2i(void)
{
    // clang-format off
    nofralloc
    b       __ashrdi3
    // clang-format on
}
