extern void fn_80168770(void);
extern void fn_80168C9C(void);
extern void DCFlushRange(void);

asm void fn_80168E34(void)
{
    // clang-format off
    nofralloc
    mflr    r30
    li      r6, 0x702
    lis     r3, 0
    ori     r3, r3, 0x8000
    lhbrx   r5, r6, r31
    cmplw   r5, r3
    ble     L_clamped
    mr      r5, r3
    stwbrx  r5, r6, r31
L_clamped:
    mr      r29, r5
    addi    r3, r31, 0x708
    li      r6, 0x704
    lwbrx   r4, r6, r31
    lwz     r7, 0x390(r31)
    andis.  r7, r7, 0x1000
    bne     L_flush
    lis     r7, 0xe000
    cmplw   r4, r7
    blt     L_fill
    ori     r7, r7, 0x3fff
    cmplw   r4, r7
    bgt     L_fill
    li      r6, 0x702
    li      r4, 0
    sthbrx  r4, r6, r31
    addi    r3, r31, 0x700
    li      r4, 8
    b       L_call
L_fill:
    bl      fn_80168770
    cmplwi  r3, 1
    beq     L_send
    addi    r6, r31, 0x708
    mr      r3, r29
    li      r5, 0xaa
L_loop:
    subi    r3, r3, 1
    stbx    r5, r3, r6
    cmpwi   r3, 0
    bgt     L_loop
    b       L_send
L_flush:
    mr      r28, r4
    bl      fn_80168770
    lis     r7, 0xe000
    cmplw   r4, r7
    blt     L_dcflush
    ori     r7, r7, 0x3fff
    cmplw   r4, r7
    ble     L_send
L_dcflush:
    mr      r3, r28
    mr      r4, r29
    bl      DCFlushRange
L_send:
    addi    r3, r31, 0x700
    mr      r4, r29
    addi    r4, r4, 8
L_call:
    lwz     r0, 0x6a4(r31)
    mtlr    r0
    blrl
    cmpwi   r3, 0
    bne     fn_80168C9C
    mtlr    r30
    blr
    // clang-format on
}
