typedef void (*__OSInterruptHandler)(short interrupt, void* context);

extern __OSInterruptHandler* InterruptHandlerTable;

__OSInterruptHandler __OSSetInterruptHandler(short interrupt, __OSInterruptHandler handler)
{
    __OSInterruptHandler oldHandler;

    oldHandler = InterruptHandlerTable[interrupt];
    InterruptHandlerTable[interrupt] = handler;
    return oldHandler;
}
