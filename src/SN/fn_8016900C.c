extern void fn_80168C9C(void);

asm void fn_8016900C(void)
{
    // clang-format off
    nofralloc
    mflr    r30
    li      r4, 0
    addi    r5, r31, 0x70c
    lis     r6, 0x8000
    lwz     r6, 0xdc(r6)
    cmpwi   r6, 0
    beq     L_done
    li      r7, 0
    li      r8, 4
    li      r9, 8
    li      r10, 0xc
    li      r11, 0x10
    li      r12, 0x14
    li      r14, 0x18
    li      r15, 0x1c
    li      r16, 0x20
L_loop:
    addi    r4, r4, 1
    stwbrx  r6, r7, r5
    lwz     r3, 0x2c8(r6)
    stwbrx  r3, r8, r5
    lwz     r3, 0x2cc(r6)
    stwbrx  r3, r9, r5
    lwz     r3, 0x2d0(r6)
    stwbrx  r3, r10, r5
    lwz     r3, 0x2d4(r6)
    stwbrx  r3, r11, r5
    lwz     r3, 0x2d8(r6)
    stwbrx  r3, r12, r5
    lwz     r3, 0x2f0(r6)
    stwbrx  r3, r14, r5
    li      r18, 0
    lwz     r3, 0x2e8(r6)
    addi    r17, r5, 0x24
L_list1:
    cmpwi   r3, 0
    beq     L_list1_end
    stwbrx  r3, r18, r17
    addi    r18, r18, 4
    lwz     r3, 0x2e0(r3)
    b       L_list1
L_list1_end:
    add     r17, r17, r18
    srwi    r18, r18, 2
    stwbrx  r18, r15, r5
    li      r18, 0
    lwz     r3, 0x2f4(r6)
L_list2:
    cmpwi   r3, 0
    beq     L_list2_end
    stwbrx  r3, r18, r17
    addi    r18, r18, 4
    lwz     r3, 0x10(r3)
    b       L_list2
L_list2_end:
    add     r17, r17, r18
    srwi    r18, r18, 2
    stwbrx  r18, r16, r5
    mr      r5, r17
    cmpwi   r4, 0x40
    beq     L_done
    lwz     r6, 0x2fc(r6)
    cmpwi   r6, 0
    bne     L_loop
L_done:
    addi    r3, r31, 0x708
    li      r6, 0
    stwbrx  r4, r6, r3
    li      r6, 0x702
    subf    r4, r3, r5
    sthbrx  r4, r6, r31
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
