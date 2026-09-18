asm long long __ashldi3(long long u, int b)
{
    // clang-format off
    nofralloc
    mr.    r5, r5
    beqlr
    subfic r0, r5, 32
    cmpwi  r0, 0
    bgt    positive
    neg    r0, r0
    li     r12, 0
    slw    r11, r4, r0
    b      done
positive:
    slw    r9, r3, r5
    srw    r0, r4, r0
    slw    r12, r4, r5
    or     r11, r9, r0
done:
    mr     r3, r11
    mr     r4, r12
    blr
    // clang-format on
}

asm long long __ashrdi3(long long u, int b)
{
    // clang-format off
    nofralloc
    mr.    r5, r5
    beqlr
    subfic r0, r5, 32
    cmpwi  r0, 0
    bgt    positive
    neg    r0, r0
    srawi  r11, r3, 31
    sraw   r12, r3, r0
    b      done
positive:
    srw    r9, r4, r5
    slw    r0, r3, r0
    sraw   r11, r3, r5
    or     r12, r9, r0
done:
    mr     r3, r11
    mr     r4, r12
    blr
    // clang-format on
}
