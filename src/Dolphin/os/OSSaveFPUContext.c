typedef struct OSContext OSContext;

extern void __OSSaveFPUContext(void);

asm void OSSaveFPUContext(register OSContext* fpuContext)
{
    // clang-format off
    nofralloc
    addi    r5, r3, 0
    b       __OSSaveFPUContext
    // clang-format on
}
