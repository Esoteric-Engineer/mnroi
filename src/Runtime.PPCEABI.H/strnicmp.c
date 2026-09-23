extern void tolower(void);

asm int strnicmp(const char* s1, const char* s2, unsigned long n)
{
    // clang-format off
    nofralloc
    stwu    r1, -0x18(r1)
    mflr    r0
    stmw    r28, 0x8(r1)
    stw     r0, 0x1c(r1)
    mr      r29, r3
    mr      r28, r4
    mr.     r31, r5
    bne     cond
    li      r3, 0
    b       done
next:
    addi    r29, r29, 1
    addi    r28, r28, 1
cond:
    cmpwi   r31, 0
    subi    r31, r31, 1
    beq     tail
    lbz     r3, 0(r29)
    extsb   r3, r3
    bl      tolower
    lbz     r0, 0(r28)
    mr      r30, r3
    extsb   r3, r0
    bl      tolower
    cmpw    r30, r3
    bne     tail
    cmpwi   r31, 0
    beq     tail
    lbz     r0, 0(r29)
    cmpwi   r0, 0
    beq     tail
    lbz     r0, 0(r28)
    cmpwi   r0, 0
    bne     next
tail:
    lbz     r3, 0(r29)
    bl      tolower
    mr      r30, r3
    lbz     r3, 0(r28)
    bl      tolower
    subf    r3, r3, r30
done:
    lwz     r0, 0x1c(r1)
    mtlr    r0
    lmw     r28, 0x8(r1)
    addi    r1, r1, 0x18
    blr
    // clang-format on
}
