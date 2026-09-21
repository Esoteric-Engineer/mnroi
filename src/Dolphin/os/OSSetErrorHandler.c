typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned long u32;
typedef unsigned long long u64;
typedef int s32;

typedef void (*OSErrorHandler)(u16 error, void* context, u32 dsisr, u32 dar);

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

extern OSErrorHandler __OSErrorTable[17];
extern volatile u32 lbl_8066C3D0;

extern volatile OSThread* __OSActiveThreadQueueHead : 0x800000DC;

extern int OSDisableInterrupts(void);
extern void OSRestoreInterrupts(int level);
extern u32 PPCMfmsr(void);
extern void PPCMtmsr(u32 msr);
extern u32 PPCMffpscr(void);
extern void PPCMtfpscr(u32 fpscr);

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
                thread->context.fpscr |= lbl_8066C3D0 & 0xF8;
                thread->context.fpscr &= 0x6005F8FF;
            }
            msr |= 0x900;
            fpscr |= lbl_8066C3D0 & 0xF8;
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
