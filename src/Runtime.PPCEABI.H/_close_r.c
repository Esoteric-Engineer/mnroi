extern int lbl_8066FB30;
extern int fn_8017A6EC(short request);

asm int _close_r(void* device, short flag)
{
    // clang-format off
    nofralloc
    stwu    r1, -16(r1)
    mflr    r0
    stw     r31, 12(r1)
    stw     r0, 20(r1)
    li      r0, 0
    mr      r31, r3
    stw     r0, lbl_8066FB30
    mr      r3, r4
    bl      fn_8017A6EC
    cmpwi   r3, -1
    bne     epilogue
    lwz     r0, lbl_8066FB30
    cmpwi   r0, 0
    beq     epilogue
    stw     r0, 0(r31)
epilogue:
    lwz     r0, 20(r1)
    mtlr    r0
    lwz     r31, 12(r1)
    addi    r1, r1, 16
    blr
    // clang-format on
}
