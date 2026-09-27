extern unsigned long* __VMBASEVirtualAddrToPageTableAddr(unsigned long addr);
extern void DCStoreRange(void* addr, unsigned long nBytes);
extern void __VMBASESetVirtualAddressForPageInMRAM(unsigned long page, unsigned long addr);

// GCC output, so asm.
asm void VMBASESetPageTableEntry(unsigned long addr, unsigned long aramAddr, unsigned long page)
{
    // clang-format off
    nofralloc
    stwu    r1, -0x20(r1)
    mflr    r0
    stw     r0, 0x24(r1)
    stw     r31, 0x1c(r1)
    mr      r31, r5
    stw     r30, 0x18(r1)
    mr      r30, r4
    stw     r29, 0x14(r1)
    mr      r29, r3
    bl      __VMBASEVirtualAddrToPageTableAddr
    rlwinm  r4, r29, 10, 26, 31
    rlwinm  r0, r30, 0, 4, 19
    oris    r4, r4, 0x8000
    stw     r4, 0x0(r3)
    li      r4, 8
    stw     r0, 0x4(r3)
    bl      DCStoreRange
    mr      r3, r31
    mr      r4, r29
    bl      __VMBASESetVirtualAddressForPageInMRAM
    lwz     r0, 0x24(r1)
    lwz     r31, 0x1c(r1)
    lwz     r30, 0x18(r1)
    lwz     r29, 0x14(r1)
    mtlr    r0
    addi    r1, r1, 0x20
    blr
    // clang-format on
}
