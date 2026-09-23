extern char lbl_8049C224[];
extern void OSPanic(void);

asm void free(void)
{
    // clang-format off
    nofralloc
    stwu    r1, -8(r1)
    mflr    r0
    stw     r0, 12(r1)
    mflr    r6
    lis     r5, lbl_8049C224@ha
    subi    r6, r6, 4
    addi    r5, r5, lbl_8049C224@l
    li      r3, 0
    li      r4, 0
    crclr   6
    bl      OSPanic
    lwz     r0, 12(r1)
    mtlr    r0
    addi    r1, r1, 8
    blr
    // clang-format on
}
