#pragma peephole off

typedef void (*__OSExceptionHandler)(unsigned char exception, void* context);

extern __OSExceptionHandler* OSExceptionTable;

__OSExceptionHandler __OSSetExceptionHandler(unsigned char exception, __OSExceptionHandler handler)
{
    __OSExceptionHandler oldHandler;

    oldHandler = OSExceptionTable[exception];
    OSExceptionTable[exception] = handler;
    return oldHandler;
}

__OSExceptionHandler __OSGetExceptionHandler(unsigned char exception)
{
    return OSExceptionTable[exception];
}
