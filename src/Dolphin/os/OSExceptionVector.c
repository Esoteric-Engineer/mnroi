extern void OSDefaultExceptionHandler(void);

asm void OSExceptionVector(void)
{
    // clang-format off
    nofralloc
    mtsprg  0, r4
    lwz     r4, 0xc0(r0)
    stw     r3, 0xc(r4)
    mfsprg  r3, 0
    stw     r3, 0x10(r4)
    stw     r5, 0x14(r4)
    lhz     r3, 0x1a2(r4)
    ori     r3, r3, 2
    sth     r3, 0x1a2(r4)
    mfcr    r3
    stw     r3, 0x80(r4)
    mflr    r3
    stw     r3, 0x84(r4)
    mfctr   r3
    stw     r3, 0x88(r4)
    mfxer   r3
    stw     r3, 0x8c(r4)
    mfsrr0  r3
    stw     r3, 0x198(r4)
    mfsrr1  r3
    stw     r3, 0x19c(r4)
    mr      r5, r3
    nop
    mfmsr   r3
    ori     r3, r3, 0x30
    mtsrr1  r3
    li      r3, 0
    lwz     r4, 0xd4(r0)
    rlwinm. r5, r5, 0, 30, 30
    bne     recoverable
    lis     r5, OSDefaultExceptionHandler@ha
    addi    r5, r5, OSDefaultExceptionHandler@l
    mtsrr0  r5
    rfi
recoverable:
    rlwinm  r5, r3, 2, 22, 29
    lwz     r5, 0x3000(r5)
    mtsrr0  r5
    rfi
    nop
    // clang-format on
}
