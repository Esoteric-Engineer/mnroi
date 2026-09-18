asm float copysignf(float x, float y)
{
    // clang-format off
    nofralloc
    stwu    r1, -16(r1)
    stfs    f1, 8(r1)
    lwz     r9, 8(r1)
    stfs    f2, 8(r1)
    lwz     r0, 8(r1)
    clrlwi  r9, r9, 1
    clrrwi  r0, r0, 31
    or      r9, r9, r0
    stw     r9, 8(r1)
    lfs     f0, 8(r1)
    fmr     f1, f0
    addi    r1, r1, 16
    blr
    // clang-format on
}
