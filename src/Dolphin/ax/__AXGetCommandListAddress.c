extern unsigned long __AXCommandListPosition;
extern void* __AXClWrite;

unsigned char __AXCommandList[0x600];

void* __AXGetCommandListAddress(void)
{
    void* addr = __AXCommandList + __AXCommandListPosition++ * 0x300;
    __AXCommandListPosition &= 1;
    __AXClWrite = __AXCommandList + __AXCommandListPosition * 0x300;
    return addr;
}
