asm void __GXSetAttr(register void* attr, register int value)
{
    // clang-format off
    nofralloc
    lwz     r0, 12(attr)
    rlwimi  r0, value, 27, 11, 31
    stw     r0, 12(attr)
    blr
    // clang-format on
}

asm void __GXSetAttr2(register void* attr, register int value, register int mask)
{
    // clang-format off
    nofralloc
    lwz     r0, 0(attr)
    rlwimi  r0, value, 0, 30, 31
    stw     r0, 0(attr)
    lwz     r0, 0(attr)
    rlwimi  r0, mask, 2, 28, 29
    stw     r0, 0(attr)
    blr
    // clang-format on
}
