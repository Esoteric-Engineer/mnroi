typedef void (*__OSInterruptHandler)(short interrupt, void* context);

volatile long long __OSLastInterruptTime;
volatile short __OSLastInterrupt;
volatile unsigned long __OSLastInterruptSrr0;
__OSInterruptHandler* InterruptHandlerTable;

__OSInterruptHandler __OSSetInterruptHandler(short interrupt, __OSInterruptHandler handler)
{
    __OSInterruptHandler oldHandler;

    oldHandler = InterruptHandlerTable[interrupt];
    InterruptHandlerTable[interrupt] = handler;
    return oldHandler;
}
