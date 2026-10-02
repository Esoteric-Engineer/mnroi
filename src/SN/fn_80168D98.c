void fn_80168770(void);
void DCFlushRange(void);
void ICInvalidateRange(void);

asm void fn_80168D98(void)
{
    // clang-format off
    nofralloc
    mflr    r30
    li      r6, 0x704
    lwbrx   r3, r6, r31
    addi    r4, r31, 0x708
    li      r6, 0x702
    lhbrx   r5, r6, r31
    lwz     r7, 0x390(r31)
    andis.  r7, r7, 0x1000
    bne     L_flush
    lis     r7, 0xe000
    cmplw   r4, r7
    blt     L_flush
    ori     r7, r7, 0x3fff
    cmplw   r4, r7
    bgt     L_flush
    li      r6, 0x702
    li      r4, 0
    sthbrx  r4, r6, r31
    addi    r3, r31, 0x700
    li      r4, 8
    b       L_call
L_flush:
    mr      r28, r3
    mr      r29, r5
    bl      fn_80168770
    cmplwi  r3, 1
    beq     L_next
L_next:
    mr      r3, r28
    mr      r4, r29
    bl      DCFlushRange
    mr      r3, r28
    mr      r4, r29
    bl      ICInvalidateRange
    addi    r3, r31, 0x700
L_call:
    li      r4, 8
    lwz     r0, 0x6a4(r31)
    mtlr    r0
    blrl
    mtlr    r30
    blr
    // clang-format on
}
