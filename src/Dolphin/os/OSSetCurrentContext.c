typedef unsigned long u32;

typedef struct OSContext OSContext;

asm void OSSetCurrentContext(register OSContext* context)
{
    nofralloc

    lis     r4, 0x8000
    stw     context, 0xD4(r4)

    clrlwi  r5, context, 2
    stw     r5, 0xC0(r4)

    lwz     r5, 0xD8(r4)
    cmpw    r5, context
    bne     _disableFPU

    lwz     r6, 0x19C(context)
    ori     r6, r6, 0x2000
    stw     r6, 0x19C(context)
    mfmsr   r6
    ori     r6, r6, 2
    mtmsr   r6
    blr

_disableFPU:
    lwz     r6, 0x19C(context)
    rlwinm  r6, r6, 0, 19, 17
    stw     r6, 0x19C(context)
    mfmsr   r6
    rlwinm  r6, r6, 0, 19, 17
    ori     r6, r6, 2
    mtmsr   r6
    isync
    blr
}
