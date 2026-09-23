typedef struct OSContext OSContext;

extern void __OSDispatchInterrupt(void);

asm void ExternalInterruptHandler(register int exception, register OSContext* context)
{
    nofralloc

    stw     r0, 0x0(context)
    stw     r1, 0x4(context)
    stw     r2, 0x8(context)
    stmw    r6, 0x18(context)
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
    stwu    r1, -0x8(r1)
    b       __OSDispatchInterrupt
}
