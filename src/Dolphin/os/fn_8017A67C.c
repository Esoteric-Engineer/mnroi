extern int fn_8016AAF8(int);
extern void* fn_8017A620(void* a, void* b);

asm int fn_8017A67C(register int handle, register void* buf, register void* count)
{
    // clang-format off
    nofralloc
    stwu    r1, -8(r1)
    mflr    r0
    stw     r0, 12(r1)
    mr      r9, r3
    addi    r0, r9, -1
    cmplwi  r0, 1
    ble     L_write
    cmpwi   r9, 0
    li      r3, -1
    beq     L_end
    mr      r3, r9
    bl      fn_8016AAF8
    b       L_end
L_write:
    mr      r3, r4
    mr      r4, r5
    bl      fn_8017A620
L_end:
    lwz     r0, 12(r1)
    mtlr    r0
    addi    r1, r1, 8
    blr
    // clang-format on
}
