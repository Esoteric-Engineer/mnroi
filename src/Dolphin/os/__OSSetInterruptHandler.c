typedef void (*__OSInterruptHandler)(short interrupt, void* context);

extern __OSInterruptHandler* lbl_8066F220;

__OSInterruptHandler __OSSetInterruptHandler(short interrupt, __OSInterruptHandler handler)
{
    __OSInterruptHandler oldHandler;

    oldHandler = lbl_8066F220[interrupt];
    lbl_8066F220[interrupt] = handler;
    return oldHandler;
}
