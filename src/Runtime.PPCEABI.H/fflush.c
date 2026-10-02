extern void _fwalk(void);
extern void __sinit(void);
extern unsigned int lbl_8066C3B0;

asm int fflush(void* stream)
{
    // clang-format off
    nofralloc
    stwu    r1, -24(r1)
    mflr    r0
    stmw    r29, 12(r1)
    stw     r0, 28(r1)
    mr.     r31, r3
    bne     have_stream
    lis     r4, fflush@ha
    lwz     r3, lbl_8066C3B0
    addi    r4, r4, fflush@l
    bl      _fwalk
    b       epilogue
have_stream:
    lwz     r0, 92(r31)
    cmpwi   r0, 0
    bne     have_92
    lwz     r0, lbl_8066C3B0
    stw     r0, 92(r31)
have_92:
    lwz     r3, 92(r31)
    lwz     r0, 56(r3)
    cmpwi   r0, 0
    bne     have_56
    crclr   4*cr1+eq
    bl      __sinit
have_56:
    lha     r3, 12(r31)
    andi.   r0, r3, 8
    beq     ret0
    lwz     r29, 16(r31)
    cmpwi   r29, 0
    beq     ret0
    lwz     r0, 0(r31)
    andi.   r9, r3, 3
    stw     r29, 0(r31)
    subf    r30, r29, r0
    bne     zero_r0
    lwz     r0, 20(r31)
    b       after_store
fail:
    lhz     r0, 12(r31)
    li      r3, -1
    ori     r0, r0, 64
    sth     r0, 12(r31)
    b       epilogue
zero_r0:
    li      r0, 0
after_store:
    stw     r0, 8(r31)
    cmpwi   r30, 0
    ble     ret0
loop:
    lwz     r9, 36(r31)
    mr      r4, r29
    lwz     r3, 28(r31)
    mr      r5, r30
    mtlr    r9
    blrl
    mr.     r3, r3
    ble     fail
    add     r29, r29, r3
    subf.   r30, r3, r30
    bgt     loop
ret0:
    li      r3, 0
epilogue:
    lwz     r0, 28(r1)
    mtlr    r0
    lmw     r29, 12(r1)
    addi    r1, r1, 24
    blr
    // clang-format on
}
