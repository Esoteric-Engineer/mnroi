extern long lbl_8066CEA4;

extern void fn_80400D30(void);
extern void __VMPageReplacementRandom(void);
extern void __VMPageReplacementFIFO(void);

// Dispatches on the replacement mode: 0 LRU, 1 random, else FIFO. GCC output, so asm.
asm void __VMGetPageToReplace(void)
{
    // clang-format off
    nofralloc
    stwu    r1, -0x10(r1)
    mflr    r0
    stw     r0, 0x14(r1)
    lwz     r0, lbl_8066CEA4
    cmpwi   r0, 0
    bne     L_not_lru
    bl      fn_80400D30
    b       L_done
L_not_lru:
    cmpwi   r0, 1
    bne     L_fifo
    bl      __VMPageReplacementRandom
    b       L_done
L_fifo:
    bl      __VMPageReplacementFIFO
L_done:
    lwz     r0, 0x14(r1)
    mtlr    r0
    addi    r1, r1, 0x10
    blr
    // clang-format on
}
