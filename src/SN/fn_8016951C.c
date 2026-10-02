asm void fn_8016951C(void)
{
    // clang-format off
    nofralloc
    lwz     r5, 0x390(r31)
    mtspr   920, r5
    lwz     r5, 0x388(r31)
    mtspr   1009, r5
    lwz     r5, 0x380(r31)
    mtspr   1008, r5
    lwz     r5, 0x450(r31)
    mtspr   1013, r5
    lwz     r5, 0x350(r31)
    mtctr   r5
    lwz     r5, 0x348(r31)
    mtxer   r5
    lwz     r5, 0x370(r31)
    mtsrr0  r5
    lwz     r5, 0x378(r31)
    mtsrr1  r5
    blr
    // clang-format on
}
