extern unsigned long __AXDSPDoneFlag;
extern unsigned long __AXOutThreadQueue[2];
extern void OSWakeupThread(void*);

void __AXDSPDoneCallback(void)
{
    __AXDSPDoneFlag = 1;
    OSWakeupThread(__AXOutThreadQueue);
}
