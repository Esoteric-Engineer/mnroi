typedef unsigned long u32;

extern void __OSSetInterruptHandler(int interrupt, void (*handler)(void));
extern u32 __OSUnmaskInterrupts(u32 mask);
extern u32 fn_8017FD74(void);
extern void GXCPInterruptHandler(void);

extern u32 CPUFifo;
extern u32 GPFifo;
extern u32 __GXCurrentThread;
extern u32 GXOverflowSuspendInProgress;

void __GXFifoInit(void)
{
    __OSSetInterruptHandler(0x11, GXCPInterruptHandler);
    __OSUnmaskInterrupts(0x4000);
    __GXCurrentThread = fn_8017FD74();
    GXOverflowSuspendInProgress = 0;
    CPUFifo = 0;
    GPFifo = 0;
}
