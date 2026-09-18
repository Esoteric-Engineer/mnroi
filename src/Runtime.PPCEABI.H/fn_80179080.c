extern int lbl_8057C4F0;
extern void fn_80178FF0(void);

asm void fn_80179080(void)
{
    // clang-format off
    nofralloc
    stwu    r1, -8(r1)
    mflr    r0
    stw     r0, 12(r1)
    lis     r9, lbl_8057C4F0@ha
    lwz     r0, lbl_8057C4F0@l(r9)
    cmpwi   r0, 0
    bne     epilogue
    li      r0, 1
    stw     r0, lbl_8057C4F0@l(r9)
    bl      fn_80178FF0
epilogue:
    lwz     r0, 12(r1)
    mtlr    r0
    addi    r1, r1, 8
    blr
    // clang-format on
}
