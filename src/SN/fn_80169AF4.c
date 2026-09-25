void fn_80169BF8(void);

asm void fn_80169AF4(void)
{
    // clang-format off
    nofralloc
    stw     r31, 0xdf8(r0)
    mfsrr0  r31
    stw     r31, 0xdf4(r0)
    mfsrr1  r31
    stw     r31, 0xdf0(r0)
    mfmsr   r31
    ori     r31, r31, 0x30
    mtsrr1  r31
    lis     r31, fn_80169BF8@h
    ori     r31, r31, fn_80169BF8@l
    mtsrr0  r31
    mflr    r31
    stw     r31, 0xdec(r0)
    bl      L_80169B2C
L_80169B2C:
    mflr    r31
    stw     r31, 0xde8(r0)
    rfi
    opword  0
    opword  0
    opword  0
    opword  0
    // clang-format on
}
