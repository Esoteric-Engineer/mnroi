extern unsigned long* g_baseVMtoARAM;

unsigned long __VMIsARAMPageDirty(unsigned long addr)
{
    return g_baseVMtoARAM[(addr >> 12) & 0x1FFF] >> 31;
}
