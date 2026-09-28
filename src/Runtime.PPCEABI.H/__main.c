__declspec(section ".data") int initialized;
extern void __do_global_ctors(void);

asm void __main(void)
{
    // clang-format off
    nofralloc
    stwu    r1, -8(r1)
    mflr    r0
    stw     r0, 12(r1)
    lis     r9, initialized@ha
    lwz     r0, initialized@l(r9)
    cmpwi   r0, 0
    bne     epilogue
    li      r0, 1
    stw     r0, initialized@l(r9)
    bl      __do_global_ctors
epilogue:
    lwz     r0, 12(r1)
    mtlr    r0
    addi    r1, r1, 8
    blr
    // clang-format on
}
