extern void tolower(void);

asm int stricmp(const char* s1, const char* s2)
{
    // clang-format off
    nofralloc
    stwu    r1, -0x18(r1)
    mflr    r0
    stmw    r29, 0xc(r1)
    stw     r0, 0x1c(r1)
    mr      r31, r3
    mr      r29, r4
    b       cond
next:
    addi    r31, r31, 1
    addi    r29, r29, 1
cond:
    lbz     r0, 0(r31)
    extsb   r3, r0
    cmpwi   r3, 0
    beq     tail
    bl      tolower
    lbz     r0, 0(r29)
    mr      r30, r3
    extsb   r3, r0
    bl      tolower
    cmpw    r30, r3
    beq     next
tail:
    lbz     r3, 0(r31)
    bl      tolower
    mr      r30, r3
    lbz     r3, 0(r29)
    bl      tolower
    subf    r3, r3, r30
    lwz     r0, 0x1c(r1)
    mtlr    r0
    lmw     r29, 0xc(r1)
    addi    r1, r1, 0x18
    blr
    // clang-format on
}
