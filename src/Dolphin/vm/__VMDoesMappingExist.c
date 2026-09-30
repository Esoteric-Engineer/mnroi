extern unsigned long* g_baseVMtoARAM;

unsigned long __VMDoesMappingExist(unsigned long addr)
{
    unsigned long v = g_baseVMtoARAM[(addr >> 12) & 0x1FFF] & 0x7FFFFFFF;
    return (-v | v) >> 31;
}
