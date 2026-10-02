extern void ICFlashInvalidate(void);

asm void fn_8017D3B0(register void (*addr)(void))
{
    // clang-format off
    nofralloc
    mflr  r0
    stw   r0, 4(r1)
    stwu  r1, -0x18(r1)
    stw   r31, 0x14(r1)
    mr    r31, r3
    bl    ICFlashInvalidate
    sync
    isync
    mtlr  r31
    blr
    // clang-format on
}
