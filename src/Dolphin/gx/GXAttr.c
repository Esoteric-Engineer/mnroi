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
