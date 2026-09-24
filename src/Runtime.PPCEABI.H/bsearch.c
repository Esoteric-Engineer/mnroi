asm void* bsearch(const void* key, const void* base, unsigned long nmemb, unsigned long size,
                  int (*compar)(const void*, const void*))
{
    // clang-format off
    nofralloc
    stwu    r1, -0x28(r1)
    mflr    r0
    stmw    r24, 0x8(r1)
    stw     r0, 0x2c(r1)
    mr      r24, r3
    mr      r25, r4
    mr      r27, r6
    mr      r26, r7
    li      r28, 0
    mr.     r29, r5
    beq     none
    cmpwi   r27, 0
    bne     check
    b       none
found:
    mr      r3, r30
    b       done
loop:
    add     r9, r28, r29
    mr      r3, r24
    srwi    r31, r9, 1
    mtlr    r26
    mullw   r0, r31, r27
    add     r30, r25, r0
    mr      r4, r30
    blrl
    cmpwi   r3, 0
    bge     notless
    mr      r29, r31
    b       check
notless:
    ble     found
    addi    r28, r31, 1
check:
    cmplw   r28, r29
    blt     loop
none:
    li      r3, 0
done:
    lwz     r0, 0x2c(r1)
    mtlr    r0
    lmw     r24, 0x8(r1)
    addi    r1, r1, 0x28
    blr
    // clang-format on
}
