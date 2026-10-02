__declspec(section ".init") asm void fn_80003300(void)
{
    // clang-format off
    nofralloc
    li r3, 0x0
    mtspr GQR0, r3
    mtspr GQR1, r3
    mtspr GQR2, r3
    mtspr GQR3, r3
    mtspr GQR4, r3
    mtspr GQR5, r3
    mtspr GQR6, r3
    mtspr GQR7, r3
    blr
    // clang-format on
}
