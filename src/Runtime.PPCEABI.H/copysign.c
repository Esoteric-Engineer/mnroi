asm double copysign(double x, double y)
{
    // clang-format off
    nofralloc
    stwu    r1, -16(r1)
    fmr     f0, f1
    stfd    f0, 8(r1)
    lwz     r7, 8(r1)
    lwz     r8, 12(r1)
    stfd    f2, 8(r1)
    lwz     r9, 8(r1)
    lwz     r10, 12(r1)
    stfd    f1, 8(r1)
    lwz     r11, 8(r1)
    lwz     r12, 12(r1)
    clrlwi  r7, r7, 1
    clrrwi  r9, r9, 31
    or      r11, r7, r9
    stw     r11, 8(r1)
    stw     r12, 12(r1)
    lfd     f0, 8(r1)
    fmr     f1, f0
    addi    r1, r1, 16
    blr
    // clang-format on
}
