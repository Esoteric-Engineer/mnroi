extern unsigned long* __VMBASEVirtualAddrToPageTableAddr(unsigned long addr);

// GCC output, so asm.
asm void VMBASESetPageReferenced(unsigned long addr, int referenced)
{
    // clang-format off
    nofralloc
    stwu    r1, -0x10(r1)
    mflr    r0
    stw     r0, 0x14(r1)
    stw     r31, 0xc(r1)
    mr      r31, r4
    bl      __VMBASEVirtualAddrToPageTableAddr
    cmpwi   r31, 0
    beq     zero
    lwz     r0, 0x4(r3)
    ori     r0, r0, 0x100
    stw     r0, 0x4(r3)
    b       done
zero:
    lwz     r0, 0x4(r3)
    rlwinm  r0, r0, 0, 24, 22
    stw     r0, 0x4(r3)
done:
    lwz     r0, 0x14(r1)
    lwz     r31, 0xc(r1)
    mtlr    r0
    addi    r1, r1, 0x10
    blr
    // clang-format on
}
