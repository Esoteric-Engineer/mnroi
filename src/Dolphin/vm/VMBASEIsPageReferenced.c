extern unsigned long* __VMBASEVirtualAddrToPageTableAddr(unsigned long addr);

// GCC output, so asm.
asm unsigned long VMBASEIsPageReferenced(unsigned long addr)
{
    // clang-format off
    nofralloc
    stwu    r1, -0x10(r1)
    mflr    r0
    stw     r0, 0x14(r1)
    bl      __VMBASEVirtualAddrToPageTableAddr
    lwz     r0, 0x4(r3)
    rlwinm  r3, r0, 24, 31, 31
    lwz     r0, 0x14(r1)
    mtlr    r0
    addi    r1, r1, 0x10
    blr
    // clang-format on
}
