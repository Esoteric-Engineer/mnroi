extern void __OSPSInit(void);
extern void __OSInitFPRs(void);
extern void __OSCacheInit(void);

__declspec(section ".init") asm void __init_hardware(void)
{
    // clang-format off
    nofralloc
    mfmsr r0
    ori r0, r0, 0x2000
    mtmsr r0
    mflr r31
    bl __OSPSInit
    bl __OSInitFPRs
    bl __OSCacheInit
    mtlr r31
    blr
    /* 20 bytes of zero padding to the end of .init (section alignment) */
    opword 0
    opword 0
    opword 0
    opword 0
    opword 0
    // clang-format on
}
