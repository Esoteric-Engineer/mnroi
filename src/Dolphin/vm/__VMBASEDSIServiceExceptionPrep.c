extern void fn_80401CA4(void);

// Saves r0-r2/r6-r31 and GQR1-7 into the exception context in r3, loads DAR into r4, then joins the shared handler. Hand-written asm.
asm void __VMBASEDSIServiceExceptionPrep(void)
{
    // clang-format off
    nofralloc
    stw     r0, 0x0(r3)
    stw     r1, 0x4(r3)
    stw     r2, 0x8(r3)
    stmw    r6, 0x18(r3)
    mfspr   r0, 913
    stw     r0, 0x1a8(r3)
    mfspr   r0, 914
    stw     r0, 0x1ac(r3)
    mfspr   r0, 915
    stw     r0, 0x1b0(r3)
    mfspr   r0, 916
    stw     r0, 0x1b4(r3)
    mfspr   r0, 917
    stw     r0, 0x1b8(r3)
    mfspr   r0, 918
    stw     r0, 0x1bc(r3)
    mfspr   r0, 919
    stw     r0, 0x1c0(r3)
    mfspr   r4, 19
    b       fn_80401CA4
    // clang-format on
}
