extern unsigned long __AXCommandListPosition;
extern void* __AXClWrite;
extern unsigned char lbl_80652040[];

void* __AXGetCommandListAddress(void)
{
    void* addr = lbl_80652040 + __AXCommandListPosition++ * 0x300;
    __AXCommandListPosition &= 1;
    __AXClWrite = lbl_80652040 + __AXCommandListPosition * 0x300;
    return addr;
}
