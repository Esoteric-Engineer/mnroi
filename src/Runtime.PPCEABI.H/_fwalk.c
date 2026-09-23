// _fwalk(reent, func): calls func(fp) for every open FILE in reent->__sglue.
asm int _fwalk(void* ptr, int (*function)(void*))
{
    // clang-format off
    nofralloc
    stwu    r1, -32(r1)
    mflr    r0
    stmw    r27, 12(r1)
    stw     r0, 36(r1)
    mr      r27, r4
    li      r28, 0
    addic.  r29, r3, 0x1d8
    beq     done
glue:
    lwz     r31, 4(r29)
    lwz     r30, 8(r29)
    subic.  r31, r31, 1
    blt     next
file:
    lha     r0, 12(r30)
    cmpwi   r0, 0
    beq     skip
    mr      r3, r30
    mtlr    r27
    crclr   6
    blrl
    or      r28, r28, r3
skip:
    addi    r30, r30, 0x60
    subic.  r31, r31, 1
    bge     file
next:
    lwz     r29, 0(r29)
    cmpwi   r29, 0
    bne     glue
done:
    mr      r3, r28
    lwz     r0, 36(r1)
    mtlr    r0
    lmw     r27, 12(r1)
    addi    r1, r1, 32
    blr
    // clang-format on
}
