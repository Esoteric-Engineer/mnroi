extern unsigned long* __VMBASEVirtualAddrToPageTableAddr(unsigned long addr);
extern void DCStoreRange(void* addr, unsigned long nBytes);
extern void __VMBASESetVirtualAddressForPageInMRAM(unsigned long page, unsigned long addr);
extern void VMBASESetPageLocked(unsigned long page, int locked);
extern void __VMBASEClearPageFromTLB(unsigned long addr);

// GCC output, so asm.
asm void VMBASEClearPageTableEntry(unsigned long addr, unsigned long page)
{
    // clang-format off
    nofralloc
    stwu    r1, -0x10(r1)
    mflr    r0
    stw     r0, 0x14(r1)
    stw     r31, 0xc(r1)
    mr      r31, r4
    stw     r30, 0x8(r1)
    mr      r30, r3
    bl      __VMBASEVirtualAddrToPageTableAddr
    li      r0, 0
    li      r4, 8
    stw     r0, 0x0(r3)
    stw     r0, 0x4(r3)
    bl      DCStoreRange
    mr      r3, r31
    li      r4, 0
    bl      __VMBASESetVirtualAddressForPageInMRAM
    mr      r3, r31
    li      r4, 0
    bl      VMBASESetPageLocked
    mr      r3, r30
    bl      __VMBASEClearPageFromTLB
    lwz     r0, 0x14(r1)
    lwz     r31, 0xc(r1)
    lwz     r30, 0x8(r1)
    mtlr    r0
    addi    r1, r1, 0x10
    blr
    // clang-format on
}
