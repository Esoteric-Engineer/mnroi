asm void Reset(unsigned long resetCode)
{
    // clang-format off
    nofralloc
    b L_1BC
L_1A0:
    mfspr   r8, HID0
    ori     r8, r8, 0x8
    mtspr   HID0, r8
    isync
    sync
    nop
    b L_1C0
L_1BC:
    b L_1DC
L_1C0:
    mftb    r5, 268
L_1C4:
    mftb    r6, 268
    subf    r7, r5, r6
    cmplwi  r7, 0x1124
    blt     L_1C4
    nop
    b L_1E0
L_1DC:
    b L_1FC
L_1E0:
    lis     r8, 0xcc00
    ori     r8, r8, 0x3000
    li      r4, 0x3
    stw     r4, 0x24(r8)
    stw     r3, 0x24(r8)
    nop
    b L_200
L_1FC:
    b L_208
L_200:
    nop
    b L_200
L_208:
    b L_1A0
    // clang-format on
}
