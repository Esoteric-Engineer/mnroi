typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned long u32;
typedef unsigned long long u64;
typedef short s16;
typedef int s32;

typedef struct __va_list_struct {
    char gpr;
    char fpr;
    char reserved[2];
    char* input_arg_area;
    char* reg_save_area;
} va_list[1];

typedef void (*OSErrorHandler)(u16 error, void* context, ...);

typedef struct OSContext {
    u32 gpr[32];
    u32 cr;
    u32 lr;
    u32 ctr;
    u32 xer;
    double fpr[32];
    u32 fpscr_pad;
    u32 fpscr;
    u32 srr0;
    u32 srr1;
    u16 mode;
    u16 state;
    u32 gqr[8];
    u32 psf_pad;
    double psf[32];
} OSContext;

typedef struct OSThread OSThread;

struct OSThread {
    OSContext context;
    u8 pad[0x2FC - sizeof(OSContext)];
    OSThread* activeNext;
};

OSErrorHandler __OSErrorTable[17];
extern volatile s16 __OSLastInterrupt;
extern volatile u32 __OSLastInterruptSrr0;
extern volatile long long __OSLastInterruptTime;

volatile OSThread* __OSActiveThreadQueueHead : 0x800000DC;
volatile OSContext* __OSFPUContext : 0x800000D8;

volatile u16 __DSPRegs[] : 0xCC005000;
volatile u32 __DIRegs[] : 0xCC006000;

extern int vprintf(const char* format, va_list arg);
extern void OSReport(const char* msg, ...);
extern int OSDisableInterrupts(void);
extern void OSRestoreInterrupts(int level);
extern unsigned long OSGetStackPointer(void);
extern void PPCHalt(void);
extern u32 PPCMfmsr(void);
extern void PPCMtmsr(u32 msr);
extern u32 PPCMffpscr(void);
extern void PPCMtfpscr(u32 fpscr);
extern long long OSGetTime(void);
extern int OSDisableScheduler(void);
extern int OSEnableScheduler(void);
extern void __OSReschedule(void);
extern void OSLoadContext(OSContext* context);
extern void OSSaveFPUContext(OSContext* context);
extern void OSDumpContext(OSContext* context);

u32 __OSFpscrEnableBits = 0xF8;

char OSPanicStr_804D0EF8[] = " in \"%s\" on line %d.\n";

void OSPanic(const char* file, int line, const char* msg, ...)
{
    va_list args;
    unsigned long i;
    unsigned long* p;

    OSDisableInterrupts();
    __builtin_va_info(&args);
    vprintf(msg, args);
    OSReport(OSPanicStr_804D0EF8, file, line);

    OSReport("\nAddress:      Back Chain    LR Save\n");
    for (i = 0, p = (unsigned long*)OSGetStackPointer(); p && (unsigned long)p != 0xffffffff && i++ < 16; p = (unsigned long*)*p) {
        OSReport("0x%08x:   0x%08x    0x%08x\n", p, p[0], p[1]);
    }

    PPCHalt();
}

OSErrorHandler OSSetErrorHandler(u16 error, OSErrorHandler handler)
{
    OSErrorHandler oldHandler;
    int enabled;

    enabled = OSDisableInterrupts();
    oldHandler = __OSErrorTable[error];
    __OSErrorTable[error] = handler;

    if (error == 16) {
        OSThread* thread;
        u32 msr;
        u32 fpscr;

        msr = PPCMfmsr();
        PPCMtmsr(msr | 0x2000);
        fpscr = PPCMffpscr();

        if (handler) {
            for (thread = (OSThread*)__OSActiveThreadQueueHead; thread; thread = thread->activeNext) {
                int i;
                thread->context.srr1 |= 0x900;
                if (!(thread->context.state & 1)) {
                    thread->context.state |= 1;
                    for (i = 0; i < 32; i++) {
                        *(u64*)&thread->context.fpr[i] = (u64)-1;
                        *(u64*)&thread->context.psf[i] = (u64)-1;
                    }
                    thread->context.fpscr = 4;
                }
                thread->context.fpscr |= __OSFpscrEnableBits & 0xF8;
                thread->context.fpscr &= 0x6005F8FF;
            }
            msr |= 0x900;
            fpscr |= __OSFpscrEnableBits & 0xF8;
        } else {
            for (thread = (OSThread*)__OSActiveThreadQueueHead; thread; thread = thread->activeNext) {
                thread->context.srr1 &= ~0x900;
                thread->context.fpscr &= ~0xF8;
                thread->context.fpscr &= 0x6005F8FF;
            }
            fpscr &= ~0xF8;
            msr &= ~0x900;
        }
        fpscr &= 0x6005F8FF;
        PPCMtfpscr(fpscr);
        PPCMtmsr(msr);
    }

    OSRestoreInterrupts(enabled);
    return oldHandler;
}

void __OSUnhandledException(u8 exception, OSContext* context, u32 dsisr, u32 dar)
{
    long long now = OSGetTime();

    if (!(context->srr1 & 2)) {
        OSReport("Non-recoverable Exception %d", exception);
    } else {
        if (exception == 6 && (context->srr1 & 0x100000) && __OSErrorTable[16]) {
            u32 msr;
            u32 fpscr;

            exception = 16;
            msr = PPCMfmsr();
            PPCMtmsr(msr | 0x2000);
            if (__OSFPUContext) {
                OSSaveFPUContext((OSContext*)__OSFPUContext);
            }
            fpscr = PPCMffpscr();
            fpscr &= 0x6005F8FF;
            PPCMtfpscr(fpscr);
            PPCMtmsr(msr);
            if (__OSFPUContext == context) {
                OSDisableScheduler();
                __OSErrorTable[exception](exception, context, dsisr, dar);
                context->srr1 &= ~0x2000;
                __OSFPUContext = 0;
                context->fpscr &= 0x6005F8FF;
                OSEnableScheduler();
                __OSReschedule();
            } else {
                context->srr1 &= ~0x2000;
                __OSFPUContext = 0;
            }
            OSLoadContext(context);
        }
        if (__OSErrorTable[exception]) {
            OSDisableScheduler();
            __OSErrorTable[exception](exception, context, dsisr, dar);
            OSEnableScheduler();
            __OSReschedule();
            OSLoadContext(context);
        }
        if (exception == 8) {
            OSLoadContext(context);
        }
        OSReport("Unhandled Exception %d", exception);
    }
    OSReport("\n");
    OSDumpContext(context);
    OSReport("\nDSISR = 0x%08x                   DAR  = 0x%08x\n", dsisr, dar);
    OSReport("TB = 0x%016llx\n", now);

    switch (exception) {
    case 2:
        OSReport("\nInstruction at 0x%x (read from SRR0) attempted to access "
                 "invalid address 0x%x (read from DAR)\n",
                 context->srr0, dar);
        break;
    case 3:
        OSReport("\nAttempted to fetch instruction from invalid address 0x%x "
                 "(read from SRR0)\n",
                 context->srr0);
        break;
    case 5:
        OSReport("\nInstruction at 0x%x (read from SRR0) attempted to access "
                 "unaligned address 0x%x (read from DAR)\n",
                 context->srr0, dar);
        break;
    case 6:
        OSReport("\nProgram exception : Possible illegal instruction/operation "
                 "at or around 0x%x (read from SRR0)\n",
                 context->srr0, dar);
        break;
    case 15:
        OSReport("\n");
        OSReport("AI DMA Address =   0x%04x%04x\n", __DSPRegs[24], __DSPRegs[25]);
        OSReport("ARAM DMA Address = 0x%04x%04x\n", __DSPRegs[16], __DSPRegs[17]);
        OSReport("DI DMA Address =   0x%08x\n", __DIRegs[5]);
        break;
    }
    OSReport("\nLast interrupt (%d): SRR0 = 0x%08x  TB = 0x%016llx\n", __OSLastInterrupt, __OSLastInterruptSrr0,
             __OSLastInterruptTime);
    PPCHalt();
}
