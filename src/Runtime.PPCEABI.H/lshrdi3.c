asm long long __lshrdi3(long long u, int b)
{
    // clang-format off
    nofralloc
    mr.    r5, r5
    beqlr
    subfic r0, r5, 32
    cmpwi  r0, 0
    bgt    positive
    neg    r0, r0
    li     r11, 0
    srw    r12, r3, r0
    b      done
positive:
    srw    r9, r4, r5
    slw    r0, r3, r0
    srw    r11, r3, r5
    or     r12, r9, r0
done:
    mr     r3, r11
    mr     r4, r12
    blr
    // clang-format on
}
