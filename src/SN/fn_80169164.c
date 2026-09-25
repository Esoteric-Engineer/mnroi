asm void fn_80169164(void)
{
    // clang-format off
    nofralloc
    mflr    r30
    lbz     r3, 0x707(r31)
    lis     r4, 0
    ori     r4, r4, 0x704
    lhbrx   r4, r4, r31
    lwz     r5, 0x708(r31)
    cmplwi  r3, 0xff
    beq     done
done:
    mtlr    r30
    blr
    // clang-format on
}
