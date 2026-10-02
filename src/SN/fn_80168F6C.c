extern void fn_80168C9C(void);

asm void fn_80168F6C(void)
{
    // clang-format off
    nofralloc
    mflr    r30
    li      r4, 0
    addi    r5, r31, 0x70c
    lis     r6, 0x8000
    lwz     r6, 0x30c8(r6)
    cmpwi   r6, 0
    beq     L_done
    li      r7, 0
    li      r8, 4
    li      r9, 8
    li      r10, 0xc
L_loop:
    addi    r4, r4, 1
    stwbrx  r6, r7, r5
    lwz     r3, 0(r6)
    stwbrx  r3, r8, r5
    lwz     r3, 0x14(r6)
    stwbrx  r3, r9, r5
    lwz     r3, 0x18(r6)
    stwbrx  r3, r10, r5
    addi    r5, r5, 0x10
    cmpwi   r4, 0x40
    beq     L_done
    lwz     r6, 4(r6)
    cmpwi   r6, 0
    bne     L_loop
L_done:
    addi    r3, r31, 0x708
    li      r6, 0
    stwbrx  r4, r6, r3
    li      r6, 0x702
    subf    r4, r3, r5
    stwbrx  r4, r6, r31
    addi    r4, r4, 8
    addi    r3, r31, 0x700
    lwz     r0, 0x6a4(r31)
    mtlr    r0
    blrl
    cmpwi   r3, 0
    bne     fn_80168C9C
    mtlr    r30
    blr
    // clang-format on
}
