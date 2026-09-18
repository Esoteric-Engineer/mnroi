extern int lbl_804D0678;
extern void fn_80195B78(int);
extern void fn_80195BE8(void* a, void* b);

asm void* fn_8017A620(register void* a, register void* b)
{
    // clang-format off
    nofralloc
    stwu    r1, -16(r1)
    mflr    r0
    stmw    r30, 8(r1)
    stw     r0, 20(r1)
    lis     r9, lbl_804D0678@ha
    mr      r30, r3
    lwz     r0, lbl_804D0678@l(r9)
    mr      r31, r4
    cmpwi   r0, 0
    beq     skip
    li      r0, 0
    li      r3, 0
    stw     r0, lbl_804D0678@l(r9)
    bl      fn_80195B78
skip:
    mr      r3, r30
    mr      r4, r31
    bl      fn_80195BE8
    mr      r3, r31
    lwz     r0, 20(r1)
    mtlr    r0
    lmw     r30, 8(r1)
    addi    r1, r1, 16
    blr
    // clang-format on
}
