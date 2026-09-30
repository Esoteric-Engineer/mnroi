extern unsigned long* g_baseVMtoARAM;

void __VMSetARAMPageAsDirty(unsigned long addr)
{
    g_baseVMtoARAM[(addr >> 12) & 0x1FFF] |= 0x80000000;
}
