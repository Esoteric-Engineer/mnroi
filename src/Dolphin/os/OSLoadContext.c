typedef struct OSContext OSContext;

extern void OSDisableInterrupts(void);

asm void OSLoadContext(register OSContext* context)
{
    nofralloc

    lis     r4, OSDisableInterrupts@ha
    lwz     r6, 0x198(context)
    addi    r5, r4, OSDisableInterrupts@l
    cmplw   r6, r5
    ble     _notInRAS
    lis     r4, (OSDisableInterrupts+0xC)@ha
    addi    r0, r4, (OSDisableInterrupts+0xC)@l
    cmplw   r6, r0
    bge     _notInRAS
    stw     r5, 0x198(context)

_notInRAS:
    lwz     r0, 0x0(context)
    lwz     r1, 0x4(context)
    lwz     r2, 0x8(context)

    lhz     r4, 0x1A2(context)
    rlwinm. r5, r4, 0, 30, 30
    beq     _notexc
    rlwinm  r4, r4, 0, 31, 29
    sth     r4, 0x1A2(context)
    lmw     r5, 0x14(context)
    b       _misc
_notexc:
    lmw     r13, 0x34(context)
_misc:
    lwz     r4, 0x1A8(context)
    mtspr   GQR1, r4
    lwz     r4, 0x1AC(context)
    mtspr   GQR2, r4
    lwz     r4, 0x1B0(context)
    mtspr   GQR3, r4
    lwz     r4, 0x1B4(context)
    mtspr   GQR4, r4
    lwz     r4, 0x1B8(context)
    mtspr   GQR5, r4
    lwz     r4, 0x1BC(context)
    mtspr   GQR6, r4
    lwz     r4, 0x1C0(context)
    mtspr   GQR7, r4

    lwz     r4, 0x80(context)
    mtcrf   255, r4
    lwz     r4, 0x84(context)
    mtlr    r4
    lwz     r4, 0x88(context)
    mtctr   r4
    lwz     r4, 0x8C(context)
    mtxer   r4

    mfmsr   r4
    rlwinm  r4, r4, 0, 17, 15
    rlwinm  r4, r4, 0, 31, 29
    mtmsr   r4

    lwz     r4, 0x198(context)
    mtsrr0  r4
    lwz     r4, 0x19C(context)
    mtsrr1  r4

    lwz     r4, 0x10(context)
    lwz     r3, 0xC(context)

    rfi
}
