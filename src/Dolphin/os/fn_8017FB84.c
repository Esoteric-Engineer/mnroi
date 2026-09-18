asm void fn_8017FB84(void)
{
    // clang-format off
    nofralloc
    mfspr r9, HID0
    ori   r10, r9, 8
    mtspr HID0, r10
    isync
    sync
    mtspr HID0, r9
    rfi
    nop
    // clang-format on
}
