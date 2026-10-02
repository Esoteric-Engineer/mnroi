typedef struct OSContext OSContext;

asm unsigned long OSSaveContext(register OSContext* context)
{
    nofralloc

    stmw    r13, 0x34(context)
    mfspr   r0, GQR1
    stw     r0, 0x1A8(context)
    mfspr   r0, GQR2
    stw     r0, 0x1AC(context)
    mfspr   r0, GQR3
    stw     r0, 0x1B0(context)
    mfspr   r0, GQR4
    stw     r0, 0x1B4(context)
    mfspr   r0, GQR5
    stw     r0, 0x1B8(context)
    mfspr   r0, GQR6
    stw     r0, 0x1BC(context)
    mfspr   r0, GQR7
    stw     r0, 0x1C0(context)
    mfcr    r0
    stw     r0, 0x80(context)
    mflr    r0
    stw     r0, 0x84(context)
    stw     r0, 0x198(context)
    mfmsr   r0
    stw     r0, 0x19C(context)
    mfctr   r0
    stw     r0, 0x88(context)
    mfxer   r0
    stw     r0, 0x8C(context)
    stw     r1, 0x4(context)
    stw     r2, 0x8(context)
    li      r0, 0x1
    stw     r0, 0xC(context)
    li      r3, 0
    blr
}
