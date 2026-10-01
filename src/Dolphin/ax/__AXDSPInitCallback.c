extern unsigned long __AXDSPInitFlag;

void __AXDSPInitCallback(void)
{
    __AXDSPInitFlag = 1;
}
