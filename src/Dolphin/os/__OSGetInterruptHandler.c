typedef void (*__OSInterruptHandler)(short interrupt, void* context);

extern __OSInterruptHandler* InterruptHandlerTable;

__OSInterruptHandler __OSGetInterruptHandler(short interrupt)
{
    return InterruptHandlerTable[interrupt];
}
