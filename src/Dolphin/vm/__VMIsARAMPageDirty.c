extern unsigned long* lbl_8066F974;

unsigned long __VMIsARAMPageDirty(unsigned long addr)
{
    return lbl_8066F974[(addr >> 12) & 0x1FFF] >> 31;
}
