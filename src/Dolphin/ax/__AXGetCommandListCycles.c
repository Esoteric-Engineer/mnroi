unsigned long __AXClMode;
unsigned long __AXCompressor;
unsigned long __AXCommandListCycles;
void* __AXClWrite;
unsigned long __AXCommandListPosition;

unsigned long __AXGetCommandListCycles(void)
{
    return __AXCommandListCycles;
}
