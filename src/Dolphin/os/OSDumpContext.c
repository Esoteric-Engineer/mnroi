typedef unsigned short u16;
typedef unsigned long u32;
typedef double f64;

typedef struct OSContext {
    u32 gpr[32];
    u32 cr;
    u32 lr;
    u32 ctr;
    u32 xer;
    f64 fpr[32];
    u32 fpscr_pad;
    u32 fpscr;
    u32 srr0;
    u32 srr1;
    u16 mode;
    u16 state;
    u32 gqr[8];
    u32 psf_pad;
    f64 psf[32];
} OSContext;

extern void OSReport(const char* msg, ...);
extern int OSDisableInterrupts(void);
extern void OSRestoreInterrupts(int level);
extern void OSSetCurrentContext(OSContext* context);

volatile OSContext* __OSCurrentContext : 0x800000D4;
volatile OSContext* __OSFPUContext : 0x800000D8;

#pragma peephole off

static inline OSContext* OSGetCurrentContext_(void)
{
    return (OSContext*)__OSCurrentContext;
}

static inline void OSClearContext_(OSContext* context)
{
    context->mode = 0;
    context->state = 0;
    if (context == __OSFPUContext)
        __OSFPUContext = 0;
}

void OSDumpContext(OSContext* context)
{
    u32 i;
    u32* p;

    OSReport("------------------------- Context 0x%08x -------------------------\n", context);

    for (i = 0; i < 16; ++i) {
        OSReport("r%-2d  = 0x%08x (%14d)  r%-2d  = 0x%08x (%14d)\n", i, context->gpr[i], context->gpr[i], i + 16,
                 context->gpr[i + 16], context->gpr[i + 16]);
    }

    OSReport("LR   = 0x%08x                   CR   = 0x%08x\n", context->lr, context->cr);
    OSReport("SRR0 = 0x%08x                   SRR1 = 0x%08x\n", context->srr0, context->srr1);

    OSReport("\nGQRs----------\n");
    for (i = 0; i < 4; ++i) {
        OSReport("gqr%d = 0x%08x \t gqr%d = 0x%08x\n", i, context->gqr[i], i + 4, context->gqr[i + 4]);
    }

    if ((u32)(context->state & 1u)) {
        OSContext* currentContext;
        OSContext fpuContext;
        int enabled;

        enabled = OSDisableInterrupts();
        currentContext = OSGetCurrentContext_();
        OSClearContext_(&fpuContext);
        OSSetCurrentContext(&fpuContext);

        OSReport("\n\nFPRs----------\n");
        for (i = 0; i < 32; i += 2) {
            OSReport("fr%d \t= %d \t fr%d \t= %d\n", i, (u32)context->fpr[i], i + 1, (u32)context->fpr[i + 1]);
        }
        OSReport("\n\nPSFs----------\n");
        for (i = 0; i < 32; i += 2) {
            OSReport("ps%d \t= 0x%x \t ps%d \t= 0x%x\n", i, (u32)context->psf[i], i + 1, (u32)context->psf[i + 1]);
        }

        OSClearContext_(&fpuContext);
        OSSetCurrentContext(currentContext);
        OSRestoreInterrupts(enabled);
    }

    OSReport("\nAddress:      Back Chain    LR Save\n");
    for (i = 0, p = (u32*)context->gpr[1]; p && (u32)p != 0xffffffff && i++ < 16; p = (u32*)*p) {
        OSReport("0x%08x:   0x%08x    0x%08x\n", p, p[0], p[1]);
    }
}

extern void __OSSetExceptionHandler(unsigned char exception, void* handler);
extern void __OSLoadFPUContext();
extern void __OSSaveFPUContext();
extern void DBPrintf(char* msg, ...);

static asm void OSSwitchFPUContext(register unsigned char exception, register OSContext* context)
{
    nofralloc
    mfmsr   r5
    ori     r5, r5, 0x2000
    mtmsr   r5
    isync
    lwz     r5, 0x19C(context)
    ori     r5, r5, 0x2000
    mtsrr1  r5
    addis   r3, r0, 0x8000
    lwz     r5, 0xD8(r3)
    stw     context, 0xD8(r3)
    cmpw    r5, r4
    beq     _restoreAndExit
    cmpwi   r5, 0
    beq     _loadNewFPUContext
    bl      __OSSaveFPUContext
_loadNewFPUContext:
    bl      __OSLoadFPUContext
_restoreAndExit:
    lwz     r3, 0x80(context)
    mtcrf   255, r3
    lwz     r3, 0x84(context)
    mtlr    r3
    lwz     r3, 0x198(context)
    mtsrr0  r3
    lwz     r3, 0x88(context)
    mtctr   r3
    lwz     r3, 0x8C(context)
    mtxer   r3
    lhz     r3, 0x1A2(context)
    rlwinm  r3, r3, 0, 31, 29
    sth     r3, 0x1A2(context)
    lwz     r5, 0x14(context)
    lwz     r3, 0xC(context)
    lwz     r4, 0x10(context)
    rfi
}

void __OSContextInit(void)
{
    __OSSetExceptionHandler(7, OSSwitchFPUContext);
    __OSFPUContext = 0;
    DBPrintf("FPU-unavailable handler installed\n");
}
