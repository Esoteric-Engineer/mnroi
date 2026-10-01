extern void* __AXCallbackAuxA;
extern unsigned long __AXContextAuxA;

void AXRegisterAuxACallback(void* callback, unsigned long context)
{
    __AXCallbackAuxA = callback;
    __AXContextAuxA = context;
}
