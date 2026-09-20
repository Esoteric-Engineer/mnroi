typedef void (*__OSInterruptHandler)(short interrupt, void* context);

extern __OSInterruptHandler* lbl_8066F220;

__OSInterruptHandler __OSGetInterruptHandler(short interrupt)
{
    return lbl_8066F220[interrupt];
}
