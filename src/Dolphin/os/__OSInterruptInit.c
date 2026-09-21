#pragma peephole off
extern void* memset(void* dst, int val, unsigned long n);
extern void __OSMaskInterrupts(unsigned long mask);
extern void __OSSetExceptionHandler(unsigned char exception, void (*handler)(void));
extern void ExternalInterruptHandler(void);

extern void* InterruptHandlerTable;

volatile unsigned long __PIRegs[0x20] : 0xCC003000;

void __OSInterruptInit(void)
{
    InterruptHandlerTable = (void*)0x80003040;

    memset(InterruptHandlerTable, 0, 0x80);

    *(volatile unsigned long*)0x800000C4 = 0;
    *(volatile unsigned long*)0x800000C8 = 0;

    __PIRegs[1] = 0xF0;

    __OSMaskInterrupts(0xFFFFFFE0);

    __OSSetExceptionHandler(4, ExternalInterruptHandler);
}
