asm float fabsf(float x)
{
    // clang-format off
    nofralloc
    stwu    r1, -16(r1)
    stfs    f1, 8(r1)
    lwz     r0, 8(r1)
    clrlwi  r0, r0, 1
    stw     r0, 8(r1)
    lfs     f0, 8(r1)
    fmr     f1, f0
    addi    r1, r1, 16
    blr
    // clang-format on
}
