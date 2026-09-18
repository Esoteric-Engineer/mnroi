asm int OSDisableInterrupts(void)
{
    // clang-format off
    nofralloc
    mfmsr  r3
    rlwinm r4, r3, 0, 17, 15
    mtmsr  r4
    rlwinm r3, r3, 17, 31, 31
    blr
    // clang-format on
}

asm int OSEnableInterrupts(void)
{
    // clang-format off
    nofralloc
    mfmsr  r3
    ori    r4, r3, 0x8000
    mtmsr  r4
    rlwinm r3, r3, 17, 31, 31
    blr
    // clang-format on
}

asm int OSRestoreInterrupts(register int level)
{
    // clang-format off
    nofralloc
    cmpwi  level, 0
    mfmsr  r4
    beq    _disable
    ori    r5, r4, 0x8000
    b      _restore
_disable:
    rlwinm r5, r4, 0, 17, 15
_restore:
    mtmsr  r5
    rlwinm r3, r4, 17, 31, 31
    blr
    // clang-format on
}
