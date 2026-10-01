extern unsigned long __AXCommandListPosition;
extern void* __AXClWrite;
extern unsigned long __AXCompressor;
extern unsigned long __AXClMode;
extern unsigned char __AXCommandList[];

void __AXClInit(void)
{
    __AXClMode = 0;
    __AXCommandListPosition = 0;
    __AXClWrite = __AXCommandList;
    __AXCompressor = 1;
}
