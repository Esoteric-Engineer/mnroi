// Invalidates the TLB entry for the page at addr. Hand-written asm.
asm void __VMBASEClearPageFromTLB(unsigned long addr)
{
    // clang-format off
    nofralloc
    rlwinm  r0, r3, 0, 14, 19
    tlbsync
    tlbie   r0
    blr
    // clang-format on
}
