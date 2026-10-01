extern unsigned long __AXCommandListPosition;
extern void* __AXClWrite;
extern unsigned long __AXCompressor;
extern unsigned long __AXClMode;
extern unsigned char lbl_80652040[];

void __AXClInit(void)
{
    __AXClMode = 0;
    __AXCommandListPosition = 0;
    __AXClWrite = lbl_80652040;
    __AXCompressor = 1;
}
