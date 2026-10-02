extern unsigned long* __VMBASEVirtualAddrToPageTableAddr(unsigned long addr);

// GCC output, so asm.
asm unsigned long VMBASEIsPageValid(unsigned long addr)
{
    // clang-format off
    nofralloc
    stwu    r1, -0x10(r1)
    mflr    r0
    stw     r0, 0x14(r1)
    bl      __VMBASEVirtualAddrToPageTableAddr
    lwz     r0, 0x0(r3)
    rlwinm  r3, r0, 1, 31, 31
    lwz     r0, 0x14(r1)
    mtlr    r0
    addi    r1, r1, 0x10
    blr
    // clang-format on
}
