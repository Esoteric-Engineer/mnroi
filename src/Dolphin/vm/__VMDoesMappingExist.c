extern unsigned long* lbl_8066F974;

unsigned long __VMDoesMappingExist(unsigned long addr)
{
    unsigned long v = lbl_8066F974[(addr >> 12) & 0x1FFF] & 0x7FFFFFFF;
    return (-v | v) >> 31;
}
