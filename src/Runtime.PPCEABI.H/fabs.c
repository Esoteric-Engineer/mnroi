asm double fabs(double x)
{
    // clang-format off
    nofralloc
    stwu    r1, -16(r1)
    fmr     f0, f1
    stfd    f0, 8(r1)
    lwz     r11, 8(r1)
    lwz     r12, 12(r1)
    stfd    f1, 8(r1)
    lwz     r9, 8(r1)
    lwz     r10, 12(r1)
    clrlwi  r9, r11, 1
    stw     r9, 8(r1)
    stw     r10, 12(r1)
    lfd     f0, 8(r1)
    fmr     f1, f0
    addi    r1, r1, 16
    blr
    // clang-format on
}
