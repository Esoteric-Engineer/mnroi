extern void* __AXCallbackAuxA;
extern void* __AXCallbackAuxB;

void __AXAuxQuit(void)
{
    __AXCallbackAuxA = 0;
    __AXCallbackAuxB = 0;
}
