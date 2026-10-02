asm void OSSwitchStack(register unsigned long pc, register unsigned long newsp)
{
    nofralloc

    mflr    r0
    mr      r5, r1
    stwu    r5, -8(r4)
    mr      r1, r4
    stw     r0, 4(r5)
    mtlr    r3
    blrl
    lwz     r5, 0(r1)
    lwz     r0, 4(r5)
    mtlr    r0
    mr      r1, r5
    blr
}
